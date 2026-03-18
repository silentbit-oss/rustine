from tree_sitter import Language, Parser
import os
import tree_sitter_rust
import subprocess
from graphviz import Digraph  # Import graphviz

# Build the Rust language library
parser = Parser()
rust_language = Language(tree_sitter_rust.language())
parser.language = rust_language 

def extract_functions_and_calls(source_code):
    """
    Parses the source code to extract function definitions and calls.
    Returns a dictionary where keys are function names and values are lists of functions they call.
    """
    tree = parser.parse(source_code.encode())
    root_node = tree.root_node
    functions = {}

    # Helper function to traverse the syntax tree
    def traverse(node, current_function=None):
        nonlocal functions

        if node.type == 'function_item' or node.type == 'method_item':
            # Extract function name
            func_name_node = node.child_by_field_name('name')
            if func_name_node:
                func_name = func_name_node.text.decode()
                if func_name not in functions:
                    functions[func_name] = []  # Initialize list of called functions

            # Traverse the function body to find calls
            for child in node.children:
                traverse(child, func_name)

        elif node.type == 'call_expression' and current_function:
            # Extract called function name
            func_call_node = node.child_by_field_name('function')
            if func_call_node and func_call_node.type == 'identifier':
                called_func_name = func_call_node.text.decode()
                if current_function not in functions:
                    functions[current_function] = []
                if called_func_name not in functions[current_function]:
                    functions[current_function].append(called_func_name)

        elif node.type in {'impl_item', 'mod_item', 'trait_item'}:
            # Traverse deeper into impl blocks, modules, or traits
            for child in node.children:
                traverse(child, current_function)

        else:
            # Continue traversing the tree
            for child in node.children:
                traverse(child, current_function)

    traverse(root_node)

    # Ensure all functions in the source code are included, even if they are not part of the call graph
    all_functions = {func_name_node.text.decode() for node in root_node.children 
                     if node.type in {'function_item', 'method_item'}
                     for func_name_node in [node.child_by_field_name('name')]
                     if func_name_node}
    
    for func in all_functions:
        if func not in functions:
            functions[func] = []  # Add functions without calls to the dictionary

    return functions

def generate_graph(functions):
    """
    Generates a Graphviz Digraph object from the call graph data.
    """
    dot = Digraph(comment='Call Graph')  # Create a Digraph object

    # Create nodes for each function
    for func in functions:
        dot.node(func, func)

    # Create directed edges for each function call
    for func, calls in functions.items():
        for called_func in calls:
            dot.edge(func, called_func)

    return dot

def write_graph_image(dot, output_path):
    """
    Writes the graph to an image file (e.g., PNG or SVG).
    """
    dot.render(output_path, format='png')

def analyze_rust_file(file_path):
    """
    Analyzes a Rust file, outputs the call graph as a PNG image,
    and outputs the recommended order of function repairs.
    """
    with open(file_path, 'r') as f:
        source_code = f.read()
        functions = extract_functions_and_calls(source_code)
        return functions
    
        

# Example usage
if __name__ == '__main__':
    rust_file_path = 'C2Rust/libcsv/src/libcsv.rs'  # Replace with the path to your Rust file
    graph_output_path = 'callgraph'  # Output path for the PNG image (without extension)
    
    analyze_rust_file(rust_file_path)
    # return functions
    # dot=generate_graph(functions)
    # write_graph_image(dot,graph_output_path)