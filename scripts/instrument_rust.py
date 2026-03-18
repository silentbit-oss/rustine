import os
import sys
from tree_sitter import Language, Parser
import tree_sitter_rust

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

def main():
    """Walk through the project directory and process all .rs files."""
    args = sys.argv[1:]
    project_dir = args[0]

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

if __name__ == "__main__":
    main()
