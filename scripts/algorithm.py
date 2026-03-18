import os
import sys
import subprocess
from tree_sitter import Language, Parser
import tree_sitter_rust
from collections import Counter
from collections import defaultdict

def setup_parser():
    """Set up the tree-sitter parser for Rust."""
    parser = Parser()
    rust_language = Language(tree_sitter_rust.language())
    parser.language = rust_language
    return parser

def instrument_function(content, new_content_idx, node):
    """Add println! statement at the start of a function's block."""
    # Get the function name
    fn_name_node = node.child_by_field_name("name")
    if not fn_name_node:
        return new_content_idx, False
    fn_name = content[fn_name_node.start_byte+new_content_idx:fn_name_node.end_byte+new_content_idx].decode("utf-8")
    #print("func:", fn_name)

    # Get the function body (block)
    body_node = node.child_by_field_name("body")
    if not body_node or body_node.type != "block":
        return new_content_idx, False

    # Find the opening brace of the function body
    start_byte = body_node.start_byte+new_content_idx
    end_byte = body_node.end_byte+new_content_idx
    body_content = content[start_byte:end_byte].decode("utf-8")
    # Insert println! after the opening brace
    insert_pos = start_byte + 1  # After the '{'
    println_stmt = f'\n\tprintln!("* {fn_name}");'
    content = content[:insert_pos] + println_stmt.encode("utf-8") + content[insert_pos:]
    
    return content, new_content_idx+len(println_stmt.encode("utf-8")), True

def process_file(file_path, parser):
    """Process a single Rust file."""
    # Read the file
    with open(file_path, "rb") as f:
        content = f.read()

    # Parse the file
    tree = parser.parse(content)
    cursor = tree.walk()
    modified = False
    new_content_idx = 0

    # Traverse the AST to find function declarations
    def traverse(node):
        nonlocal new_content_idx, modified, content
        if node.type == "function_item":
            content, new_content_idx, was_modified = instrument_function(content, new_content_idx, node)
            if was_modified:
                modified = True
        for child in node.children:
            traverse(child)

    traverse(tree.root_node)

    if modified:
        # Write the modified content back to the file
        with open(file_path, "wb") as f:
            f.write(content)
        print(f"Modified {file_path}")

def suspiciousness_weighted_descending(input_dict,order):
    """
    Takes a dictionary with string keys (test names) and a list of tuples. The first tuple element is method that is executed prior to test/assertion failure and the next tuple element is the weight of method, depending on proximity to the failed assertion 
    dict[str, list[tuple[str, int]]]
    Returns the list of all methods that were executed by the failed tests before assertion, sorted by their aggregated weights (descending).
    """
    weight_map = defaultdict(int)

    # Aggregate weights
    for executed_methods in input_dict.values():
        for executed_method, weight in executed_methods:
            weight_map[executed_method] += weight

    if order == 'ascending':
        # Sort by total weight descending, then alphabetically
        suspicious_methods = sorted(weight_map.items(), key=lambda x: (x[1], x[0]))
        return suspicious_methods
        # Print result
        #print("Weight-based ranking ascending")
        #for method, total_weight in suspicious_methods:
        #    print(f"{method}: {total_weight}")
    else:
        # Sort by total weight descending, then alphabetically
        suspicious_methods = sorted(weight_map.items(), key=lambda x: (-x[1], x[0]))
        return suspicious_methods
        # Print result
        #print("Weight-based ranking descending")
        #for method, total_weight in suspicious_methods:
        #    print(f"{method}: {total_weight}")


def instrument(project_dir):
    if not os.path.isdir(project_dir):
        print("Invalid directory path!")
        return

    parser = setup_parser()

    for root, _, files in os.walk(project_dir):
        for file in files:
            if file.endswith(".rs"):
                file_path = os.path.join(root, file)
                print(f"Processing {file_path}")
                process_file(file_path, parser)

def build(project_dir):
    os.chdir(project_dir)
    subprocess.run(['cargo', 'build'], check=False)

def get_call_stack(exec_path):
    result = subprocess.run([exec_path], capture_output=True, text=True, check=False)
    output = result.stdout
    lines = output.strip().split('\n')
    call_stack = [line.lstrip('* ').strip() for line in lines if line.startswith('*')]
    return call_stack

def apply_algorithm(call_stack):
    result = []
    current_list = []
    for item in call_stack:
        if "test" in item:
            if current_list:
                result.append(current_list)
            current_list = [item]
        else:
            if current_list:
                current_list.append(item)
    
    if current_list:
        result.append(current_list)
    
    my_map = {item[0]: [(val, i) for i, val in enumerate(item[1:], start=1)] for item in result}
    result_weighted_descending = suspiciousness_weighted_descending(my_map,"descending")
    probably_correct = {item[0]: item[1:] for item in result}
    probably_correct.popitem()
    merged_list = []
    for value_list in probably_correct.values():
        merged_list.extend(value_list)
    merged_list = list(set(merged_list))
    
    modified_list = []
    for string, weight in result_weighted_descending:
        if string in merged_list:
            modified_list.append((string, max(weight - 1, 0)))
        else:
            modified_list.append((string, weight))
    return modified_list, probably_correct

def run():
    """Walk through the project directory and process all .rs files."""
    args = sys.argv[1:]
    project_dir = args[0]

    instrument(project_dir)
    build(project_dir)
    
    exec_path = "./target/debug/test"
    call_stack = get_call_stack(exec_path)
    weighted, probably_correct = apply_algorithm(call_stack)
    print(weighted)
    print("\n-------------\n")
    print(probably_correct)

if __name__ == "__main__":
    run()
