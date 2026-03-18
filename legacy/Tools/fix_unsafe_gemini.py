from litellm import completion
import os
import re
import pdfplumber
from tree_sitter import Language, Parser,Node
import tree_sitter_rust
from rust_analysis import analyze_rust_file
from openai import OpenAI,OpenAIError
from divide_blocks import parse_and_chunk_code
import json

from langchain.memory import ConversationBufferMemory
import time
import tiktoken 
import argparse
# Ensure OpenAI API key and base URL are set in environment variables

# Memory for functions to avoid
functions_memory = ConversationBufferMemory(
    input_key="functions_to_avoid",
    output_key="ignored_output"
)

# Memory for safe structs
structs_memory = ConversationBufferMemory(
    input_key="safe_structs",
    output_key="ignored_output"
)

# Initialize Tree-sitter for Rust
parser = Parser()
rust_language = Language(tree_sitter_rust.language())
parser.language = rust_language 

def count_tokens(text):
    encoding = tiktoken.get_encoding("cl100k_base")
    return len(encoding.encode(text))

def parse_static_items(code):
    """
    Parse the given code and return a list of all static variable declarations (mut and non-mut).
    """
    byte_code = code.encode('utf-8')
    tree = parser.parse(byte_code)
    root_node = tree.root_node

    static_items = []

    def extract_static_items(node, code_bytes):
        # Capture all static variable declarations
        if node.type == 'static_item':  # Tree-sitter node type for static declarations
            static_item = code_bytes[node.start_byte:node.end_byte].decode('utf-8')
            static_items.append(static_item)

        # Traverse the children of the node
        for child in node.children:
            extract_static_items(child, code_bytes)

    extract_static_items(root_node, byte_code)
    return static_items

def extract_struct_code(source_code):
    """
    Extracts the code of all structs from the source code.
    """
    query = rust_language.query("""
        (struct_item) @struct  ; Ensure we are matching the struct item
    """)
    tree = parser.parse(source_code.encode())
    root_node = tree.root_node
    captures = query.captures(root_node)
    structs = []

    for capture in captures['struct']:
        struct_node = capture
        struct_code = source_code[struct_node.start_byte:struct_node.end_byte]
        if "pub struct _IO_FILE" in struct_code:
            continue  # Skip this struct
        structs.append(struct_code)
        
    return structs
def extract_extern_c_functions(source_code):
    extern_c_functions = []
    pattern = r'extern "C" {([^}]*)}'
    match = re.search(pattern, source_code, re.MULTILINE | re.DOTALL)
    
    if match:
        extern_block = match.group(1)
        function_pattern = r'fn\s+(\w+)\s*\('
        extern_c_functions = re.findall(function_pattern, extern_block)
    
    return extern_c_functions

def extract_function_code(source_code, function_name):
    tree = parser.parse(source_code.encode())
    root_node = tree.root_node

    def find_function_node(node):
        if node.type in ['function_item', 'method_item']:
            func_name_node = node.child_by_field_name('name')
            if func_name_node and func_name_node.text.decode() == function_name:
                return node
        for child in node.children:
            result = find_function_node(child)
            if result:
                return result
        return None

    func_node = find_function_node(root_node)
    return func_node.text.decode() if func_node else None

def extract_c_code_from_type_def(json_file_path):
    """
    Extracts the 'c_code' field from entries in the JSON file where the 'fragment_type' is 'Type_def'.
    
    :param json_file_path: Path to the JSON file
    :return: List of 'c_code' strings
    """
    with open(json_file_path, 'r', encoding='utf-8') as f:
        data = json.load(f)

    # List to store extracted 'c_code' values
    c_code_list = []

    # Iterate over the JSON data and extract 'c_code' where 'fragment_type' is 'Type_def'
    for entry in data:
        if entry.get('fragment_type') == 'Type_def':
            c_code = entry.get('transpilation')
            if c_code:
                c_code_list.append(c_code)
    
    return c_code_list

# def extract_c_function_descriptions(pdf_path, function_names):
#     """
#     Extracts descriptions of specified C functions from a PDF file.
#     :param pdf_path: Path to the PDF file.
#     :param function_names: A list of function names to search for.
#     :return: A dictionary mapping function names to their descriptions.
#     """
#     descriptions = {}

#     # Open the PDF file using pdfplumber
#     with pdfplumber.open(pdf_path) as pdf:
#         # Iterate through all the pages of the PDF
#         for page_num, page in enumerate(pdf.pages):
#             text = page.extract_text()

#             if not text:
#                 continue  # Skip if no text on the page

#             # Split the text into lines for easier processing
#             lines = text.split('\n')

#             # Iterate over lines and search for function names
#             for i, line in enumerate(lines):
#                 line = line.strip()
                
#                 # Check if the line contains one of the function names
#                 for function in function_names:
#                     if function in line:
#                         # Capture the current line as the function name and prototype
#                         function_prototype = line

#                         # Look for the description in the next few lines
#                         description = []
#                         j = i + 1  # Start looking from the next line
#                         while j < len(lines) and not re.match(r'^\s*$', lines[j]):  # Continue until an empty line or end of block
#                             # Append to description only if it doesn't look like the next function
#                             if all(f not in lines[j] for f in function_names):
#                                 description.append(lines[j].strip())
#                             j += 1
                        
#                         # Join the description lines into one string
#                         descriptions[function] = {
#                             'prototype': function_prototype,
#                             'description': ' '.join(description).strip()
#                         }

#     return descriptions
def fix_extern_c_functions_block(block_code, functions_to_avoid):

    prompt_step1 = (
        f"The following Rust code is a section of a larger Rust function. Rewrite the following Rust code to eliminate the use of the following extern C functions: "
        f"({', '.join(functions_to_avoid)}).\n\n"
        f"```\n{block_code}\n```\n\n"
        f"If and only if there are raw pointers to remove, focus on these specific tasks for this section, otherwise just return the original snippet. Never add code that was not there originally:\n"
        f"1. This step is the most important, please ensure that you do this. Remove all raw pointers (remove all places with *) and replace with safe Rust types (e.g., &mut, &, Vec).\n"
        f"2. Use Rust's Result or Option types for error handling.\n"
        f"3. Replace C-style callbacks with safe Rust closures or function types.\n"
        f"4. Use Rust's native types (i32, u8, usize) instead of C types.\n"
        f"5. Replace function pointers with Box<dyn Fn> or similar Rust types.\n"
        "6. This step is very crucial. Keep as close to the original structure of the code as possible, as in retain the structure and logic of the original code. Pay especially close attention to how the code in the original snippet begins and ends, as well as how/where brackets and parentheses are placed throughout the code of the original snippet.  Ensure that the function declaration eg: pub unsafe extern \"C\" fn csv_parse( ... ) -> size_t {{ remains unremoved (raw pointers should also be replaced with safe types).\n"
        f"\nProvide only the converted Rust code for this specific section (do not include comments). The code should fit back into the larger function."
        f"\n```\n"
    )
    print(prompt_step1)
    try:
        response = completion(
        model="gemini/gemini-pro", 
        messages=[{"role": "user", "content":prompt_step1}],
        safety_settings=[
        {
            "category": "HARM_CATEGORY_HARASSMENT",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_HATE_SPEECH",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_SEXUALLY_EXPLICIT",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_DANGEROUS_CONTENT",
            "threshold": "BLOCK_NONE",
        },]
    )
        
        response_content = response.choices[0].message.content
        if response_content is None:
            print("No content in response. Full response object:", response)
        safe_code_step1 = re.sub(r'^```[a-z]*\n|\n```$', '', response_content, flags=re.MULTILINE).strip()
        return safe_code_step1

    except OpenAIError as e:
        print(f"API error encountered during Step 1: {e}")
        # Print the error details for debugging
        print(f"Error details: {e.http_status}, {e.error}")
        raise e

def fix_extern_c_functions(block_code, functions_to_avoid):
    prompt_step1 = (
        f"Rewrite the following Rust function code to eliminate the use of the following extern C functions: "
        f"({', '.join(functions_to_avoid)}).\n\n"
        f"```\n{block_code}\n```\n\n"
        f"Follow these guidelines when rewriting the function:\n"
        f"1. Remove all raw pointers (*mut, *const) and unsafe code.\n"
        f"2. Replace pointer types with Rust references (&mut or &) or owned types like Vec.\n"
        f"3. Replace unsafe blocks with safe Rust equivalents, avoiding manual memory management and pointer arithmetic.\n"
        f"4. Use Rust's native memory management functions like Vec::with_capacity and Vec::resize instead of libc::realloc and libc::free.\n"
        f"5. Use Rust types like i32, u8, usize, etc., and handle errors using Rust's error handling mechanisms like Result or Option.\n"
        f"6. Replace function pointers with Box<dyn Fn> or similar Rust types for safe function pointers.\n"
        f"7. Replace *mut libc::c_void in callback functions with &mut [u8] for type safety.\n\n"
        f"Provide only the converted Rust code for the specified function enclosed in triple backticks, "
        f"with absolutely no notes, explanations, or comments.\n```\n"
    )

    print(prompt_step1)
    try:
        response = completion(
        model="gemini/gemini-pro", 
        messages=[
            {"role": "user", "content":prompt_step1}],
        safety_settings=[
        {
            "category": "HARM_CATEGORY_HARASSMENT",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_HATE_SPEECH",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_SEXUALLY_EXPLICIT",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_DANGEROUS_CONTENT",
            "threshold": "BLOCK_NONE",
        },
    ]
    )
        response_content = response.choices[0].message.content
        safe_code_step1 = re.sub(r'^```[a-z]*\n|\n```$', '', response_content, flags=re.MULTILINE).strip()
        return safe_code_step1

    except OpenAIError as e:
        print(f"API error encountered during Step 1: {e}.")
        raise e  


def fix_unsafe_code(safe_code_step1, structs_context):
    safe_structs = []
    history = structs_context.get("history", "")
    match = re.search(r"Human: (.*?)\nAI:", history, re.MULTILINE | re.DOTALL)
    if match:
        safe_structs.append(match.group(1).strip())

    prompt_step2 = (
        f"Given the following struct definition:\n\n"
        f"```\n{safe_structs}\n```\n\n"
        f"Rewrite the following Rust function code to eliminate all unsafe parameters and operations involving raw pointers (*const, *mut), using completely safe Rust constructs instead."
        f"Replace raw pointers with safe Rust types or references, and ensure that function callbacks are updated to use safe Rust function types:】\n\n"
        f"```\n{safe_code_step1}\n```\n"
        f"\nProvide only the converted Rust code for the specified function enclosed in triple backticks, "
        f"with absolutely no notes, explanations, or comments\n```\n"
    )
    try:
        response = completion(
            model="gemini/gemini-pro", 
            messages=[{"role": "user", "content":prompt_step2}],
             safety_settings=[
        {
            "category": "HARM_CATEGORY_HARASSMENT",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_HATE_SPEECH",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_SEXUALLY_EXPLICIT",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_DANGEROUS_CONTENT",
            "threshold": "BLOCK_NONE",
        },
    ]
        )
        response_content = response.choices[0].message.content
        final_safe_code = re.sub(r'^```[a-z]*\n|\n```$', '', response_content, flags=re.MULTILINE).strip()
        return final_safe_code

    except OpenAIError as e:
        print(f"API error encountered during Step 2: {e}.")
        raise e 

def fix_unsafe_code_block(safe_code_step1, structs_context):
    safe_structs = []

    history = structs_context.get("history", "")
    match = re.search(r"Human: (.*?)\nAI:", history, re.MULTILINE | re.DOTALL)
    if match:
        safe_structs.append(match.group(1).strip())

    prompt_step2 = (
        f"Given the following struct definition:\n\n"
        f"```\n{safe_structs}\n```\n\n"
        f"Rewrite the following Rust code to eliminate all unsafe parameters and operations involving raw pointers (*const, *mut), using completely safe Rust constructs instead. The Rust code is a small portion of a larger Rust function, so please keep the structure of the code snippet in your response. "
        f"Replace raw pointers with safe Rust types or references, and ensure that function callbacks are updated to use safe Rust function types:】\n\n"
        f"```\n{safe_code_step1}\n```\n"
        f"\nFocus on these specific tasks for this section:\n "
        f"1. This step is the most important, please ensure that you do this. Remove all raw pointers (remove all places with *) and replace with safe Rust types (e.g., &mut, &, Vec).\n"
        f"2. Use Rust's Result or Option types for error handling.\n"
        f"3. Replace C-style callbacks with safe Rust closures or function types.\n"
        f"4. Use Rust's native types (i32, u8, usize) instead of C types.\n"
        f"5. Replace function pointers with Box<dyn Fn> or similar Rust types.\n"
        f"6. This step is very crucial. Keep as close to the original structure of the code as possible, as in retain the structure and logic of the original code. Pay especially close attention to how the code in the original snippet begins and ends, as well as how/where brackets and parentheses are placed throughout the code of the original snippet. For example, if there is no opening bracket in the original snippet, do not include one in your returned snippet.\n"
        f"\nProvide only the converted Rust code for this specific section (do not include comments). The code should fit back into the larger function."
        f"\n```\n"
    )
    print(prompt_step2)

    try:
        response = completion(
            model="gemini/gemini-pro", 
            messages=[{"role": "user", "content":prompt_step2}],
            safety_settings=[
        {
            "category": "HARM_CATEGORY_HARASSMENT",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_HATE_SPEECH",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_SEXUALLY_EXPLICIT",
            "threshold": "BLOCK_NONE",
        },
        {
            "category": "HARM_CATEGORY_DANGEROUS_CONTENT",
            "threshold": "BLOCK_NONE",
        },
    ]
        )
        response_content = response.choices[0].message.content
        final_safe_code = re.sub(r'^```[a-z]*\n|\n```$', '', response_content, flags=re.MULTILINE).strip()
        return final_safe_code

    except OpenAIError as e:
        print(f"API error encountered during Step 2: {e}.")
        raise e 


def convert_unsafe_to_safe(unsafe_code, pdf_path):
    functions_context = functions_memory.load_memory_variables({"functions_to_avoid": ""})
    structs_context = structs_memory.load_memory_variables({"safe_structs": ""})
    functions_to_avoid = []
    history = functions_context.get("history", "")
    match = re.search(r"Human: \[(.*?)\]", history)
    if match:
        functions_to_avoid = eval(f"[{match.group(1)}]")

    # function_descriptions = extract_c_function_descriptions(pdf_path, functions_to_avoid)
    blocks = parse_and_chunk_code(unsafe_code,7500)
    fixed_blocks = []
    for block in blocks:
        safe_code_step1 = fix_extern_c_functions_block(block, functions_to_avoid)
        time.sleep(2)
        final_safe_code = fix_unsafe_code_block(safe_code_step1, structs_context)
        fixed_blocks.append(final_safe_code)
    return "\n".join(fixed_blocks)


def contains_raw_pointers(struct_code):
    """
    Checks if the struct code contains any raw pointers.
    """
    return bool(re.search(r'\*const\s|\*mut\s', struct_code))

def convert_structs_to_safe(struct_code):
    """
    Converts the given Rust struct code to a version that does not use raw pointers or extern C functions.
    """
    functions_context = functions_memory.load_memory_variables({"functions_to_avoid": ""})
    # Extract functions to avoid from history
    functions_to_avoid = []
    history = functions_context.get("history", "")
    match = re.search(r"Human: \[(.*?)\]", history)
    if match:
        functions_to_avoid = eval(f"[{match.group(1)}]")  # Safely evaluate to list


    prompt = (
    f"Rewrite the following Rust struct code to eliminate all dereferences of raw pointers (*const T, *mut T) in the struct fields and method bodies. **Do not change** the function signatures or types involving raw pointers (e.g., `fn(size_t) -> *mut libc::c_void`). Instead, replace them with safer alternatives where appropriate.\n\n"
    f"Example transformation:\n"
    f"```rust\n"
    f"pub malloc_func: Option<unsafe extern \"C\" fn(size_t) -> *mut libc::c_void>,\n"
    f"To:\n"
    f"pub malloc_func: Option<Box<dyn Fn(usize) -> Vec<u8>>>,\n"
    f"```\n\n"
    f"Do not use the following extern C functions: ({', '.join(functions_to_avoid)}).\n\n"
    f"Keep the struct field names and types unchanged, except for converting the usage of raw pointers to safer alternatives. Ensure that the structure of the original struct remains unchanged. Provide only the modified code between ```\n``` without any additional explanations.\n\n"
    f"```\n{struct_code}\n```\n"
    )


    response = completion(
        model="gemini/gemini-pro", 
        messages=[{"role": "user", "content": prompt}]
    )
    response_content = response.choices[0].message.content

    safe_struct_code = re.sub(r'^```[a-z]*\n|\n```$', '', response_content, flags=re.MULTILINE).strip()
    
    # Save the current version of the struct
    structs_memory.save_context({"safe_structs": safe_struct_code}, {"ignored_output": ""})

    # Check if the new struct code still contains raw pointers
    if not contains_raw_pointers(safe_struct_code):
        # print("No raw pointers found, conversion complete.")
        return safe_struct_code
    
    # Update struct_code with the new version for the next iteration
    struct_code = safe_struct_code

    print("Maximum iterations reached. Returning the latest version of the code.")
    return safe_struct_code

def convert_typedef_to_safe(typedef_code):
    functions_context = functions_memory.load_memory_variables({"functions_to_avoid": ""})
    # Extract functions to avoid from history
    functions_to_avoid = []
    history = functions_context.get("history", "")
    match = re.search(r"Human: \[(.*?)\]", history)
    if match:
        functions_to_avoid = eval(f"[{match.group(1)}]")  # Safely evaluate to list


    prompt = (
    f"Rewrite the following Rust code to eliminate all dereferences of raw pointers (*const T, *mut T) in the struct fields and method bodies. **Do not change** the function signatures or types involving raw pointers (e.g., `fn(size_t) -> *mut libc::c_void`). Instead, replace them with safer alternatives where appropriate.\n\n"
    f"Example transformation:\n"
    f"```rust\n"
    f"pub malloc_func: Option<unsafe extern \"C\" fn(size_t) -> *mut libc::c_void>,\n"
    f"To:\n"
    f"pub malloc_func: Option<Box<dyn Fn(usize) -> Vec<u8>>>,\n"
    f"```\n\n"
    f"Do not use the following extern C functions: ({', '.join(functions_to_avoid)}).\n\n"
    f"Keep the typedef names unchanged, except for converting the usage of raw pointers to safer alternatives. Provide only the modified code between ```\n``` without any additional explanations.\n\n"
    f"```\n{typedef_code}\n```\n"
    )


    response = completion(
        model="gemini/gemini-pro", 
        messages=[{"role": "user", "content": prompt}]
    )
    response_content = response.choices[0].message.content

    safe_typedef_code = re.sub(r'^```[a-z]*\n|\n```$', '', response_content, flags=re.MULTILINE).strip()
    return safe_typedef_code

def convert_static_to_safe(static_code):
    """
    Converts the given Rust static variable and function declarations to a safer version that does not use raw pointers.
    """
    functions_context = functions_memory.load_memory_variables({"functions_to_avoid": ""})
    
    # Extract functions to avoid from history
    functions_to_avoid = []
    history = functions_context.get("history", "")
    match = re.search(r"Human: \[(.*?)\]", history)
    if match:
        functions_to_avoid = eval(f"[{match.group(1)}]")  # Safely evaluate to list
    
    prompt = (
        f"Rewrite the following Rust static variable declarations to eliminate the use of raw pointers (*const T, *mut T). "
        f"Replace them with safe Rust constructs like Box or Vec as appropriate while maintaining the same semantics.\n\n"
        f"Example transformation:\n"
        f"```rust\n"
        f"pub static mut foo: *mut libc::c_void = ptr::null_mut();\n"
        f"To:\n"
        f"pub static mut foo: Option<Box<[u8]>> = None;\n"
        f"```\n\n"
        f"Do not use the following extern C functions: ({', '.join(functions_to_avoid)}).\n\n"
        f"Provide only the modified code between ``` and ``` without any additional explanations.\n\n"
        f"```\n{static_code}\n```\n"
    )

    response = completion(
    model="gemini/gemini-pro", 
    messages=[{"role": "user", "content": prompt}]
    )
    # print(response)
    response_content = response.choices[0].message.content
    safe_static_code = re.sub(r'^```[a-z]*\n|\n```$', '', response_content, flags=re.MULTILINE).strip()

    # Check if the new static code still contains raw pointers
    if not contains_raw_pointers(safe_static_code):
        print("No raw pointers found, static conversion complete.")
        return safe_static_code

    # Update static_code with the new version for the next iteration
    static_code = safe_static_code

    return safe_static_code

def analyze_and_convert_functions(file_path, function_order):
    with open(file_path, 'r') as f:
        source_code = f.read()

    extern_c_functions = extract_extern_c_functions(source_code)
    # Save functions to avoid to memory
    functions_memory.save_context({"functions_to_avoid": extern_c_functions}, {"ignored_output": ""})

    updated_source_code = source_code

    struct_codes = extract_struct_code(updated_source_code)
    for struct_code in struct_codes:
        safe_struct_code = convert_structs_to_safe(struct_code)
        updated_source_code = updated_source_code.replace(struct_code, safe_struct_code)
     # Remove #[derive(Copy, Clone)] and #[repr(C)] from the source code before replacing it
    updated_source_code = re.sub(r'#\[derive\s*\(Copy,\s*Clone\)\]\s*', '', updated_source_code)
    updated_source_code = re.sub(r'#\[repr\s*\(C\)\]\s*', '', updated_source_code)
    with open(file_path, 'w') as f:
        f.write(updated_source_code)
    typedef_codes=extract_c_code_from_type_def("Decompositions/genann/application.json")
    for typedef_code in typedef_codes:
        print(typedef_code)
        safe_typedef_code = convert_typedef_to_safe(typedef_code)
        print(safe_typedef_code)
        updated_source_code = updated_source_code.replace(typedef_code, safe_typedef_code)
    with open(file_path, 'w') as f:
        f.write(updated_source_code)  

    static_declarations = parse_static_items(updated_source_code)

# Modify each static item and append it to the result
    for static_item in static_declarations:
        token_limit=3072
        fixed_blocks = []
        blocks = parse_and_chunk_code(static_item,7000)
        for block in blocks:
            modified_static_block = convert_static_to_safe(static_item)
            fixed_blocks.append(modified_static_block)
        modified_static_item = "\n".join(fixed_blocks)
        updated_source_code = updated_source_code.replace(static_item, modified_static_item)
    with open(file_path, 'w') as f:
        f.write(updated_source_code)

    # Function to extract `use` statements from the safe code and add them to the top of the file if missing
    def extract_and_add_use_statements(safe_code, source_code):
        # Find all `use` statements in the safe_code
        use_statements = re.findall(r'use\s+[^\s;]+{[^}]+}[^;]*;', safe_code)
        use_statements += re.findall(r'(use\s+[^\s;]+;)', safe_code)

        # Find the use statements that are missing from the source code
        use_statements_to_add = [use for use in use_statements if use not in source_code]
        print(use_statements_to_add)

        # Remove `use` statements from the safe_code
        safe_code_without_uses = re.sub(r'use\s+[^\s;]+{[^}]+}[^;]*;', '', safe_code)
        safe_code_without_uses = re.sub(r'(use\s+[^\s;]+;)', '', safe_code_without_uses)

        
        # Add missing `use` statements to the top of the source code
        if use_statements_to_add:
            source_code = "\n".join(use_statements_to_add) + "\n" + source_code
        
        return safe_code_without_uses, source_code

    for func_name in function_order:
        func_code = extract_function_code(updated_source_code, func_name)
        if func_code:
            if 'unsafe' in func_code:
                pdf_path = "Standard C Library Functions Table By Name - IBM Documentation.pdf"
                # Attempt to convert unsafe code to safe code
                safe_code = convert_unsafe_to_safe(func_code, pdf_path)

                if safe_code is not None:                    # Extract and move use statements to the top
                    safe_code, updated_source_code = extract_and_add_use_statements(safe_code, updated_source_code)
                    
                    # Replace the old function code with the new safe code
                    updated_source_code = updated_source_code.replace(func_code, safe_code)
                else:
                    print(f"Conversion failed for {func_name}. Keeping the original code.")
            
            # Write the updated source code back to the file immediately after processing each function
            with open(file_path, 'w') as f:
                f.write(updated_source_code)
        else:
            print(f"Function {func_name} not found in the source code.")

if __name__ == '__main__':
    arg_parser = argparse.ArgumentParser(description='Process a Rust file.')
    arg_parser.add_argument('rust_file_path', type=str, help='Path to the Rust file')
    arg_parser.add_argument('output_path', type=str, help='Path for the output file')

# Parse the arguments
    args = arg_parser.parse_args()
    function_order = analyze_rust_file(args.rust_file_path)
    print(function_order)
    analyze_and_convert_functions(args.rust_file_path, function_order)

