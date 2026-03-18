import os
import json
import argparse
from tree_sitter import Language, Parser
import tree_sitter_c
import tree_sitter_rust
import re
from decompose_rust import find_rust_function, find_rust_struct, find_rust_field
from decompose_c import analyze_project
from c_cfg import cfg_gen
# Define project files with their source and test files
project_files = {
    'Subjects/genann': {
        'source_files': ['genann.c', 'genann.h'],
        'test_files': ['test.c']
    },
    'Subjects/libcsv': {
        'source_files': ['libcsv.c', 'csv.h'],
        'test_files': ['test_csv.c']
    },
    'Subjects/url_parser': {
        'source_files': ['gen_char_category_table.c', 'url_char_category.h', 'url.c', 'url.h'],
        'test_files': ['test.c']
    },
    # Add more projects and their associated files as needed
}

# Paths for the language library and grammar
parser = Parser()
c_language = Language(tree_sitter_c.language())
parser.language = c_language


def parse_call_graph(call_graph_text):
    """
    Parse a call graph text to extract caller-callee relationships.
    Returns a dictionary where each function has lists of 'callers' and 'callees'.
    """
    graph = {}
    lines = call_graph_text.strip().splitlines()

    for line in lines:
        # Match edges like 'caller -> callee'
        match = re.match(r'\s*(\w+)\s*->\s*(\w+)', line)
        if match:
            caller, callee = match.groups()
            if caller not in graph:
                graph[caller] = {'callers': [], 'callees': []}
            if callee not in graph:
                graph[callee] = {'callers': [], 'callees': []}

            # Add caller-callee relationship
            graph[caller]['callees'].append(callee)
            graph[callee]['callers'].append(caller)

    return graph


def parse_c_project(project_path, cfg_path, rust_project_path, call_graph_text, project_files):
    call_graph = parse_call_graph(call_graph_text)
    # Define the specific files (both source and test) for each project

    fragments = []

    # Check if the given project path has predefined files
    if project_path in project_files:
        files_to_parse = project_files[project_path]['source_files']
        test_files = project_files[project_path]['test_files']
    else:
        raise ValueError(f"No predefined files for project: {project_path}")

    # Loop through the predefined source files for the project
    for root, _, files in os.walk(project_path):
        for file in files:
            if file in files_to_parse:  # Only process the predefined source files
                file_path = os.path.join(root, file)

                # Open and read the file
                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    code = f.read()

                # Parse the code using the parser
                tree = parser.parse(bytes(code, 'utf8'))
                root_node = tree.root_node

                # Extract fragments from the parsed tree and analyze test invocations
                fragments.extend(extract_fragments(
                    root_node, file_path, code, project_path, test_files, rust_project_path, call_graph, cfg_path))

    return fragments


def get_name(function_def_node):
    declarator_node = function_def_node.child_by_field_name("declarator")

    # Traverse to the nested declarator to find the identifier
    while declarator_node:
        # Check if the current node is an identifier
        if declarator_node.type == "identifier":
            return declarator_node.text.decode("utf-8")
        # Otherwise, move to the child declarator
        declarator_node = declarator_node.child_by_field_name("declarator")

    return None  # Return None if identifier is not found


def extract_fragments(node, file_path, code, project_path, test_files, rust_project_path, call_graph, cfg_path):
    fragments = []

    if node.type == 'function_definition' or node.type == 'method_definition':
        # Get the full content of the function
        function_content = code[node.start_byte:node.end_byte].strip()

        start_byte = node.start_byte
        while start_byte > 0 and (code[start_byte - 1] == ' ' or code[start_byte - 1] == '\n'):
            start_byte -= 1

        while start_byte > 0 and code[start_byte - 1].isalpha():
            start_byte -= 1

        function_content = code[start_byte:node.end_byte].strip()

        function_name = get_name(node)
        # Look for invocations in the test files
        invocations = []
        for test_file in test_files:
            # Construct full test file path
            test_file_path = os.path.join(project_path, test_file)

            # Open and read the test file
            with open(test_file_path, 'r', encoding='utf-8', errors='ignore') as test_f:
                test_code = test_f.read()

            # Find invocations in the test file
            invocations.extend(find_test_invocations(
                function_name, test_code, test_file_path))

        # Find corresponding Rust function code
        rust_code = find_rust_function(function_name, rust_project_path)
        # Remove duplicates
        callers = list(
            set(call_graph.get(function_name, {}).get('callers', [])))
        # Remove duplicates
        callees = list(
            set(call_graph.get(function_name, {}).get('callees', [])))
        cfg_path = cfg_gen(function_name, node.text.decode('utf-8'), cfg_path)
        fragments.append({
            'path': file_path,
            'fragment_type': 'Function',
            'c_code': function_content,  # Store full content instead of just the name
            'test_invocations': invocations,  # Store test invocations
            'transpilation': rust_code,  # Store the Rust equivalent code
            'callers': callers,  # Add callers
            'callees': callees,   # Add callees
            'cfg': cfg_path  # Add cfg for this function
        })

    elif node.type == 'struct_specifier':
        # Get the full content of the struct
        start_byte = node.start_byte
        while start_byte > 0 and (code[start_byte - 1] == ' ' or code[start_byte - 1] == '\n'):
            start_byte -= 1

        while start_byte > 0 and code[start_byte - 1].isalpha():
            start_byte -= 1

        struct_content = code[start_byte:node.end_byte].strip()
        type_id_node = node.child_by_field_name('name')
        if type_id_node:
            struct_name = code[type_id_node.start_byte:type_id_node.end_byte]
        body_node = node.child_by_field_name('body')
        rust_struct = find_rust_struct(struct_name, rust_project_path)
        if body_node is not None:
            fragments.append({
                'path': file_path,
                'fragment_type': 'Struct',
                'c_code': struct_content,  # Store full content of the struct
                'transpilation': rust_struct
            })
        # Extract fields inside the struct
        field_nodes = node.child_by_field_name('body')
        if field_nodes:
            for field in field_nodes.named_children:
                if field.type == 'field_declaration':
                    start_byte = field.start_byte
                    while start_byte > 0 and (code[start_byte - 1] == ' ' or code[start_byte - 1] == '\n'):
                        start_byte -= 1

                    while start_byte > 0 and code[start_byte - 1].isalnum():
                        start_byte -= 1
                    field_content = code[start_byte:field.end_byte].strip()
                    declarator = field.child_by_field_name('declarator')
                    if declarator:
                        field_name = code[declarator.start_byte:declarator.end_byte]
                    rust_field_content = find_rust_field(
                        field_name, rust_project_path)
                    fragments.append({
                        'path': file_path,
                        'fragment_type': 'Field',
                        'c_code': field_content,  # Store full content of the field
                        'transpilation': rust_field_content
                    })

    # Recursively check children nodes
    else:
        for child in node.children:
            fragments.extend(extract_fragments(
                child, file_path, code, project_path, test_files, rust_project_path, call_graph, cfg_path))

    return fragments


def find_test_invocations(fragment_name, test_code, test_file_path):
    invocations = []

    # Step 2: Parse the test code with Tree-sitter
    tree1 = parser.parse(bytes(test_code, "utf8"))
    root_node = tree1.root_node

    # Step 3: Traverse the AST to find all function definitions
    for function_node in root_node.children:
        if function_node.type == 'function_definition':
            # Extract the function name (from the 'declarator' field)

            function_name = get_name(function_node)
            # print(f"Found function: {function_name}")

            # Extract the function body (from the 'body' field)
            function_body_node = function_node.child_by_field_name('body')
            function_body = test_code[function_body_node.start_byte:function_body_node.end_byte]
            # print(f"Function body: {function_body}")

            # Step 4: Check if the function body contains an invocation of the cleaned fragment name
            if fragment_name in function_body:
                # print(f"Function {function_name} calls {cleaned_fragment_name}")
                invocations.append({
                    'test_file': test_file_path,
                    'test_function': function_name
                })

    return invocations


def get_corresponding_rust_path(c_file_path):
    # Get the project name from the C project path
    project_name = os.path.basename(os.path.dirname(c_file_path))

    # Construct the path to the corresponding Rust file
    c_file_name = os.path.basename(c_file_path)
    rust_file_name = os.path.splitext(c_file_name)[0] + ".rs"

    # Construct the full path to the Rust file
    rust_base_path = os.path.join("C2Rust", project_name, "src")
    rust_path = os.path.join(rust_base_path, rust_file_name)

    return rust_path if os.path.exists(rust_path) else None


def parse_c_file(file_path):
    parser = Parser()
    c_language = Language(tree_sitter_c.language())
    parser.language = c_language

    with open(file_path, 'r') as f:
        source_code = f.read()

    tree = parser.parse(bytes(source_code, 'utf8'))
    return tree, source_code


def parse_rust_file(file_path):
    parser = Parser()
    rust_language = Language(tree_sitter_rust.language())
    parser.language = rust_language

    with open(file_path, 'r') as f:
        source_code = f.read()

    tree = parser.parse(bytes(source_code, 'utf8'))
    return tree, source_code


def find_rust_fragment(rust_tree, rust_source_code, c_fragment_name):
    cursor = rust_tree.walk()

    def traverse(cursor):
        node = cursor.node

        # Check if this node contains the C fragment name
        node_text = rust_source_code[node.start_byte:node.end_byte]
        if c_fragment_name in node_text:
            # If it's a function, struct, or field definition, return the whole node
            if node.type in ["function_item", "struct_item", "field_declaration"]:
                return node_text.strip()

        # Recurse through children
        if cursor.goto_first_child():
            result = traverse(cursor)
            cursor.goto_parent()
            if result:
                return result

        if cursor.goto_next_sibling():
            result = traverse(cursor)
            if result:
                return result

        return None

    return traverse(cursor)


def extract_code_fragments(tree, source_code, file_path):
    fragments = []
    cursor = tree.walk()

    # Parse corresponding Rust file if it exists
    rust_path = get_corresponding_rust_path(file_path)
    rust_tree = None
    rust_source_code = None
    if rust_path:
        try:
            rust_tree, rust_source_code = parse_rust_file(rust_path)
        except FileNotFoundError:
            pass

    def traverse(cursor):
        node = cursor.node
        node_type = node.type
        fragment_name = None
        fragment_type = None

        if node_type == "struct_specifier":
            for child in node.children:
                if child.type == "type_identifier":
                    fragment_name = source_code[child.start_byte:child.end_byte]
                    fragment_type = "Struct"
                    break

        elif node_type == "function_definition":
            declarator = node.child_by_field_name('declarator')
            if declarator:
                for child in declarator.children:
                    if child.type == "identifier":
                        fragment_name = source_code[child.start_byte:child.end_byte]
                        break

            if fragment_name:
                function_body_node = node.child_by_field_name('body')
                function_body_text = source_code[function_body_node.start_byte:function_body_node.end_byte]

                test_indicators = ["test", "assert",
                                   "expect", "check", "verify"]
                if any(indicator in fragment_name.lower() for indicator in test_indicators) or \
                   any(indicator in function_body_text.lower() for indicator in test_indicators):
                    fragment_type = "Test"
                else:
                    fragment_type = "Helper Method"

        elif node_type == "field_declaration":
            declarator = node.child_by_field_name('declarator')
            if declarator:
                fragment_name = source_code[declarator.start_byte:declarator.end_byte]
                fragment_type = "Field"

        if fragment_name and fragment_type:
            # Find corresponding Rust code if available
            rust_code = None
            if rust_tree and rust_source_code:
                rust_code = find_rust_fragment(
                    rust_tree, rust_source_code, fragment_name)

            fragments.append({
                "file_path": file_path,
                "class": os.path.basename(file_path),
                "fragment_name": fragment_name,
                "fragment_type": fragment_type,
                "c_code": source_code[node.start_byte:node.end_byte].strip(),
                "transpilation": rust_code if rust_code else None,
                "rust_file": rust_path if rust_path else None
            })

        if cursor.goto_first_child():
            traverse(cursor)
            cursor.goto_parent()

        if cursor.goto_next_sibling():
            traverse(cursor)

    traverse(cursor)
    return fragments


def find_test_files(directory):
    test_files = []
    for root, _, files in os.walk(directory):
        if "example" not in root.lower():
            for file in files:
                if file.endswith(".c") and "test" in file.lower() and "example" not in file.lower():
                    test_files.append(os.path.join(root, file))
    return test_files


def test(c_project_dir, output_json_path):
    all_fragments = []

    # Find all test files
    test_files = find_test_files(c_project_dir)

    # Extract fragments from each test file
    for test_file in test_files:
        tree, source_code = parse_c_file(test_file)
        fragments = extract_code_fragments(tree, source_code, test_file)
        all_fragments.extend(fragments)

    # Write the fragments to the output JSON file
    with open(output_json_path, 'w') as json_file:
        json.dump(all_fragments, json_file, indent=4)


def c_structure(c_project_dir, output_json_path):
    # Fetch the source files for the specified project directory
    files_info = project_files.get(c_project_dir)
    if not files_info:
        raise ValueError(
            f"No files found for project directory: {c_project_dir}")

    # Build full paths for source files in the specified project directory
    source_file_paths = [os.path.join(c_project_dir, file)
                         for file in files_info['source_files']]

    # Call analyze_project with the list of source file paths and the output JSON path
    analyze_project(source_file_paths, output_path=output_json_path)


def main():
    parser = argparse.ArgumentParser(
        description='Decompose C project into fragments and find test invocations.')
    parser.add_argument('--c', dest='c_project_path',
                        required=True, help='Path to the C project')
    parser.add_argument('--app', dest='app_output_path',
                        required=True, help='Output JSON file for application code')
    parser.add_argument('--transpilation', dest='rust_project_path',
                        required=True, help='Path to the Rust project')
    parser.add_argument("--test", required=True, help="Output JSON file path.")
    parser.add_argument('--structure', required=True,
                        help="Output JSON file path.")
    parser.add_argument('--cfg', dest='cfg_path', required=True,
                        help="Output CFG file directory path")

    args = parser.parse_args()
    print(args.c_project_path)
    project_name = os.path.basename(args.c_project_path)
    print(project_name)
    call_graph_path = f"call_graph/{project_name}"
    with open(call_graph_path, 'r') as cg_file:
        call_graph_text = cg_file.read()
    os.makedirs(args.cfg_path, exist_ok=True)
    fragments = parse_c_project(
        args.c_project_path, args.cfg_path, args.rust_project_path, call_graph_text, project_files)

    # Save the fragments into the application JSON file
    os.makedirs(os.path.dirname(args.app_output_path), exist_ok=True)
    with open(args.app_output_path, 'w', encoding='utf-8') as f:
        json.dump(fragments, f, indent=4)

    test(args.c_project_path, args.test)

    c_structure(args.c_project_path, args.structure)


if __name__ == '__main__':
    main()