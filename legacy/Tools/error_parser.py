import re
import os
from typing import Generator
from collections import defaultdict
import pandas as pd
from concurrent.futures import ThreadPoolExecutor
from tree_sitter import Language, Parser, Tree, Node
import tree_sitter_rust as language_rust
import argparse


def count_errors_by_class(log):
    error_positions = defaultdict(list)

    current_error = None
    error_start_regex = re.compile(r'^error\[')
    position_regex = re.compile(r'\s+--> (.+?).rs:(\d+):(\d+)')
    err_line = 1
    for line in log.splitlines():
        # Check if the line indicates an error
        if error_start_regex.match(line):
            current_error = line
        elif current_error and position_regex.search(line):
            match = position_regex.search(line)
            if match:
                filename = match.group(1)
                line_num = int(match.group(2))
                col_num = int(match.group(3))
                error_positions[filename].append((line_num, col_num, err_line))
                current_error = None  # Reset current_error after capturing the position
        err_line += 1

    return error_positions


def count_warnings_by_class(log):
    warning_positions = defaultdict(list)

    current_error = None
    error_start_regex = re.compile(r'^warning:')
    position_regex = re.compile(r'\s+--> (.+?).rs:(\d+):(\d+)')
    warn_line = 1
    for line in log.splitlines():
        # Check if the line indicates an error
        if error_start_regex.match(line):
            current_error = line
        elif current_error and position_regex.search(line):
            match = position_regex.search(line)
            if match:
                filename = match.group(1)
                line_num = int(match.group(2))
                col_num = int(match.group(3))
                warning_positions[filename].append(
                    (line_num, col_num, warn_line))
        warn_line += 1

    return warning_positions


def error_by_class(error_positions, output_file):

    # Prepare data for the DataFrame
    data = {
        'File': [],
        'Number of Errors': [],
        'Error Positions': []
    }

    for file, positions in error_positions.items():
        data['File'].append(file)
        data['Number of Errors'].append(len(positions))
        data['Error Positions'].append(positions)

    # Create a DataFrame

    df = pd.DataFrame(data)
    # Write the DataFrame to an Excel file
    df.to_excel(output_file, index=False)


def warn_by_class(warn_positions, output_file):

    # Prepare data for the DataFrame
    data = {
        'File': [],
        'Number of Warnings': [],
        'Warning Positions': []
    }

    for file, positions in warn_positions.items():
        data['File'].append(file)
        data['Number of Warnings'].append(len(positions))
        data['Warning Positions'].append(positions)

    df = pd.DataFrame(data)

    # Write the DataFrame to an Excel file
    df.to_excel(output_file, index=False)


def traverse_tree(tree: Tree) -> Generator[Node, None, None]:
    cursor = tree.walk()

    visited_children = False
    while True:
        if not visited_children:
            yield cursor.node
            if not cursor.goto_first_child():
                visited_children = True
        elif cursor.goto_next_sibling():
            visited_children = False
        elif not cursor.goto_parent():
            break


def get_function_name(node):
    # Assuming the function name is the first child of type 'identifier'
    for child in node.children:
        if child.type == 'identifier':
            return child.text
    return None


def find_function_definitions(tree):
    function_nodes = []
    for node in traverse_tree(tree):
        if node.type == 'function_item':
            function_name = get_function_name(node)
            function_nodes.append((node, function_name))
    return function_nodes


def is_position_within_node(position, node):
    start_point = node.start_point
    end_point = node.end_point
    return (start_point[0]+1 <= position[0] <= end_point[0]+1)


def get_msg_from_line(log, line_num):
    lines = log.splitlines()
    for i in range(line_num-2, len(lines)):
        if lines[i] == '':
            return "\n".join(lines[line_num - 2: i])
    return None


def find_non_func_nodes(tree, position):
    root = tree.root_node
    for node in traverse_tree(tree):
        if node.start_point[0]+1 <= position[0] <= node.end_point[0]+1 and node != root:
            return node
    return None


def process_file(filename, error_positions, error_log):
    with open(filename, 'r') as f:
        source_code = f.read()
    RUST_LANGUAGE = Language(language_rust.language())
    parser = Parser()
    parser.language = RUST_LANGUAGE
    tree = parser.parse(bytes(source_code, 'utf8'))
    function_nodes = find_function_definitions(tree)
    matches = []
    for pos in error_positions:
        in_func = False
        for node, function_name in function_nodes:
            if is_position_within_node(pos, node):
                matches.append(
                    (pos, function_name, node.start_byte, node.end_byte))
                in_func = True
                break
        if not in_func:
            node = find_non_func_nodes(tree, pos)
            matches.append((pos, "Code lines", node.start_byte, node.end_byte))
    # group the matches by node.start and node.end
    groups = defaultdict(list)
    for p, f, ns, ne in matches:
        groups[(ns, ne)].append((p, f, ns, ne))

    return filename, groups


def get_code_from_byte(file, startbyte, endbyte):
    with open(file, 'r') as f:
        f.seek(startbyte)
        return f.read(endbyte - startbyte)


def trim_function_name(byte_text):
    # Check if the text is a byte string
    if byte_text == "Code lines":
        return byte_text
    # Decode the byte text to a string
    decoded_text = byte_text.decode('utf-8')
    # Strip the leading and trailing characters
    function_name = decoded_text.strip("b'\"")
    return function_name


def error_by_method(err_results, output_file):
    data = {
        'File': [],
        'Class': [],
        'Method': [],
        'Number of Errors': []
    }
    for file, matches in err_results:
        method_counts = defaultdict(int)
        for pos, func_name, node_start, node_end in matches:
            method_counts[func_name] += 1
            # Assume class name is part of the file name for simplicity
            class_name = file.split('/')[-1].split('.')[0]

        for method_name, count in method_counts.items():
            data['File'].append(file)
            data['Class'].append(class_name)
            data['Method'].append(trim_function_name(method_name))
            data['Number of Errors'].append(count)

    df = pd.DataFrame(data)
    df.to_excel(output_file, index=False)


def warn_by_method(warn_results, output_file):
    data = {
        'File': [],
        'Class': [],
        'Method': [],
        'Number of Warnings': []
    }

    for file, matches in warn_results:
        method_counts = defaultdict(int)
        for pos, func_name, node_start, node_end in matches:
            method_counts[func_name] += 1
            # Assume class name is part of the file name for simplicity
            class_name = file.split('/')[-1].split('.')[0]

        for method_name, count in method_counts.items():
            data['File'].append(file)
            data['Class'].append(class_name)
            data['Method'].append(trim_function_name(method_name))
            data['Number of Warnings'].append(count)

    df = pd.DataFrame(data)
    df.to_excel(output_file, index=False)


def main(args):
    if not os.path.exists(args.error_log) or not os.path.exists(args.src_dir):
        print(f"Folder does not exist.")
        return
    with open(args.error_log, 'r') as f:
        err_msg = f.read()
    warning_positions = count_warnings_by_class(err_msg)
    error_positions = count_errors_by_class(err_msg)
    error_by_class(error_positions, f"{args.report_dir}/error_class.xlsx")
    warn_by_class(warning_positions, f"{args.report_dir}/warning_class.xlsx")
    err_results = []
    warn_results = []
    with ThreadPoolExecutor() as executor:
        future_to_file = {executor.submit(process_file, os.path.join(
            args.src_dir, f"{file}.rs"), pos, err_msg): file for file, pos in error_positions.items()}
        for future in future_to_file:
            file, matches = future.result()
            err_results.append((file, matches))
    error_by_method(err_results, f"{args.report_dir}/error_method.xlsx")
    with ThreadPoolExecutor() as executor:
        future_to_file = {executor.submit(process_file, os.path.join(
            args.src_dir, f"{file}.rs"), pos, err_msg): file for file, pos in warning_positions.items()}
        for future in future_to_file:
            file, matches = future.result()
            warn_results.append((file, matches))

    warn_by_method(warn_results, f"{args.report_dir}/warning_method.xlsx")


# for file, matches in results:
#     print(f"File: {file}")
#     for pos, func_name, node in matches:
#         print(f"  Error at {pos} in function '{func_name}' starting at {node.start_point} and ending at {node.end_point}")

if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        description='Count erros raised by classes and methods')
    parser.add_argument(
        '--error_log', help='path to error messages', required=True, type=str)
    parser.add_argument(
        '--src_dir', help='sorce directory of files', required=True, type=str)
    parser.add_argument(
        '--report_dir', help='path to directory to generate report', required=True, type=str)
    args = parser.parse_args()

    main(args)

# error_positions_to_excel(err_msg, 'error_class.xlsx')
