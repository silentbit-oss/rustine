import tree_sitter


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


def text(node):
    return node.text.decode("utf-8")


def get_children_type(node):
    types = []
    for c in node.children:
        types.append(c.type)
    return types
