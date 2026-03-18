import os
import re
from tree_sitter import Language, Parser
import tree_sitter_rust

# Initialize Tree-sitter for Rust language
parser = Parser()
rust_language = Language(tree_sitter_rust.language())
parser.language = rust_language 

def find_rust_code(c_name, rust_project_path, item_type):
    """
    Generalized function to find Rust code (functions, structs, fields) by item name.
    """
    c_name = clean_c_name(c_name, item_type)
    
    for root, _, files in os.walk(rust_project_path):
        for file in files:
            if file.endswith('.rs'):
                rust_file_path = os.path.join(root, file)
                with open(rust_file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    rust_code_content = f.read()

                tree = parser.parse(bytes(rust_code_content, 'utf8'))
                root_node = tree.root_node

                # Match the desired item (function, struct, field)
                matched_code = extract_rust_item(root_node, c_name, rust_code_content, item_type)
                if matched_code:
                    # Return both the matched code and the file path
                    return matched_code, rust_file_path

    return None, None


def clean_c_name(c_name, item_type):
    """
    Clean the C name based on item type (function, struct, field).
    """
    if item_type == 'struct_item':
        c_name = re.sub(r'[\(\{].*$', '', c_name).strip()
        c_name = re.sub(r'[^\w\s]', '', c_name).strip()
        # For structs, remove curly braces and special characters.
        return re.sub(r'[^\w\s]', '', re.sub(r'[\(\{].*$', '', c_name).strip())
    elif item_type == 'field_declaration':
        # For fields, simplify by removing unnecessary symbols.
        return re.sub(r'[^\w\s]', '', re.sub(r'\)\s*\(.*?\)', ')', c_name).strip())
    elif item_type == 'type_item':
        # For fields, simplify by removing unnecessary symbols.
        return re.sub(r'[^\w\s]', '', re.sub(r'\)\s*\(.*?\)', ')', c_name).strip())
    return c_name

def extract_rust_item(node, c_name, rust_code_content, item_type):
    """
    Generalized function to extract Rust code items (function, struct, field) from AST nodes.
    """
    if node.type == item_type:
        identifier_node = node.child_by_field_name('name')
        if identifier_node:
            rust_name = rust_code_content[identifier_node.start_byte:identifier_node.end_byte]
            if c_name in rust_name:
                return rust_code_content[node.start_byte:node.end_byte].strip()

    for child in node.children:
        result = extract_rust_item(child, c_name, rust_code_content, item_type)
        if result:
            return result

    return None

def find_rust_function(c_function_name, rust_project_path):
    """
    Find the Rust function corresponding to the C function name.
    """
    return find_rust_code(c_function_name, rust_project_path, 'function_item')

def find_rust_struct(c_struct_name, rust_project_path):
    """
    Find the Rust struct corresponding to the C struct name.
    """
    return find_rust_code(c_struct_name, rust_project_path, 'struct_item')

def find_rust_field(c_field_name, rust_project_path):
    """
    Find the Rust field corresponding to the C field name.
    """
    return find_rust_code(c_field_name, rust_project_path, 'field_declaration')

def find_rust_typedef(c_field_name, rust_project_path):
    """
    Find the Rust field corresponding to the C field name.
    """
    return find_rust_code(c_field_name, rust_project_path, 'type_item')
