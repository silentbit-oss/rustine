import ast
import builtins
import os
import sys
import utils
import re
import keyword
import math
from collections import Counter
import nltk
import tokenize
from io import BytesIO
from nltk import word_tokenize
nltk.download('punkt_tab')
from nltk.corpus import wordnet as wn
from nltk.corpus import words
from nltk.corpus import stopwords
from nltk.stem import PorterStemmer
import tiktoken
# from sklearn.cluster import DBSCAN
# from sklearn.feature_extraction.text import TfidfVectorizer
# from sklearn.metrics import jaccard_score
import numpy as np
# import pycparser
# from pycparser import c_ast, parse_file
from tree_sitter import Language, Parser, Node
import tree_sitter_c as tsc

try:
    # Try to access the words corpus (it will fail if the corpus hasn't been downloaded yet)
    words.words()
    
except LookupError:
    # If the corpus hasn't been downloaded, download it
    nltk.download('words')
    nltk.download('stopwords')
    nltk.download('wordnet')
    nltk.download('omw-1.4')
    nltk.download('punkt')
    nltk.download('punkt_tab')

parser = Parser()
c_language = Language(tsc.language())
parser.language = c_language

def count_tokens(text):
    encoding = tiktoken.get_encoding("cl100k_base")
    return len(encoding.encode(text))

def parse_c_code(code):
    tree = parser.parse(bytes(code, "utf8"))
    return tree

def remove_includes(code):
    tree = parser.parse(bytes(code, "utf8"))
    root_node = tree.root_node

    new_code_lines = []
    for line in code.splitlines():
        if not line.strip().startswith("#include"):
            new_code_lines.append(line)
    
    return "\n".join(new_code_lines)

class LoopCounter:
    def __init__(self):
        self.loop_count = 0
        self.loops = []

    def visit(self, node):
        if node.type in ['for_statement', 'while_statement', 'do_statement']:
            self.loop_count += 1
            self.loops.append(node)
        for child in node.children:
            self.visit(child)

class ConditionCounter:
    def __init__(self):
        self.condition_count = 0
        self.conditions = []

    def visit(self, node):
        if node.type == 'if_statement':
            self.condition_count += 1
            self.conditions.append(node)
        for child in node.children:
            self.visit(child)

class AssignmentCounter:
    def __init__(self):
        self.assignment_count = 0
        self.assignments = []

    def visit(self, node):
        if node.type == 'assignment_expression':
            self.assignment_count += 1
            self.assignments.append(node)
        for child in node.children:
            self.visit(child)


class LoopNestingCounter:
    def __init__(self):
        self.max_nesting_depth = 0
        self.current_depth = 0

    def visit(self, node):
        if node.type in ['for_statement', 'while_statement', 'do_statement']:
            self.current_depth += 1
            self.max_nesting_depth = max(self.max_nesting_depth, self.current_depth)
            for child in node.children:
                self.visit(child)
            self.current_depth -= 1
        else:
            for child in node.children:
                self.visit(child)
        

class MaxConditionCounter:
    def __init__(self):
        self.max_conditions = 0

    def visit(self, node):
        if node.type == 'if_statement':
            conditions_count = self.count_conditions(node.children[1]) 
            self.max_conditions = max(self.max_conditions, conditions_count)
        for child in node.children:
            self.visit(child)

    def count_conditions(self, node):
        if node.type == 'binary_expression':
            if node.children[1].type == '&&' or node.children[1].type == '||':
                return self.count_conditions(node.children[0]) + self.count_conditions(node.children[2])
        elif node.type == 'parenthesized_expression':
            return self.count_conditions(node.children[1])
        return 1
        
class IfNestingCounter:
    def __init__(self):
        self.max_nesting_depth = 0
        self.current_depth = 0

    def visit(self, node):
        if node.type == 'if_statement':
            self.current_depth += 1
            self.max_nesting_depth = max(self.max_nesting_depth, self.current_depth)
            for child in node.children:
                self.visit(child)
            self.current_depth -= 1
        else:
            for child in node.children:
                self.visit(child)
        
class CodeLineCounter:
    def __init__(self):
        self.code_lines = set()

    def visit(self, node):
        if 'start_point' in dir(node):
            self.code_lines.add(node.start_point[0])
        for child in node.children:
            self.visit(child)
        
class VariableCounter:
    def __init__(self):
        self.variables = set()

    def visit(self, node):
        if node.type == 'identifier':
            self.variables.add(node.text.decode('utf-8'))
        for child in node.children:
            self.visit(child)

class ArrayCounter:
    def __init__(self):
        self.array_count = 0
        self.arrays = []

    def visit(self, node):
        if node.type == 'array_declarator':
            if node.parent.type != 'array_declarator':
                self.array_count += 1
                self.arrays.append(node)
        for child in node.children:
            self.visit(child)

class OperatorCounter:
    def __init__(self):
        self.operator_count = 0

    def visit(self, node):
        if node.type in ['binary_expression', 'unary_expression']:
            self.operator_count += 1
        for child in node.children:
            self.visit(child)
        
class MissingConditionCounter:
    def __init__(self):
        self.missing_conditions_count = 0

    def visit_node(self, node):
        if node.type == 'while_statement' or node.type == 'if_statement':
            condition_node = node.child_by_field_name('condition')
            if condition_node and self.is_true_condition(condition_node):
                self.missing_conditions_count += 1

        for child in node.children:
            self.visit_node(child)

    def is_true_condition(self, node):
        if node.text == b'(true)':
            return True
        if node.text == b'(1)':
            return True
        return False

# class NestedCastingCounter(ast.NodeVisitor):
#     def __init__(self):
#         self.max_nested_casting = 0
#         self.current_depth = 0

#     def visit_Call(self, node):
#         if isinstance(node.func, ast.Name) and node.func.id in {'int', 'float', 'str', 'bool', 'complex', 'bytes', 'list', 'tuple', 'set', 'dict'}:
#             self.current_depth += 1
#             self.max_nested_casting = max(self.max_nested_casting, self.current_depth)
#             self.generic_visit(node)
#             self.current_depth -= 1
#         else:
#             self.generic_visit(node)

class NestedCastingCounter:
    def __init__(self):
        self.nested_casting_count = 0
        self.nested = []

    def visit_node(self, node):
        if node.type == 'cast_expression':
            for child in node.children:
                if child.type == 'cast_expression':
                    self.nested_casting_count += 1
                    self.nested.append(child.text.decode('utf-8'))

        for child in node.children:
            self.visit_node(child)
            
def get_nested_casting(tree):
    counter = NestedCastingCounter()
    counter.visit_node(tree.root_node)
    return counter.nested_casting_count, counter.nested


def get_num_of_missing_conditions(c_code: str) -> int:
    tree = parser.parse(bytes(c_code, "utf8"))
    root_node = tree.root_node
    counter = MissingConditionCounter()
    counter.visit_node(root_node)
    return counter.missing_conditions_count
        
def get_num_of_operators(tree):
    counter = OperatorCounter()
    counter.visit(tree.root_node)
    return counter.operator_count


def get_num_of_arrays(tree):
    counter = ArrayCounter()
    counter.visit(tree.root_node)
    return counter.array_count, counter.arrays

def get_num_of_variables(tree):
    counter = VariableCounter()
    counter.visit(tree.root_node)
    return len(counter.variables), counter.variables
        
def get_max_conditions(tree):
    counter = MaxConditionCounter()
    counter.visit(tree.root_node)
    return counter.max_conditions

def get_max_nested_loops(tree):
    loop_nesting_counter = LoopNestingCounter()
    loop_nesting_counter.visit(tree.root_node)
    return loop_nesting_counter.max_nesting_depth


def get_max_line_token_length(code):
    lines = code.split('\n')
    max_length = max(count_tokens(line) for line in lines)
    return max_length

def get_lines_of_code(tree):
    counter = CodeLineCounter()
    counter.visit(tree.root_node)
    return len(counter.code_lines)

def tokenize_code(code):
    tokens = word_tokenize(code)
    return len(tokens)

def get_num_of_tokens(code):
    num_tokens = count_tokens(code)
    return num_tokens


def get_num_of_conditions(tree):
    counter = ConditionCounter()
    counter.visit(tree.root_node)
    return counter.condition_count, counter.conditions

def get_num_of_loops(tree):
    counter = LoopCounter()
    counter.visit(tree.root_node)
    return counter.loop_count, counter.loops

def get_num_of_assignments(tree):
    counter = AssignmentCounter()
    counter.visit(tree.root_node)
    return counter.assignment_count, counter.assignments

def get_max_nested_ifs(tree):
    counter = IfNestingCounter()
    counter.visit(tree.root_node)
    return counter.max_nesting_depth

def main(c_file):
    code = open(c_file, 'r').read()
    tree = parse_c_code(code)
    metrics_r2i(tree, code)
    # metrics_textual(tree, code)
    
def metrics_r2i(tree, code):
    num_tokens = get_num_of_tokens(code)
    num_conditions, conditions = get_num_of_conditions(tree)
    num_loops, loops = get_num_of_loops(tree)
    num_assignments, assignments = get_num_of_assignments(tree)
    num_max_nested_loop = get_max_nested_loops(tree)
    num_max_nested_if = get_max_nested_ifs(tree)
    num_max_conditions_in_if = get_max_conditions(tree)
    max_line_tokens = get_max_line_token_length(code)
    lines_of_code = get_lines_of_code(tree)
    num_of_variables, variables = get_num_of_variables(tree)
    num_of_arrays, arrays = get_num_of_arrays(tree)
    num_of_operators = get_num_of_operators(tree)
    num_of_missing_conditions = get_num_of_missing_conditions(code)
    num_of_nested_casting, _ = get_nested_casting(tree)

    metrics = {
        "num_tokens": num_tokens,
        "num_conditions": num_conditions,
        "num_loops": num_loops,
        "num_assignments": num_assignments,
        "num_max_nested_loop": num_max_nested_loop,
        "num_max_nested_if": num_max_nested_if,
        "num_max_conditions_in_if": num_max_conditions_in_if,
        "max_line_tokens": max_line_tokens,
        "lines_of_code": lines_of_code,
        "num_of_variables": num_of_variables,
        "num_of_arrays": num_of_arrays,
        "num_of_operators": num_of_operators,
        "num_of_missing_conditions": num_of_missing_conditions,
        "num_of_nested_casting": num_of_nested_casting
    }

    return metrics


def preprocessing(code):
    no_imports_code = remove_includes(code)
    tree = parser.parse(bytes(no_imports_code, "utf8"))
    tokens = remove_non_textual_tokens_from_code(tree) 
    splited_tokens = split_tokens(tokens) 
    filtered_tokens = remove_stop_words(splited_tokens)  
    stemmed_tokens = apply_porter_stemming(filtered_tokens)  
    return stemmed_tokens


def preprocessing_line(code):
    tree = parser.parse(bytes(code, "utf8"))
    tokens = remove_non_textual_tokens_from_code(tree) # Textual tokens
    splited_tokens = split_tokens(tokens) # Split tokens
    filtered_tokens = remove_stop_words(splited_tokens) # Filtered tokens
    stemmed_tokens = apply_porter_stemming(filtered_tokens) # Stemmed tokens
    return stemmed_tokens

def remove_non_textual_tokens_from_code(tree):
    tokens = []
    cursor = tree.walk()

    def traverse(cursor):
        while True:
            node = cursor.node
            if node.type in {"identifier", "string_literal", "number_literal"}:
                tokens.append(node.text.decode('utf-8'))
            
            if cursor.goto_first_child():
                traverse(cursor)
                cursor.goto_parent()
            
            if not cursor.goto_next_sibling():
                break

    traverse(cursor)
    return tokens


def split_tokens(tokens):
    split_tokens = []
    for token in tokens:
        parts = token.split('_')
        for part in parts:
            camel_case_parts = re.findall(r'[A-Z]?[a-z]+|[A-Z]+(?=[A-Z]|$)', part)
            split_tokens.extend(camel_case_parts)
    return split_tokens


def remove_stop_words(tokens):
    stop_words = set(stopwords.words('english'))
    filtered_tokens = [token for token in tokens if token.lower() not in stop_words]
    return filtered_tokens

def apply_porter_stemming(tokens):
    porter = PorterStemmer()
    stemmed_tokens = [porter.stem(token) for token in tokens]
    return stemmed_tokens


def get_itid(tokens):
    english_words = words.words()
    overlap = [token for token in tokens if token in english_words]
    rate = len(overlap) / len(tokens) if tokens else 0
    return rate


def get_nm(tokens):
    # Number of Meanings (NM)
    nm_values = [number_of_meanings(token) for token in tokens]
    if nm_values:
        return max(nm_values), sum(nm_values) / len(nm_values)
    else:
        return 0, 0
    
def number_of_meanings(term):
    synsets = wn.synsets(term)
    return len(synsets)

def extract_identifiers(node):
    identifiers = []
    cursor = node.walk()

    def traverse(cursor):
        while True:
            current_node = cursor.node
            if current_node.type == "identifier":
                identifiers.append(current_node.text.decode("utf8"))
            
            if cursor.goto_first_child():
                traverse(cursor)
                cursor.goto_parent()
            
            if not cursor.goto_next_sibling():
                break

    traverse(cursor)
    return identifiers


def extract_blocks(tree):
    blocks = []
    cursor = tree.walk()
    
    def traverse(cursor):
        while True:
            node = cursor.node
            if node.type in {"function_definition", "for_statement", "while_statement", "if_statement"}:
                block_identifiers = extract_identifiers(node)
                blocks.append(set(block_identifiers))
            
            if cursor.goto_first_child():
                traverse(cursor)
                cursor.goto_parent()
            
            if not cursor.goto_next_sibling():
                break

    traverse(cursor)
    return blocks


def vocabulary_overlap(block1, block2):
    return len(block1 & block2) / float(len(block1 | block2))

def get_TC(tree):
    blocks = extract_blocks(tree)
    overlaps = []
    num_blocks = len(blocks)
    for i in range(num_blocks):
        for j in range(i + 1, num_blocks):
            overlap = vocabulary_overlap(blocks[i], blocks[j])
            overlaps.append(overlap)
    return {
        'max_overlap': max(overlaps) if overlaps else 0,
        'min_overlap': min(overlaps) if overlaps else 0,
        'average_overlap': sum(overlaps) / len(overlaps) if overlaps else 0
    }
    
def preprocess_line(line):
    tokens = nltk.word_tokenize(line)
    return [token.lower() for token in tokens if token.isalpha()]


def jaccard_similarity(list1, list2):
    set1, set2 = set(list1), set(list2)
    intersection = len(set1.intersection(set2))
    union = len(set1.union(set2))
    return intersection / union if union != 0 else 0

def prepare_documents(code_snippet):
    lines = code_snippet.strip().split('\n')
    documents = [preprocess_line(line) for line in lines if line.strip() != '']
    return documents

def compute_jaccard_matrix(documents):
    n = len(documents)
    jaccard_matrix = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            jaccard_matrix[i, j] = 1 - jaccard_similarity(documents[i], documents[j])
    return jaccard_matrix
    
# def get_noc(code):
#     documents = prepare_documents(code)
#     jaccard_matrix = compute_jaccard_matrix(documents)
#     dbscan = DBSCAN(metric='precomputed', eps=0.5, min_samples=1)
#     clusters = dbscan.fit_predict(jaccard_matrix)
#     num_clusters = len(set(clusters))
#     num_documents = len(documents)
#     noc = num_clusters
#     noc_norm = num_clusters / num_documents if num_documents else 0
#     return noc, noc_norm



def find_particularity(term):
    synsets = wn.synsets(term)
    if not synsets:
        return 0
    # Get the first synset (most common sense)
    synset = synsets[0]
    # Calculate the number of hops to the root hypernym
    hypernym_paths = synset.hypernym_paths()
    if not hypernym_paths:
        return 0
    # Use the shortest path to the root
    shortest_path = min(len(path) for path in hypernym_paths)
    return shortest_path

def get_nmi_line_tokens(line):
    tokens = preprocessing_line(line)
    # Narrow Meaning Identifiers (NMI), summing the "particularity" of each term in a line of code. The "particularity" of a term is defined as the number of hops from the term to the root of its hypernym tree in WordNet.
    particularities = [find_particularity(token) for token in tokens if token.isalpha()]
    return sum(particularities)

def get_nmi_snippet(snippet):
    lines = snippet.strip().split('\n')
    line_nmis = [get_nmi_line_tokens(line) for line in lines]
    total_nmi = sum(line_nmis)
    average_nmi = total_nmi / len(line_nmis) if line_nmis else 0
    return average_nmi


def get_entropy(code):
    tokens = word_tokenize(code)
    token_counts = Counter(tokens)
    total_tokens = sum(token_counts.values())
    entropy = 0
    for count in token_counts.values():
        probability = count / total_tokens
        entropy -= probability * math.log2(probability) 
    return entropy



# def metrics_textual(tree, code):
#     stemmed_tokens = preprocessing(code)
#     itid_rate = get_itid(stemmed_tokens)
#     max_nm, avg_nm = get_nm(stemmed_tokens)
#     tc_res = get_TC(tree)
#     average_tc = tc_res["average_overlap"]
#     noc, noc_norm = get_noc(code)
#     nmi = get_nmi_snippet(code)
#     entropy = get_entropy(code)
    
#     print("""itid_rate: {}, average NM: {}, average_tc: {}, noc_norm: {}, nmi: {}, entropy: {}"""\
#         .format(itid_rate, avg_nm, average_tc, noc_norm, nmi, entropy))

if __name__ == "__main__":
    args = sys.argv[1:]
    python_file = args[0]
    main(python_file)
    