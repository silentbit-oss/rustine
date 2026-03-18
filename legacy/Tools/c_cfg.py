
import os
from tree_sitter import Language, Parser
import tree_sitter_c

# import networkx as nx
import subprocess


class Vertex:
    def __init__(self, index, stmt, node, start_switch=None, end_switch=None):
        self.index = index
        self.stmt = stmt
        self.node = node
        self.start_switch = start_switch
        self.end_switch = end_switch
        self.edges = []  # List to store adjacent vertices (edges)

    def add_edge(self, vertex):
        self.edges.append(vertex)

    def __repr__(self):
        return f"Vertex(index={self.index}, statement='{self.stmt}')"


def get_child_by_type(node, type_name, index=0):
    if not node:
        return None
    type_child_id = 0
    for child in node.children:
        if child.type == type_name:
            if type_child_id == index:
                return child
            else:
                type_child_id += 1
    return None


def extract_func(root):
    functions = {}
    for node in root.children:
        if node.type == 'function_definition':
            declarator = get_child_by_type(node, 'function_declarator')
            if not declarator:
                pointer_declarator = get_child_by_type(
                    node, 'pointer_declarator')
                declarator = get_child_by_type(
                    pointer_declarator, 'function_declarator')
            if not declarator:
                continue

            identifier = get_child_by_type(declarator, 'identifier')
            func_name = identifier.text.decode('utf-8')
            functions[func_name] = node
    return functions


def text(node):
    return node.text.decode('utf-8')


def refactor_switch(source_code):
    def find_switch(node, switch_list):
        for child in node.children:
            if child.type == 'switch_statement':
                # TODO: switch inside switch
                switch_list.append(child)
            switch_list = find_switch(child, switch_list)
        return switch_list

    def insert_code_by_index(source_code, indexed_insert_code):
        offset = 0
        new_code = source_code
        for index, code in indexed_insert_code:
            new_index = index + offset
            new_code = new_code[:new_index] + \
                code + new_code[new_index:]
            offset += len(code)
        return new_code

    def find_insert_code(node):
        # detect the first `break` that is the direct child of the `case_statement` node
        # it's the `break` that can stop the case
        """
        input: current `case_statement` node
        output: code should be inserted
        """
        insert_code = ''
        case_node = node.next_sibling
        while (case_node):
            if case_node.type != 'case_statement':
                case_node = case_node.next_sibling
                continue
            if get_child_by_type(case_node, ':').next_sibling:
                execute_node = get_child_by_type(case_node, ':').next_sibling
            else:
                case_node = case_node.next_sibling
                continue
            while execute_node:
                insert_code += '\n'+text(execute_node)+'\n'
                if execute_node.type == 'break_statement':
                    return insert_code
                execute_node = execute_node.next_sibling
            case_node = case_node.next_sibling
        return insert_code

    parser = Parser()
    c_language = Language(tree_sitter_c.language())
    parser.language = c_language
    tree = parser.parse(bytes(source_code, 'utf8'))
    root = tree.root_node
    indexed_insert_code = []
    for switch_node in find_switch(root, []):
        assert switch_node.type == 'switch_statement'
        compound = get_child_by_type(switch_node, 'compound_statement')
        for child in compound.children:
            if child.type == 'case_statement':
                if get_child_by_type(child, 'break_statement'):
                    continue
                else:
                    last_byte = child.end_byte
                    insert_code = find_insert_code(child)
                    indexed_insert_code.append((last_byte, insert_code))
    new_code = insert_code_by_index(source_code, indexed_insert_code)
    return new_code


def build_node(node, index):

    def build_if_node(node, index):
        if_condition = get_child_by_type(node, 'parenthesized_expression')
        if_condition_text = text(if_condition)
        index += 1
        start = Vertex(index, if_condition_text, node)
        true_br = if_condition.next_sibling
        while true_br.type == 'comment':
            true_br = true_br.next_sibling
        start_true, end_true, index = build_node(true_br, index)
        if true_br.next_sibling:
            assert true_br.next_sibling.type == 'else_clause', node.start_point
            false_br = true_br.next_sibling
            false_br = false_br.child(1)  # else + compound / else + if_stmt
            start_false, end_false, index = build_node(false_br, index)
        else:
            index += 1
            start_false = end_false = Vertex(index, '', None)

        start.add_edge(start_true)
        start.add_edge(start_false)
        index += 1
        end = Vertex(index, '', None)
        end_true.add_edge(end)
        end_false.add_edge(end)
        return start, end, index

    def build_while_node(node, index):
        while_condition = get_child_by_type(node, 'parenthesized_expression')
        while_condition_text = text(while_condition)
        index += 1
        start = Vertex(index, while_condition_text, node)
        true_br = while_condition.next_sibling

        start_true, end_true, index = build_node(true_br, index)
        start.add_edge(start_true)
        end_true.add_edge(start)
        index += 1
        end = Vertex(index, '', None)
        start.add_edge(end)
        return start, end, index

    def build_for_node(node, index):
        for_block = node.child(node.child_count-1)
        for_condition_text = text(node).replace(text(for_block), '')
        index += 1
        start = Vertex(index, for_condition_text, node)
        start_true, end_true, index = build_node(for_block, index)
        start.add_edge(start_true)
        end_true.add_edge(start)
        index += 1
        end = Vertex(index, '', None)
        start.add_edge(end)
        return start, end, index

    def build_switch_node(node, index):
        switch_condition = get_child_by_type(node, 'parenthesized_expression')
        switch_condition_text = text(switch_condition)
        index += 1
        start = Vertex(index, switch_condition_text, node)
        index += 1
        end = Vertex(index, '', None)
        cases = switch_condition.next_sibling
        for child in cases.children:
            if child.type == '{' or child.type == '}':
                continue
            assert child.type == 'case_statement', child.type
            start_case, end_case, index = build_node(child, index)
            start.add_edge(start_case)
            end_case.add_edge(end)
        start.end_switch = end  # end_switch will be eliminated because it's blank
        start.start_switch = start
        end.start_switch = start  # start_switch will not be eliminated
        end.end_switch = end
        return start, end, index
    if node.type == 'if_statement':
        return build_if_node(node, index)
    if node.type == 'while_statement':
        return build_while_node(node, index)
    if node.type == 'for_statement':
        return build_for_node(node, index)
    if node.type == 'switch_statement':
        return build_switch_node(node, index)
    if node.type in ['compound_statement', 'case_statement']:
        index += 1
        start = Vertex(index, '', None)
        prev_node = start
        for c in node.children:
            if c.type in ['{', '}', 'comment', 'case', ':']:
                continue
            else:
                start_node, end_node, index = build_node(c, index)
                prev_node.add_edge(start_node)
                prev_node = end_node
        end = end_node
        return start, end, index
    # if node.type == 'expression_statement':
    #     call_expression = get_child_by_type(node, 'call_expression')
    #     if call_expression:
    #         identifier = get_child_by_type(call_expression, 'identifier')
    #         if identifier.text == 'assert':
    #             # assert node
    #             return build_assert_node(node, index)
    if node.type in ['return_statement', 'expression_statement', 'break_statement', 'continue_statement']:
        index += 1
        start = Vertex(index, text(node), node)
        end = start
        return start, end, index
    if node.type == 'identifier' and node.parent.type == 'case_statement':
        index += 1
        start = Vertex(index, text(node), node.parent)
        end = start
        return start, end, index
    else:
        index += 1
        start = Vertex(index, text(node), node)
        end = start
        return start, end, index


def build_ast(node, index):
    body = get_child_by_type(node, 'compound_statement')
    start_ast, end_ast, index = build_node(body, index)
    index += 1
    start = Vertex(index, 'start', None)
    index += 1
    end = Vertex(index, 'end', None)
    start.add_edge(start_ast)
    end_ast.add_edge(end)
    return start, end, index


def print_ast(node, source_code, file, indent=0):
    """ Recursively print the AST with indentation for better readability """
    # if not node.children:
    print('  ' * indent +
          f"{node.type} [start:({node.start_point[0]+1},{node.start_point[1]+1}),end:({node.end_point[0]+1},{node.end_point[1]+1})]", file=file)

    # if node.type in ['parenthesized_expression', 'expression_statement', 'return_statement', 'function_declarator', 'declaration']:
    #     return
    for child in node.children:
        print_ast(child, source_code, file, indent + 1)


def print_cfg(start_vertex, visited=set(), dot_lines=[]):
    if start_vertex.index in visited:
        return dot_lines
    visited.add(start_vertex.index)
    stmt = start_vertex.stmt.replace('\"', '\\\"')
    stmt = stmt.replace('\\\\\"', '\\\\\\\"')
    dot_lines.append(
        f"{start_vertex.index} [label=\"{start_vertex.index}-{stmt}\"];")
    if not start_vertex.edges:
        return dot_lines
    for edge_index, child in enumerate(start_vertex.edges):
        dot_lines.append(
            f"{start_vertex.index} -> {child.index} [label = \"{edge_index}\"];")
        print_cfg(child, visited, dot_lines)
    return dot_lines


def dot_gen(start_node, visited):
    dot_lines = ["digraph G {", "node [shape=rect]; "]
    dot_lines += print_cfg(start_node, visited, [])
    dot_lines.append("}")
    return "\n".join(dot_lines)


def eliminate_blank(start: Vertex, visited=set()):
    # let the flow do not pass the blank node
    if start.index in visited:
        return
    visited.add(start.index)
    if not start.edges:
        return
    for i in range(len(start.edges)):
        # skip this blank node
        if start.edges[i].stmt == '':
            # blank node only has one outedge
            assert len(start.edges[i].edges) == 1
            # not have a start_switch, so, not in a switch
            if start.edges[i].start_switch == None:
                # find next non-blank node
                next_node = start.edges[i].edges[0]
                while next_node.stmt == '' and len(next_node.edges) == 1:
                    next_node = next_node.edges[0]
                    # reconnect switch start-end
                start.edges[i] = next_node
            else:
                next_node = start.edges[i].edges[0]
                next_node.start_switch = start.edges[i].start_switch
                assert (next_node.start_switch != None)
                next_node.start_switch.end_switch = next_node
                while next_node.stmt == '' and len(next_node.edges) == 1:
                    new_node = next_node.edges[0]
                    new_node.start_switch = next_node.start_switch
                    new_node.start_switch.end_switch = new_node
                    next_node = new_node
                start.edges[i] = next_node
        eliminate_blank(start.edges[i], visited)
    return


def return_to_end(start: Vertex, end: Vertex, visited=set()):
    if start.index in visited:
        return
    visited.add(start.index)
    # return is the end node
    if start.node != None and start.node.type == 'return_statement':
        assert len(start.edges) == 1
        # start.edges[0] = end
        start.edges = []

    # assert fail to exit
    if start.node != None and start.node.type == 'expression_statement':
        call_expression = get_child_by_type(start.node, 'call_expression')
        if call_expression:
            identifier = get_child_by_type(call_expression, 'identifier')
            if identifier and text(identifier) == 'assert':
                # assert node
                exit_node = Vertex(end.index+1, 'exit', None)
                start.add_edge(exit_node)
    if not start.edges:
        return
    for i in range(len(start.edges)):
        return_to_end(start.edges[i], end, visited)
    return


def tag_switch(start: Vertex, visited=set()):
    if start.index in visited:
        return
    visited.add(start.index)
    if not start.edges:
        return
    for child in start.edges:
        if start.start_switch != None and start.end_switch != start:
            child.start_switch = start.start_switch
            child.end_switch = start.start_switch.end_switch
        tag_switch(child, visited)


def handle_continue_and_break(start: Vertex, end: Vertex, loop_node: Vertex, block_node: Vertex, visited=set()):
    if start.index in visited:
        return
    visited.add(start.index)
    if start.node != None and (start.node.type == 'while_statement' or start.node.type == 'for_statement'):
        loop_node = start  # continue in a loop
    if start.node != None and (start.node.type == 'while_statement' or start.node.type == 'for_statement'):
        block_node = start  # break in a block
    if start.node != None and start.node.type == 'continue_statement':
        assert len(start.edges) == 1
        assert loop_node != None
        # start.edges[0] = end
        start.edges[0] = loop_node
    if start.node != None and start.node.type == 'break_statement':
        if start.start_switch == None:
            assert len(start.edges) == 1
            assert block_node != None, start.node.start_point
            # start.edges[0] = end
            next = block_node.edges[1]  # false br of loop_node
            start.edges[0] = next
        else:
            # in switch block
            assert len(start.edges) == 1
            start.edges[0] = start.end_switch
    if not start.edges:
        return
    for i in range(len(start.edges)):
        handle_continue_and_break(
            start.edges[i], end, loop_node, block_node, visited)
    return


def get_children_type(node):
    types = []
    for c in node.children:
        types.append(c.type)
    return types


def extract_var(node):
    declarator = node.child(node.child_count-1)
    if declarator.type == 'pointer_declarator':
        var_type = 'pointer'
        if get_child_by_type(declarator, "identifier"):
            var_name = text(get_child_by_type(declarator, "identifier"))
            return var_name, var_type
    return None


def get_parameter_var(node):
    var = {}
    function_declarator = get_child_by_type(node, "function_declarator")
    if not function_declarator:
        function_declarator = get_child_by_type(get_child_by_type(
            node, "pointer_declarator"), "function_declarator")
    parameter_list = get_child_by_type(function_declarator, "parameter_list")
    for parameter in parameter_list.children:
        if parameter.type in ['(', ')', ',']:
            continue
        assert parameter.type == 'parameter_declaration', parameter.type

        if (extracted_var := extract_var(parameter)):
            var_name, var_type = extracted_var
            var[var_name] = var_type
    return var


def is_check_pointer_null(binary_expression, var):
    """
    Given a binary expression, check whether the binary expression is like `p == NULL`
    """
    if (binary_expression and get_children_type(binary_expression) == ['identifier', '==', 'null']):
        # this binary_exp is like 'p == null'
        p = text(get_child_by_type(binary_expression, "identifier"))

        if (p in var and var[p] == 'pointer'):  # check if p is a pointer
            # keep only the false branch
            return True
    return False


def remove_null_pointer_check(start: Vertex, end: Vertex, visited=set(), var=dict()):
    if start.index in visited:
        return
    visited.add(start.index)
    if start.node and start.node.type == 'declaration':
        if (extracted_var := extract_var(start.node)):
            var_name, var_type = extracted_var
            var[var_name] = var_type
    # if (p)
    # if (p == NULL)
    if start.node != None and start.node.type == 'if_statement':
        if_condition = get_child_by_type(
            start.node, "parenthesized_expression")
        binary_expression = get_child_by_type(
            if_condition, "binary_expression")

        if is_check_pointer_null(binary_expression, var):  # check if p is a pointer
            # keep only the false branch
            start.edges = [start.edges[1]]
        if (get_children_type(if_condition) == ['(', 'identifier', ')']):
            # this if_condition is like 'if(p)'
            p = text(get_child_by_type(if_condition, "identifier"))
            if (p in var and var[p] == 'pointer'):
                start.edges = [start.edges[0]]  # keep only the true branch
        if (binary_expression and get_children_type(binary_expression) == ['binary_expression', '||', 'binary_expression']):
            binary_exp1 = get_child_by_type(
                binary_expression, "binary_expression", 0)
            binary_exp2 = get_child_by_type(
                binary_expression, "binary_expression", 1)
            if is_check_pointer_null(binary_exp1, var) and is_check_pointer_null(binary_exp2, var):
                # keep only the false branch
                start.edges = [start.edges[1]]
            # assert(p && ...)
    if start.node != None and start.node.type == 'expression_statement':

        call_expression = get_child_by_type(start.node, 'call_expression')
        if call_expression:
            identifier = get_child_by_type(call_expression, 'identifier')
            argument_list = get_child_by_type(call_expression, "argument_list")
            if identifier and text(identifier) == 'assert':  # assert node
                # assert (p && ...)
                if get_children_type(argument_list) == ['(', 'binary_expression', ')']:
                    binary_expression = get_child_by_type(
                        argument_list, "binary_expression")
                    binary_operands = text(binary_expression).split("&&")
                    flag = True
                    for op in binary_operands:
                        op = op.strip()
                        if (op in var and var[op] == 'pointer'):
                            continue
                        if ((op.startswith("\"") or op.startswith("'")) and (op.endswith("\"") or op.endswith("'"))):
                            continue
                        else:
                            flag = False
                            break

                    if flag == True:  # remove false br
                        start.edges = [start.edges[0]]
    for i in range(len(start.edges)):
        remove_null_pointer_check(
            start.edges[i], end, visited, var)
    return


def remove_comments(source_code):
    def collect_comments(node):
        comments = []
        if node.child_count == 0:  # leaf node
            if node.type == 'comment':
                comments.append(text(node))
        for child in node.children:
            comments += collect_comments(child)
        return comments
    parser_c = Parser()
    c_language = Language(tree_sitter_c.language())
    parser_c.language = c_language
    tree = parser_c.parse(source_code.encode())
    comments = collect_comments(tree.root_node)
    cleaned_code = source_code
    for comment in comments:
        cleaned_code = cleaned_code.replace(comment, '')
    return cleaned_code


def cfg_gen(name, source_code, cfg_path):
    source_code = remove_comments(source_code)
    source_code = refactor_switch(source_code)
    parser_c = Parser()
    c_language = Language(tree_sitter_c.language())
    parser_c.language = c_language
    c_tree = parser_c.parse(source_code.encode('utf-8'))
    root = c_tree.root_node
    root = get_child_by_type(root, "function_definition")
    index = 0
    visited = set()
    start, end, index = build_ast(root, index=0)
    eliminate_blank(start, visited)
    visited = set()
    return_to_end(start, end, visited)
    visited = set()
    tag_switch(start, visited)
    visited = set()
    handle_continue_and_break(start, end, None, None, visited)
    visited = set()
    var = get_parameter_var(root)
    remove_null_pointer_check(start, end, visited, var)
    visited = set()
    dot_content = dot_gen(start, visited)
    dot_path = os.path.join(cfg_path, f'{name}.dot')
    png_path = os.path.join(cfg_path, f'{name}.png')
    with open(f'{dot_path}', 'w') as file:
        file.write(dot_content)
    command = f"dot -Tpng {dot_path} -o {png_path}"
    subprocess.run(command, shell=True, check=True)
    command = f'rm {dot_path}'
    subprocess.run(command, shell=True, check=True)
    return png_path


if __name__ == '__main__':
    with open('/home/chengxiao/c2rust/Rust-Test-Translation/example/libcsv/c/libcsv.c') as file:
        src_code = file.read()
    src_code = remove_comments(src_code)
    src_code = refactor_switch(src_code)
    # init parser info
    parser_c = Parser()
    c_language = Language(tree_sitter_c.language())
    parser_c.language = c_language
    # with open('refactored.c') as file:
    #     src_code = file.read()
    # src_code = replace_switch(src_code)
    # with open('refactored.c','w') as file:
    #     file.write(src_code)
    c_tree = parser_c.parse(src_code.encode('utf-8'))
    root = c_tree.root_node
    with open('test.ast', 'w') as file:
        print_ast(root, src_code, file=file)
    # extract all the functions
    functions = extract_func(root)
    # build ast for each function
    for name in functions.keys():
        node = functions[name]

        # if name != 'csv_fini':
        #     continue
        print("--------------------")
        print(name)
        index = 0
        visited = set()
        start, end, index = build_ast(node, index=0)
        eliminate_blank(start, visited)
        visited = set()
        return_to_end(start, end, visited)
        visited = set()
        tag_switch(start, visited)
        visited = set()
        handle_continue_and_break(start, end, None, None, visited)
        visited = set()
        var = get_parameter_var(node)
        remove_null_pointer_check(start, end, visited, var)
        visited = set()
        dot_content = dot_gen(start, visited)
        with open(f'results/libcsv/c/{name}.dot', 'w') as file:
            file.write(dot_content)
        command = f"dot -Tpng results/libcsv/c/{name}.dot -o results/libcsv/c/graphs/{name}.png"
        subprocess.run(command, shell=True, check=True)
