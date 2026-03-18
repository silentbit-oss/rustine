from tree_sitter import Language, Parser
import tree_sitter_rust
import tiktoken 

parser = Parser()
rust_language = Language(tree_sitter_rust.language())
parser.language = rust_language 

def find_largest_node_within_limit(source_code, line_number, max_bytes=8192):
    tree = parser.parse(source_code.encode('utf8'))

    root_node = tree.root_node

    # Step 1: Traverse down to find the smallest node containing the line number
    def find_smallest_node_containing_line(node):
        if not (node.start_point[0] <= line_number-1 <= node.end_point[0]):
            # If the line number is not within the node's range, skip this node
            return None

        # Try to find a more specific child node that contains the line number
        for child in node.children:
            result = find_smallest_node_containing_line(child)
            if result:
                return result

        # If no more specific child node is found, return the current node
        return node

    # Find the most specific (smallest) node containing the line
    smallest_node = find_smallest_node_containing_line(root_node)

    if smallest_node is None:
        return None

    # Step 2: Traverse up to find the largest node within the byte limit
    current_node = smallest_node
    last_valid_node = smallest_node

    while current_node:
        node_size = current_node.end_byte - current_node.start_byte
        if node_size > max_bytes:
            # If the current node exceeds the limit, stop and return the last valid node
            break
        # Update the last valid node
        last_valid_node = current_node
        print(last_valid_node.start_point[0])
        print(last_valid_node.text.decode('utf-8'))
        # Move up to the parent node
        current_node = current_node.parent

    # Return the last valid node found within the limit
    return last_valid_node

def parse_code(code):
    """
    Parse the given code and return a list of meaningful blocks (e.g., if, while, loop expressions).
    """
    byte_code = code.encode('utf-8')
    tree = parser.parse(byte_code)
    root_node = tree.root_node

    blocks = []


    def extract_meaningful_blocks(node, code_bytes, last_end_byte=0):

        if node.start_byte < last_end_byte:
            return last_end_byte

        if node.type in ['if_expression', 'while_expression', 'loop_expression', 'for_expression','match_expression']:
            print(node.type)
            if last_end_byte < node.start_byte:
                blocks.append(code_bytes[last_end_byte:node.start_byte].decode('utf-8'))


            blocks.append(code_bytes[node.start_byte:node.end_byte].decode('utf-8'))
            last_end_byte = node.end_byte
        for child in node.children:
            last_end_byte = extract_meaningful_blocks(child, code_bytes, last_end_byte)

        return last_end_byte


    last_end_byte = extract_meaningful_blocks(root_node, byte_code)


    if last_end_byte < len(byte_code):
        blocks.append(byte_code[last_end_byte:].decode('utf-8'))


    return blocks





def store_lines_for_node(node, code):
    if node is None:
        return []
    
    # Find previous non-whitespace character to capture all leading whitespace
    pos = node.start_byte - 1
    while pos >= 0 and chr(code[pos]).isspace():
        pos -= 1
    
    # Get all content from after that character up to node end
    node_code = code[pos + 1:node.end_byte]
    # print(node_code)
    
    # Decode and split into lines
    code_str = node_code.decode('utf-8')
    return code_str.splitlines()

def get_node_size(node):
    """Calculate the size of a node based on its text length."""
    return len(node.text.decode('utf-8'))

def find_node_by_line_number(node, line_number):
    target_node = None
    
    def visit(n):
        nonlocal target_node
        # Get the starting row (0-indexed, so line_number=2 means line 3 in the text)
        start_line = n.start_point[0]
        
        if start_line == line_number:
            target_node = n
            return

        # Recursively visit each child node
        for child in n.named_children:
            visit(child)

    visit(node)
    return target_node

def is_basic_block_start(line):
    """Check if the line starts a basic block by looking for ending '{'."""
    return line.strip().endswith('{')

# def has_nested_basic_blocks(lines):
#     """Check if the given lines contain any nested basic blocks."""
#     return any(is_basic_block_start(line) for line in lines)

# def is_basic_block(node):
#     """Check if the node represents a control structure (basic block)."""
#     return node.type in ('if_expression', 'else_clause', 'while_expression', 'for_expression', 'loop_expression', 'match_expression')

# def get_node_text(node):
#     """Get the text of a node."""
#     return node.text.decode('utf-8')




def divide_into_chunks(code, context_window):
    """
    Divide code into chunks based on the context window size, respecting basic blocks.
    """
    # chunks = []
    current_chunk = []
    current_size = 0
    lines = code.split('\n')
    i = 0

    while i < len(lines):
        line = lines[i]
       
        
        if is_basic_block_start(line):
            # print(line)
            """Parse the code and divide it into chunks based on the context window size."""
            byte_code = code.encode('utf-8')
            
            tree = parser.parse(byte_code)
            root_node = tree.root_node
            node = find_node_by_line_number(root_node, i)
            # print(node)
            # block_size = get_node_size(node)
            # print(f"Node text:\n{code[node.start_byte:node.end_byte]}")

            block_lines=store_lines_for_node(node, byte_code)
            if block_lines and block_lines[0] == '':
                block_lines.pop(0)

            block_lines.pop(0)
            block_lines.insert(0,line)

            block_size = sum(len(temp_line) for temp_line in block_lines)
            # print(block_size)
            # print(block_lines)

            # print(i, current_chunk)

            # Check if the entire block fits in the current chunk
            # print(block_size)
            # print(current_chunk)

            if current_size + block_size <= context_window:
                current_chunk.extend(block_lines)
                # print("yay")
                # print(current_chunk)
                current_size += block_size
                # print(block_lines)
                # print(block_size)
                i+=len(block_lines)-1
                # print(current_size)
                # print(current_chunk, current_size)
                return current_chunk
            else:
                if current_size + len(block_lines[0]) <= context_window:
                    # print(block_lines[0])
                    # print(len(block_lines[0]))

                    # print(block_lines)
                    current_size += len(block_lines[0]) + 1
                    # print(block_lines[0])
                    # print("no")
                    
                    current_chunk.append(block_lines[0])
                    
                    first_newline_index = code[node.start_byte:node.end_byte].find('\n')
                    
                    # print(current_chunk)
                    # print(context_window-current_size)
                    additional_lines = divide_into_chunks(code[node.start_byte + first_newline_index + 1:node.end_byte], context_window - current_size)
                    # print("additional lines", additional_lines)
                    # print("yeah")
                    current_chunk.extend(additional_lines)
                    # print(current_size)
                    # print(current_chunk, current_size)
                    return current_chunk
                else:
                    # print(current_size)
                    # print(current_chunk, current_size)
                    return current_chunk

        else:
            # Regular line, add it if it doesn't fit
            if current_size + len(line) + 1 > context_window:

                # chunks.append('\n'.join(current_chunk))
                # current_chunk = [line]
                # current_size = len(line) + 1
                # print(current_chunk, current_size)
                # print(current_size)
                # print(current_chunk)
                return current_chunk
            else:
                current_chunk.append(line)
                current_size += len(line) + 1
        i+=1
    return current_chunk

    # # Add the last chunk if it's not empty
    # if current_chunk:
    #     chunks.append('\n'.join(current_chunk))

    # return chunks

def parse_and_chunk_code(code, context_window):
    chunks = []
    lines = code.split('\n')
    if lines[0] == '':
        lines.pop(0)
    if lines[-1] == '':
        lines.pop(-1)
    code_with_no_empty_ends = lines
    # print(len(code_with_no_empty_ends))
    # print(code_with_no_empty_ends)

    i = 0
    while i < len(code_with_no_empty_ends):
        # print("yes")
        snippet = code_with_no_empty_ends[i:]
        rejoined_code = '\n'.join(snippet)

        # Add a newline at the start if it doesn't already have one
        if not rejoined_code.startswith('\n'):
            rejoined_code = '\n' + rejoined_code

        # Add a newline at the end if it doesn't already have one
        if not rejoined_code.endswith('\n'):
            rejoined_code += '\n'

        # print(rejoined_code.split('\n'))

        result = divide_into_chunks(rejoined_code, context_window)  # Call the function
        if result is not None:
            real_chunk = result  # Unpack only if result is not None
            if real_chunk:  # Check if the chunk is not empty
                # print(real_chunk)
                chunks.append('\n'.join(real_chunk))
                # print(real_chunk)
                # Jump to the new index
                # print(final_i)
                i += len(real_chunk) - 1
                # print(i)
            else:
                break  # Exit if no chunk was created
        else:
            break  # Exit if divide_into_chunks returned None


    # Simply print without returning anything
    # for chunk in chunks:
    #     print(chunk, end='')  # Print without adding extra newlines
    return chunks
def count_tokens(text):
    encoding = tiktoken.get_encoding("cl100k_base")
    return len(encoding.encode(text))




# context_window =400# Adjust this value to change the chunk size
# chunkz = parse_and_chunk_code(rust_code, context_window)
# # print(chunkz)
# separator = '---\n' 
# for chunk in chunkz:
#     print(chunk, end=separator) # Print without adding extra newlines extra newlines
