from tree_sitter import Language, Parser
import tree_sitter_rust

# Initialize the parser and language
parser = Parser()
rust_language = Language(tree_sitter_rust.language())
parser.language = rust_language

def get_node_text(node, code):
    """Returns the text content of a node."""
    start_byte = node.start_byte
    end_byte = node.end_byte
    return code[start_byte:end_byte].decode('utf-8')

def analyze_rust_code_for_raw_pointers(code):
    """Parses the Rust code and returns the total number of raw pointer occurrences."""
    # Ensure the code is a bytestring
    if not isinstance(code, bytes):
        code = code.encode('utf-8')

    # Parse the code
    tree = parser.parse(code)
    root_node = tree.root_node

    raw_pointer_count = 0  # Initialize the total count

    def recursive_analysis(node):
        nonlocal raw_pointer_count
        # Check for raw pointer declarations
        if node.type == 'pointer_type':
            pointer_text = get_node_text(node, code)
            if '*const' in pointer_text or '*mut' in pointer_text:
                raw_pointer_count += 1

        if node.type == 'unary_expression':
            # Iterate through child nodes to find dereference operators
            for child in node.children:
                child_text = get_node_text(child, code)
                if child_text == '*':  # This is the dereference operator
                    raw_pointer_count += 1

        # Recursively analyze child nodes
        for child in node.children:
            recursive_analysis(child)

    # Start recursive analysis from the root node
    recursive_analysis(root_node)
    return raw_pointer_count
def extract_function_calls(rust_code):
    """
    Extracts all function call names from the Rust code's syntax tree.
    """
    # Ensure the input is a bytestring
    if not isinstance(rust_code, bytes):
        rust_code = rust_code.encode('utf-8')

    # Parse the Rust code
    tree = parser.parse(rust_code)
    function_calls = []

    def visit_node(node):
        nonlocal function_calls
        if node.type == 'call_expression':
            function_name_node = node.child_by_field_name('function')
            if function_name_node:
                # Extract the function name using byte positions
                function_name = rust_code[function_name_node.start_byte:function_name_node.end_byte].decode('utf-8')
                function_calls.append(function_name)

        # Recursively visit children
        for child in node.children:
            visit_node(child)

    root_node = tree.root_node
    visit_node(root_node)
    return function_calls
def get_rust_function_definitions(source_code):
    """
    Extracts function definition names from the given Rust source code.

    Args:
        source_code (str): The Rust source code as a string.

    Returns:
        list: A list of function names found in the source code.
    """


    # Parse the source code
    tree = parser.parse(bytes(source_code, 'utf-8'))
    function_names = []

    def traverse_tree(node):
        if node.type == 'function_item':
            # Extract the function name
            function_name_node = node.child_by_field_name('name')
            if function_name_node:
                function_name = source_code[function_name_node.start_byte:function_name_node.end_byte]
                function_names.append(function_name)
        # Recursively visit children nodes
        for child in node.children:
            traverse_tree(child)

    # Start traversing from the root node
    root_node = tree.root_node
    traverse_tree(root_node)

    return function_names
# Example Rust code
rust_code = b'''
fn main() {
    let raw_ptr: *const i32;
    unsafe {
        let val = *raw_ptr;  
    }
}
'''

# Analyze the code and print the result

