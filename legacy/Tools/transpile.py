import subprocess
import os
import argparse
from tree_sitter import Language, Parser
import tree_sitter_rust
from typing import List, Dict, Set, Tuple
from dataclasses import dataclass
import re
import sys
import json

class FusedNode:
    """A simple wrapper class to represent a fused node."""
    def __init__(self, start_byte, end_byte, parent, text, chunk_identifier = ""):
        self.start_byte = start_byte
        self.end_byte = end_byte
        self.parent = parent
        self.text = text
        self.chunk_identifier = chunk_identifier

    def to_dict(self):
        """Convert the FusedNode instance to a dictionary."""
        return {
            "start_byte": self.start_byte,
            "end_byte": self.end_byte,
            "parent": self.parent.type,
            "text": self.text,
            "chunk_identifier": self.chunk_identifier
        }

def get_node_text(node, source_code):
    """Helper function to get the text represented by a node."""
    return source_code[node.start_byte:node.end_byte]

def write_chunks_to_json(marked_chunks, filename="chunks.json"):
    """Convert marked_chunks to JSON and write to a file."""
    # Convert each FusedNode in marked_chunks to a dictionary
    chunks_as_dict = [chunk.to_dict() for chunk in marked_chunks]

    # Write the array of chunk dictionaries to a JSON file
    with open(filename, "w", encoding="utf-8") as f:
        json.dump(chunks_as_dict, f, indent=4, ensure_ascii=False)


def collect_leaf_nodes(node):
    """Collect all leaf nodes in the parse tree."""
    leaf_nodes = []
    if len(node.children) == 0:  # Leaf node
        leaf_nodes.append(node)
    else:
        for child in node.children:
            leaf_nodes.extend(collect_leaf_nodes(child))
    return leaf_nodes

def aggregate_non_overlapping_chunks(nodes, source_code, context_limit):
    """Recursively aggregate nodes from leaf to root as non-overlapping chunks."""
    parent_nodes = []  # Final list of non-overlapping parent nodes

    def process_nodes(node_array):
        nonlocal parent_nodes
        next_level_nodes = []  # Track parent nodes for the next recursion level

        for node in node_array:
            # Skip if this node is already covered by the last node in parent_nodes
            if parent_nodes and node.end_byte <= parent_nodes[-1].end_byte:
                continue
            
            if node.type == "function_item" and len(get_node_text(node)) <= context_limit:
                parent_nodes.append(node)
                continue
            # Check the parent's length first if it exists
            parent = node.parent
            if parent:
                parent_text = get_node_text(parent, source_code)
                
                # Check if the parent fits within the context limit and is more inclusive
                if len(parent_text) <= context_limit:
                    # Check if it fully includes the last node in parent_nodes
                    if parent_nodes and parent.start_byte <= parent_nodes[-1].start_byte and parent.end_byte >= parent_nodes[-1].end_byte:
                        # Replace the last node with this more inclusive parent
                        parent_nodes[-1] = parent
                        continue  # Move to the next node since we included the parent
                    
                    # If the parent is not overlapping, add it to parent nodes
                    parent_nodes.append(parent)
                    continue  # Move to the next node since we included the parent

            # If the parent does not fit or doesn't exist, add the current node itself
            node_text = get_node_text(node, source_code)
            if len(node_text) <= context_limit:
                parent_nodes.append(node)
            # elif parent:
            #     # If the current node doesn’t fit but has a parent, add the parent to the next level
            #     next_level_nodes.append(parent)

        # Recur on the next level nodes if they exist
        if next_level_nodes:
            process_nodes(next_level_nodes)

    # Start processing from the initial array of leaf nodes
    process_nodes(nodes)

    return parent_nodes

def is_half_parenthesis(node_text):
    """Check if the node contains only a half parenthesis character."""
    return node_text in {"(", ")", "[", "]", "{", "}"}

def fuse_nodes_with_same_parent(nodes: List, source_code: str, context_limit: int):
    """Fuse nodes in the array that share the same parent by only adjusting start and end byte, respecting context_limit."""
    fused_nodes = []
    i = 0

    while i < len(nodes):
        node = nodes[i]
        parent = node.parent

        # Collect all consecutive nodes with the same parent
        siblings = [node]
        while i + 1 < len(nodes) and (nodes[i + 1].parent == parent):
            siblings.append(nodes[i + 1])
            i += 1

        # print("=" * 40, "\n")
        # print(get_node_text(node, source_code))
        # print(siblings)
        # print("\n","=" * 40, "\n")
        # Process siblings to create fused nodes within the context limit
        start_index = 0
        while start_index < len(siblings):
            # Initialize the starting byte range of the new fused node
            start_byte = siblings[start_index].start_byte
            end_byte = siblings[start_index].end_byte
            j = start_index + 1

            # Attempt to fuse as many siblings as possible within the context limit
            while j < len(siblings):
                sibling = siblings[j]
                sibling_text = get_node_text(sibling, source_code)

                # Check if adding this sibling would exceed the context limit
                if (end_byte - start_byte) + (sibling.end_byte - sibling.start_byte) > context_limit:
                    break

                # Handle half-parenthesis cases
                fused_text = source_code[start_byte:end_byte]
                if is_half_parenthesis(fused_text) or is_half_parenthesis(sibling_text):
                    # If a node contains a half-parenthesis, ensure it has a matching pair within the limit
                    if not ((fused_text == "(" and sibling_text == ")") or
                            (fused_text == "[" and sibling_text == "]") or
                            (fused_text == "{" and sibling_text == "}") or
                            (fused_text == ")" and sibling_text == "(") or
                            (fused_text == "]" and sibling_text == "[") or
                            (fused_text == "}" and sibling_text == "{")):
                        # Stop fusing if no matching pair found within the context limit
                        break

                # Extend the end byte to include the current sibling
                end_byte = sibling.end_byte
                j += 1

            # Create the fused node and add it to the fused_nodes list
            fused_node_text = source_code[start_byte:end_byte]
            fused_node = FusedNode(start_byte=start_byte, end_byte=end_byte, parent=parent, text=fused_node_text)
            fused_nodes.append(fused_node)

            # Move to the next set of siblings that couldn't be included in the current fused node
            start_index = j

        i += 1  # Move to the next node outside the sibling group

    return fused_nodes

def mark_chunks_with_identifiers(fused_nodes: List[FusedNode], root_node, source_code: str):
    """
    Mark each chunk in `fused_nodes` with a unique chunk identifier based on depth in the parse tree.
    """
    
    NEW_LEVEL_BLOCKS = {'function_item', 'if_expression', 'while_expression', 'for_expression', 'loop_expression', 'match_expression', 'match_arm', 'else_clause'}
    
    # Helper function to find the depth of each chunk
    def calculate_chunk_depth(chunk, node):
        depth = 1
        # Traverse the tree from the root node down to the smallest node containing the chunk
        while node:
            # If the node fully contains the chunk
            if node.start_byte <= chunk.start_byte and node.end_byte >= chunk.end_byte:
                # Increase depth only if we encounter a block within a NEW_LEVEL_BLOCK or else_clause that fully contains the chunk
                if node.type in NEW_LEVEL_BLOCKS:
                    # Find the block child that fully contains the chunk
                    block_node = next((child for child in node.children 
                                       if (child.type == 'block' or  child.type == 'match_block') and 
                                       child.start_byte <= chunk.start_byte and 
                                       child.end_byte >= chunk.end_byte), None)
                    if block_node:
                        depth += 1
                        node = block_node  # Move to the block node for further depth calculation
                        continue
                # Traverse into children to find a smaller containing node
                for child in node.children:
                    if child.start_byte <= chunk.start_byte and child.end_byte >= chunk.end_byte:
                        node = child
                        break
                else:
                    break  # No smaller node found, break out
            else:
                break
        return depth

    # Calculate depth for each chunk
    for chunk in fused_nodes:
        chunk.depth = calculate_chunk_depth(chunk, root_node)

    # Generate identifiers based on depth and sequence
    last_depths = []  # Track identifiers at each depth level

    for chunk in fused_nodes:
        # Adjust the last_depths list to match the current chunk's depth
        if len(last_depths) < chunk.depth:
            last_depths.append(1)
        elif len(last_depths) == chunk.depth:
            last_depths[-1] += 1
        else:
            # Truncate last_depths to the current depth and increment
            last_depths = last_depths[:chunk.depth]
            last_depths[-1] += 1

        # Assign the identifier based on the last_depths list
        chunk.chunk_identifier = '-'.join(map(str, last_depths))

    return fused_nodes

def run_command(command, output_file, cwd=None):
    try:
        with open(output_file, 'w') as file:
            result = subprocess.run(command, shell=True, check=True, stdout=file, stderr=file, cwd=cwd)
    except subprocess.CalledProcessError as e:
        with open(output_file, 'a') as file:
            file.write(f"\nError occurred while running command: {str(e)}")


def main(folder, transpile_dir, cw, build_output_file, run_output_file):
    project_path = os.path.join(os.getcwd(), folder)
    compile_output_path = os.path.join(project_path, "command_output.log")

    if folder == "Subjects/libcsv":
        bear_command = "bear -- make check"
        binary_name = "test_csv"
    elif folder == "Subjects/genann" or folder == "Subjects/url_parser":
        bear_command = "bear -- make"
        binary_name = "test"
    else:
        with open(compile_output_path, 'a') as file:
            file.write(f"Error: No specific command configured for folder: {folder}\n")
        print(f"Error: No specific command configured for folder: {folder}")
        return

    print(f"Running bear command for {folder}...")
    run_command(bear_command, compile_output_path, cwd=project_path)

    compile_commands_path = os.path.join(project_path, "compile_commands.json")
    if not os.path.isfile(compile_commands_path):
        with open(compile_output_path, 'a') as file:
            file.write("Error: compile_commands.json not found. Please check the bear command and Makefile.\n")
        print("Error: compile_commands.json not found. Please check the bear command and Makefile.")
    else:
        folder_name = folder.split('/')[-1]
        if not os.path.exists(transpile_dir):
            os.makedirs(transpile_dir)
        relative_transpile_dir = os.path.relpath(transpile_dir, start=project_path)

        print("Running c2rust transpile command")
        c2rust_command = f"c2rust transpile --emit-build-files --binary {binary_name} --output-dir {relative_transpile_dir} compile_commands.json"
        run_command(c2rust_command, compile_output_path, cwd=project_path)

        print(f"Running cargo build in {transpile_dir} and saving result to {build_output_file}")
        cargo_build_command = "cargo build"
        run_command(cargo_build_command, build_output_file, cwd=transpile_dir)

        print(f"Running cargo run in {transpile_dir} and saving result to {run_output_file}")
        cargo_run_command = "cargo run"
        run_command(cargo_run_command, run_output_file, cwd=transpile_dir)

        print(f"Files moved successfully to Rust directory at {transpile_dir}.")
    run_command("make clean", compile_output_path, cwd=project_path)

    parser = Parser()
    rust_language = Language(tree_sitter_rust.language())
    parser.language = rust_language 

    src_dir = os.path.join(transpile_dir, "src")
    for root, _, files in os.walk(src_dir):
        for file in files:
            if file.endswith(".rs"):
                # Construct the full path to the .rs file
                file_path = os.path.join(root, file)
                
                # Read the source code from the file
                with open(file_path, 'r', encoding='utf-8') as f:
                    source_code = f.read()
                
                # Run the tree-sitter parser on the source code
                tree = parser.parse(bytes(source_code, "utf8"))
                root_node = tree.root_node

                # Step 1: Collect all leaf nodes
                leaf_nodes = collect_leaf_nodes(root_node)

                # Step 2: Aggregate into non-overlapping parent nodes recursively
                aggregated_chunks = aggregate_non_overlapping_chunks(leaf_nodes, source_code, cw)

                # Step 3: Fuse nodes with the same parent within the context limit
                fused_chunks = fuse_nodes_with_same_parent(aggregated_chunks, source_code, cw)

                # Step 4: Mark each chunk with a unique identifier
                marked_chunks = mark_chunks_with_identifiers(fused_chunks, root_node, source_code)

                # Define the output JSON filename (same name as .rs file, but with .json extension)
                json_filename = os.path.splitext(file)[0] + ".json"
                json_file_path = os.path.join(root, json_filename)

                # Write chunks to JSON file
                write_chunks_to_json(marked_chunks, json_file_path)

                print(f"Processed {file_path} -> {json_file_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Process folder for transpilation and build.')
    parser.add_argument('--c', type=str, required=True, help='The folder name')
    parser.add_argument('--transpile', type=str, required=True, help='Directory for C2Rust transpiled files')
    parser.add_argument('--cw', type=int, required=False, help='context window for the chunks to fit into')
    parser.add_argument('--compile_output', type=str, required=True, help='File to save cargo build results')
    parser.add_argument('--build_output', type=str, required=True, help='File to save cargo run results')
    args = parser.parse_args()
    main(args.c, args.transpile, args.cw, args.compile_output, args.build_output)
