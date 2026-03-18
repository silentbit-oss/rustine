from tree_sitter import Language, Parser
import tree_sitter_rust
from collections import defaultdict
import sys
import os
import re
from litellm import completion
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
from utils import *
import time
import argparse

def code_partition(root):
    """
    input: code
    output:
    - head: dict, key is type, val is [[nodelist1],[nodelist2],...], nodelist is attribute_node + node
    - body: dict, key is type=='func', val is the same
    """
    head = defaultdict(list)
    body = defaultdict(list)
    for node in root.children:
        if node.type == "attribute_item":
            continue
        node_prev = node.prev_sibling
        cur_node_list = [node]
        while node_prev and node_prev.type == "attribute_item":
            cur_node_list = [node_prev] + cur_node_list
            node_prev = node_prev.prev_sibling
        # print(node.type)
        if node.type in [
            "use_declaration",
            "foreign_mod_item",
            "type_item",
            "enum_item",
            "struct_item",
            "static_item",
        ]:
            head[node.type].append(cur_node_list)
        elif node.type in ["function_item"]:
            body["function_item"].append(cur_node_list)
        else:
            raise Exception("node type not usual")
    sort_head = {
        i: head[i]
        for i in [
            "use_declaration",
            "foreign_mod_item",
            "type_item",
            "enum_item",
            "struct_item",
            "static_item",
        ]
    }
    return sort_head, body

def extract_extern_c(source_code):
    extracted_items = []
    # Match the extern "C" block
    pattern = r'extern "C" {([^}]*)}'
    match = re.search(pattern, source_code, re.MULTILINE | re.DOTALL)
    
    if match:
        extern_block = match.group(1)
        # Match both type and function declarations
        item_pattern = r'(pub type \w+;|fn\s+\w+\s*\([^)]*\)\s*->?\s*[^;]*;)'
        extracted_items = re.findall(item_pattern, extern_block)
    
    return extracted_items

def fix_extern_c(code, functions_to_avoid):
    prompt_step1 = (
        f"Rewrite the following Rust function code to eliminate the use of the following extern C functions or variables: "
        f"({', '.join(functions_to_avoid)}).\n\n"
        f"```\n{code}\n```\n\n"
        f"Provide only the converted Rust code for the specified function enclosed in triple backticks, "
        f"with absolutely no notes, explanations, or comments.\n```\n"
    )

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
    },
    ]
    )
    response_content = response.choices[0].message.content
    safe_code = re.sub(r'^```[a-z]*\n|\n```$', '', response_content, flags=re.MULTILINE).strip()
    return safe_code


def type_mapping(type_transpiler, item_type):
    """
    Map the transpiler type to the equivalent Rust type based on the item type.

    Args:
        type_transpiler (str): The type from the transpiler (e.g., C to Rust conversion).
        item_type (str): The item type ('struct', 'function', etc.).

    Returns:
        str: The mapped Rust type.
    """
    if item_type=="struct":
        prompt = (
        f"Rewrite the given Rust struct to replace all raw pointers (*const T, *mut T) and libc types with safer alternatives (e.g., Vec, Option, Box, or custom abstractions). Ensure the following:\n\n"
        f"- **Struct field names and general structure remain unchanged.**\n"
        f"- Avoid using raw pointers and `extern C` functions.\n"
        f"- If the declaration does not contain raw pointers, libc types, or `extern C` functions, do not modify it.\n"
        f"- Example type mapping:\n"
        f"  - `libc::c_int` → `i32`\n"
        f"  - `libc::c_uint` → `u32`\n"
        f"  - `libc::c_char` → `u8`\n"
        f"  - Dynamic arrays (`*T` pointing to memory eg. *mut libc::c_uchar, *mut libc::c_double) → `Vec<T>` \n"
        f"  - `*const T` → `&T`\n"
        f"  - `*mut T` → `&mut T`\n"
        f"  - Nullable `*const T` or `*mut T` → `Option<&T>` or `Option<&mut T>`\n"
        f"  - Fixed-size arrays `[T; N]` → Rust's `[T; N]`\n"
        f"  - `__off_t` or `__off64_t` → `i64`\n"
        f"  - `size_t` → `usize`\n"
        f"  - `*mut libc::c_void` → `Option<Box<[u8]>>` \n"
        f"  - Function pointers → `Box<dyn Fn>` or `Box<dyn FnMut>`\n"
        f"Provide only the modified struct code enclosed in triple backticks (` ``` `), without additional comments or explanations.\n\n"
        f"```\n{type_transpiler}\n```\n"
        )
        time.sleep(1)


        response = completion(
            model="gemini/gemini-pro", 
            messages=[{"role": "user", "content": prompt}]
        )
        response_content = response.choices[0].message.content


        safe_struct_code = re.sub(r'^```[a-z]*\n|\n```$', '', response_content, flags=re.MULTILINE).strip()

        type_rust=safe_struct_code

        
    else:
        type_rust=type_transpiler
    


    # Default mapping to itself if the type is not in the map
    return type_rust


def construct_struct(struct_node,extern_c):
    """
    input: struct root node
    output: modified struct code
    """
    # replace_field_decl = []
    # field_declaration_list = get_child_by_type(struct_node, "field_declaration_list")
    # for node in field_declaration_list.children:
    #     if node.type == "field_declaration":
    #         type_identifier = get_child_by_type(node, ":").next_sibling
    #         assert type_identifier != None
    #         modified_type = type_mapping(text(type_identifier),"struct")
    #         replace_field_decl.append(
    #             (
    #                 text(node),
    #                 text(node).replace(text(type_identifier), modified_type),
    #             )
    #         )
    # # replace
    # modified_code = text(struct_node)
    # for original_field_decl, modified_field_decl in replace_field_decl:
    #     print(modified_field_decl)
    #     modified_code = modified_code.replace(original_field_decl, modified_field_decl)
    # return modified_code
    original_code = text(struct_node)
    print("Original Struct Code:", original_code)
    
    modified_code = type_mapping(original_code, "struct")

    print("Modified Struct Code:", modified_code)
    # safe_code = fix_extern_c(modified_code,extern_c)
    # print("safe Struct Code:", safe_code)
    
    return modified_code

def construct_type_item(type_item_node):
    """
    input: type item root node
    output: modified type item code
    """
    original_type = text(type_item_node).split("=")[1].strip() #use all the text after "="
    modified_type = type_mapping(original_type,"type")
    return text(type_item_node).replace(original_type, modified_type)


def get_identifier(node, ids):
    """
    return all the identifier node in the node
    """
    if node.type == "identifier":
        ids.append(node)
        return ids
    for child in node.children:
        ids = get_identifier(child, ids)
    return ids


def get_global_var(root_node):
    """
    return list of variable names
    """
    var_list = []
    for node in root_node.children:
        if node.type == "static_item":
            var_name = text(get_child_by_type(node, "identifier"))
            var_list.append(var_name)
    return var_list


def analyze_variable(root_node):
    """
    input: root node
    output: var_used, key is function node, val is [var_name]
    """
    var_list = get_global_var(root_node)
    var_used = defaultdict(list)
    for child in root_node.children:
        ids = []
        ids = get_identifier(child, ids)
        ids = [text(identifier) for identifier in ids]
        for identifier in ids:
            if identifier in var_list and child.type != "static_item":
                # TODO: global variables will not be used in initialize other global variables' value?
                assert (
                    child.type == "function_item"
                ), f"only function can use variables {identifier}"
                var_used[child].append(identifier)

    return var_used


def construct_variable(var_node):
    """
    input: static item root node (global variable node)
    output:
    - modified variable code
    - variable info: live in which functions
    """
    code = text(var_node)
    scoped_type_identifier = get_child_by_type(var_node, ":").next_sibling
    modified_type = type_mapping(text(scoped_type_identifier),"variable")
    modified_type = f"Lazy<Mutex<{modified_type}>>"
    code = code.replace(text(scoped_type_identifier), modified_type)
    unary_expression = get_child_by_type(var_node, "=").next_sibling
    val = text(unary_expression)
    modified_val = f"Lazy::new(|| Mutex::new({val}))"
    code = code.replace(val, modified_val)
    if get_child_by_type(var_node, "mutable_specifier"):
        mut_flag = True
        code = code.replace("mut", "")
    var_name = text(get_child_by_type(var_node, "identifier"))
    var_rename = var_name.upper()
    code = code.replace(var_name, var_rename)
    return code


def construct_function(func_node, use_var):
    """
    input:
    - func_node: function node
    - use_var: variables used in this function node, list [var_name]
    output:
    modified function code
    """
    code = text(func_node)
    function_modifiers = get_child_by_type(func_node, "function_modifiers")
    if get_children_type(function_modifiers) == ["unsafe", "extern_modifier"]:
        code = code.replace(text(function_modifiers), "", 1)
    paras = get_child_by_type(func_node, "parameters")
    for node in paras.children:
        if node.type == "parameter":
            para_type = text(get_child_by_type(node, ":").next_sibling)
            modified_type = type_mapping(para_type,"parameter")
            modified_para = text(node).replace(para_type, modified_type)
            code = code.replace(text(node), modified_para)
    return_value = None
    if (
        get_child_by_type(func_node, "->")
        and get_child_by_type(func_node, "->").next_sibling
    ):
        original_result_type = text(get_child_by_type(func_node, "->").next_sibling)
        modified_result_type = type_mapping(original_result_type,"return_value")
        code = code.replace(original_result_type, modified_result_type)
        return_value = modified_result_type

    block = get_child_by_type(func_node, "block")
    unlock_var_code = ""
    use_var = list(dict.fromkeys(use_var))
    for var_name in use_var:
        unlock_var_code += f"let {var_name} = {var_name.upper()}.lock().unwrap();\n"
    if return_value:
        default_values = {
        "f64": "0.0",
        "i32": "0",
        "String": "String::new()",
        "bool": "false",  
        "usize": "0",     
        "libc::c_double":"0.0",
    }
        if return_value.startswith("*mut ") or return_value.startswith("*const "):
            return_stmt = "std::ptr::null_mut()"

        else:
            return_stmt = default_values.get(return_value, f"{return_value}::default()")

        unlock_var_code += f"return {return_stmt};\n"
    assert block != None
    code = code.replace(text(block), f"{{{unlock_var_code}}}\n")
    return code


def construct_skeleton(source_code, extern_c):
    parser = Parser()
    rust_language = Language(tree_sitter_rust.language())
    parser.language = rust_language
    tree = parser.parse(bytes(source_code, "utf8"))
    root = tree.root_node
    code = ""
    head, body = code_partition(root)
    for node_type, nodes in head.items():
        if nodes == []:
            continue
        if node_type == "use_declaration":
            for node_list in nodes:
                # keep
                for n in node_list:
                    code += text(n) + "\n"
            if head["static_item"] != []:
                # global variable exists
                code += "use once_cell::sync::Lazy;\nuse std::sync::Mutex;\n" # add it in cargo.toml
        if node_type == "foreign_mod_item":
            for node_list in nodes:
                for n in node_list:
                    for n in node_list:
                        code += text(n) + "\n"
        if node_type == "type_item":
            for node_list in nodes:
                for n in node_list:
                    if n.type != "attribute_item":
                        assert n.type == "type_item"
                        code += construct_type_item(n) + "\n"
                    else:
                        code += text(n) + "\n"
        if node_type == "struct_item":
            for node_list in nodes:
                for n in node_list:
                    if n.type != "attribute_item":
                        assert n.type == "struct_item"
                        code += construct_struct(n,extern_c) + "\n"
                    else:
                        code += text(n) + "\n"
        if node_type == "static_item":
            for node_list in nodes:
                for n in node_list:
                    if n.type != "attribute_item":
                        assert n.type == "static_item"
                        code += construct_variable(n) + "\n"
                        
                    else:
                        code += text(n) + "\n"

    var_used = analyze_variable(root)
    for node_type, nodes in body.items():
        assert node_type == "function_item"
        for node_list in nodes:
            for n in node_list:
                if n.type != "attribute_item":
                    assert n.type == "function_item"
                    var_func_used = var_used[n]
                    code += construct_function(n, var_func_used)
                else:
                    code += text(n) + "\n"
    return code


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process and transform Rust code.")
    parser.add_argument("--source", type=str, required=True, help="Path to the source Rust file")
    parser.add_argument("--output", type=str, required=True, help="Path to the output Rust file")
    
    args = parser.parse_args()

    source_file = args.source
    output_file = args.output


    with open(source_file) as f:
        source_code = f.read()

    extern_c = extract_extern_c(source_code)


    skeleton_code = construct_skeleton(source_code, extern_c)
    with open(output_file, "w") as f:
        f.write(skeleton_code)

