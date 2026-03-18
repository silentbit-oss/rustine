from tree_sitter import Language, Parser
import tree_sitter_c as tsc
import os
import sys

C_LANGUAGE = Language(tsc.language())
parser = Parser()
parser.language = C_LANGUAGE

function_define = 0
config_define = 0

def print_macros(node):
    global function_define
    global config_define

    for child in node.children:
        if child.type == "preproc_ifdef":
            #print(child.type, " => ", child.text)
            config_define += 1
        elif child.type == "preproc_include":
            #print(child.type, " => ", child.text)
            config_define += 1
        elif child.type == "preproc_function_def":
            #print(child.type, " => ", child.text)
            function_define += 1
        elif child.type == "preproc_def":
            #print(child.type, " => ", child.text)
            config_define += 1

        print_macros(child)

def main(c_file):
    with open(c_file, 'rb') as f:
        tree = parser.parse(f.read())
        root_node = tree.root_node
        print_macros(root_node)

if __name__ == "__main__":
    args = sys.argv[1:]
    path = args[0]

    if os.path.isfile(path):
        if path.endswith('.c') or path.endswith('.h'):
            main(path)
    elif os.path.isdir(path):
        for root, _, files in os.walk(path):
            for file in files:
                if file.endswith('.c') or file.endswith('.h'):
                    file_path = os.path.join(root, file)
                    main(file_path)
    else:
        print("Invalid path")

    print(f"Number of function macro: {function_define}")
    print(f"Number of config macro: {config_define}")
