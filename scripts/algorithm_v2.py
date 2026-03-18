import os
import sys
import re
import subprocess
import json
from tree_sitter import Language, Parser
import tree_sitter_rust
from collections import Counter
from collections import defaultdict
from openai import OpenAI
from bisect import bisect_right


def setup_parser():
    """Set up the tree-sitter parser for Rust."""
    parser = Parser()
    rust_language = Language(tree_sitter_rust.language())
    parser.language = rust_language
    return parser


def instrument_function(content, new_content_idx, node):
    """Add println! statement at the start of a function's block."""
    # Get the function name
    fn_name_node = node.child_by_field_name("name")
    if not fn_name_node:
        return new_content_idx, False
    fn_name = content[fn_name_node.start_byte+new_content_idx:fn_name_node.end_byte+new_content_idx].decode("utf-8")
    #print("func:", fn_name)

    # Get the function body (block)
    body_node = node.child_by_field_name("body")
    if not body_node or body_node.type != "block":
        return new_content_idx, False

    # Find the opening brace of the function body
    start_byte = body_node.start_byte+new_content_idx
    end_byte = body_node.end_byte+new_content_idx
    body_content = content[start_byte:end_byte].decode("utf-8")
    # Insert println! after the opening brace
    insert_pos = start_byte + 1  # After the '{'
    println_stmt = f'\n\tprintln!("* {fn_name}");'
    content = content[:insert_pos] + println_stmt.encode("utf-8") + content[insert_pos:]
    
    return content, new_content_idx+len(println_stmt.encode("utf-8")), True


def process_file(file_path, parser):
    """Process a single Rust file."""
    # Read the file
    with open(file_path, "rb") as f:
        content = f.read()

    # Parse the file
    tree = parser.parse(content)
    cursor = tree.walk()
    modified = False
    new_content_idx = 0

    # Traverse the AST to find function declarations
    def traverse(node):
        nonlocal new_content_idx, modified, content
        if node.type == "function_item":
            content, new_content_idx, was_modified = instrument_function(content, new_content_idx, node)
            if was_modified:
                modified = True
        for child in node.children:
            traverse(child)

    traverse(tree.root_node)

    if modified:
        # Write the modified content back to the file
        with open(file_path, "wb") as f:
            f.write(content)
        #print(f"Modified {file_path}")


def suspiciousness_weighted_descending(input_dict,order):
    """
    Takes a dictionary with string keys (test names) and a list of tuples. The first tuple element is method that is executed prior to test/assertion failure and the next tuple element is the weight of method, depending on proximity to the failed assertion 
    dict[str, list[tuple[str, int]]]
    Returns the list of all methods that were executed by the failed tests before assertion, sorted by their aggregated weights (descending).
    """
    weight_map = defaultdict(int)

    # Aggregate weights
    for executed_methods in input_dict.values():
        for executed_method, weight in executed_methods:
            weight_map[executed_method] += weight

    if order == 'ascending':
        # Sort by total weight descending, then alphabetically
        suspicious_methods = sorted(weight_map.items(), key=lambda x: (x[1], x[0]))
        return suspicious_methods
        # Print result
        #print("Weight-based ranking ascending")
        #for method, total_weight in suspicious_methods:
        #    print(f"{method}: {total_weight}")
    else:
        # Sort by total weight descending, then alphabetically
        suspicious_methods = sorted(weight_map.items(), key=lambda x: (-x[1], x[0]))
        return suspicious_methods
        # Print result
        #print("Weight-based ranking descending")
        #for method, total_weight in suspicious_methods:
        #    print(f"{method}: {total_weight}")



def instrument(project_dir):
    if not os.path.isdir(project_dir):
        print("Invalid directory path!")
        return

    parser = setup_parser()

    for root, _, files in os.walk(project_dir):
        for file in files:
            if file.endswith(".rs"):
                file_path = os.path.join(root, file)
                process_file(file_path, parser)


def build(project_dir):
    os.chdir(project_dir)
    subprocess.run(['cargo', 'build'], capture_output=True, check=False)


def get_call_stack(exec_path):
    result = subprocess.run([exec_path], capture_output=True, text=True, check=False)
    output = result.stdout
    lines = output.strip().split('\n')
    call_stack = [line.lstrip('* ').strip() for line in lines if line.startswith('*')]
    return call_stack, result.stderr, result.returncode


def apply_algorithm(call_stack):
    result = []
    current_list = []
    for item in call_stack:
        if "test" in item:
            if current_list:
                result.append(current_list)
            current_list = [item]
        else:
            if current_list:
                current_list.append(item)
    
    if current_list:
        result.append(current_list)
    
    my_map = {item[0]: [(val, i) for i, val in enumerate(item[1:], start=1)] for item in result}
    result_weighted_descending = suspiciousness_weighted_descending(my_map,"descending")
    probably_correct = {item[0]: item[1:] for item in result}
    probably_correct.popitem()
    merged_list = []
    for value_list in probably_correct.values():
        merged_list.extend(value_list)
    merged_list = list(set(merged_list))
    
    modified_list = []
    for string, weight in result_weighted_descending:
        if string in merged_list:
            modified_list.append((string, max(weight - 1, 0)))
        else:
            modified_list.append((string, weight))
    return modified_list, probably_correct


def uncomment(file_path, line_num):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    line = lines[line_num - 1]
    stripped_line = line.lstrip()
    print(f"[uncomment] file={file_path} line={line_num} before='{line.rstrip()}'")
    new_line = line[:line.index('//')] + line[line.index('//') + 2:].lstrip()
    lines[line_num - 1] = new_line
    with open(file_path, 'w') as f:
        f.writelines(lines)
    print(f"[uncomment] file={file_path} line={line_num} after='{new_line.rstrip()}'")


def comment_out(file_path, line_num):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    line = lines[line_num - 1]
    stripped_line = line.lstrip()
    leading_space = len(lines[line_num - 1]) - len(stripped_line)
    line_idx = line_num - 1
    lines[line_idx] = lines[line_idx][:leading_space] + '// ' + lines[line_idx][leading_space:]
    with open(file_path, 'w') as f:
        f.writelines(lines)


def disable_panic_test(call_stack, err, project_dir):
    match = re.search(r'panicked at\s+(.+?):(\d+):(\d+)', err)
    if match and "assertion" in err:
        file_path = match.group(1)
        line_num = int(match.group(2))
        comment_out(file_path, line_num)
        return file_path, line_num
    else:
        last_test = None
        for s in reversed(call_stack):
            if "test" in s.lower():
                last_test = s
                break
        print(f"[disable_panic_test] last_test from call_stack: {last_test}")
        if last_test:
            command = ['grep', '-rwn', '--include=*.rs',last_test, project_dir]
            result = subprocess.run(command, capture_output=True, text=True, check=True)
            input_data = result.stdout
            lines = input_data.strip().split('\n')
            function_call_pattern = r'^\s*[A-Za-z_][A-Za-z0-9_]*\s*\([^;{}]*\)\s*;\s*$'
            for line in lines:
                match = re.match(r'([^:]+):(\d+):\s*(.+)', line.strip())
                if match:
                    file_name, line_number, content = match.groups()
                    if re.search(function_call_pattern, content):
                        line_number = int(line_number)
                        comment_out(file_name, line_number)
                        return file_name, line_number


def _read_file_safe(path):
    try:
        with open(path, 'r', encoding='utf-8', errors='ignore') as f:
            return f.read()
    except Exception:
        return ""


def _find_rust_functions(project_dir, fn_name):
    """Return list of (file_path, code_text) for Rust functions named fn_name."""
    results = []
    try:
        pattern = f'^[[:space:]]*(pub[[:space:]]+)?fn[[:space:]]+{fn_name}\\b'
        rg = subprocess.run(
            [
                'grep','-R','-n','-E',
                '--include=*.rs',
                pattern
            ], cwd=project_dir, capture_output=True, text=True, check=False
        )
        for line in rg.stdout.splitlines():
            try:
                file_path, line_no, _ = line.split(':', 2)
                abs_path = os.path.join(project_dir, file_path)
                code = _read_file_safe(abs_path)
                results.append((abs_path, code))
            except Exception:
                continue
    except Exception:
        pass
    return results


def _find_c_functions(c_root_dir, fn_name):
    """Return list of (file_path, code_text) for C functions named fn_name."""
    results = []
    if not c_root_dir or not os.path.isdir(c_root_dir):
        return results
    try:
        rg = subprocess.run(
            [
                'grep','-R','-n',f'\b{fn_name}\s*\(', '--include=*.c'
            ], cwd=c_root_dir, capture_output=True, text=True, check=False
        )
        for line in rg.stdout.splitlines():
            try:
                file_path, line_no, _ = line.split(':', 2)
                abs_path = os.path.join(c_root_dir, file_path)
                code = _read_file_safe(abs_path)
                results.append((abs_path, code))
            except Exception:
                continue
    except Exception:
        pass
    return results


def _extract_failing_test_snippet(err):
    m = re.search(r'panicked at\s+(.+?):(\d+):(\d+)', err)
    if not m:
        return None, None
    file_path = m.group(1)
    try:
        line_no = int(m.group(2))
    except Exception:
        line_no = None
    snippet = None
    text = _read_file_safe(file_path)
    if text and line_no:
        lines = text.splitlines()
        start = max(0, line_no-5)
        end = min(len(lines), line_no+5)
        snippet = '\n'.join(lines[start:end])
    return file_path, snippet


def _replace_fn_in_file_with_treesitter(file_path, fn_name, new_fn_code):
    try:
        with open(file_path, 'rb') as f:
            content = f.read()
        parser = setup_parser()
        tree = parser.parse(content)
        root = tree.root_node
        target = None

        def visit(node):
            nonlocal target
            if target is not None:
                return
            if node.type in ('function_item', 'method_definition'):
                name_node = node.child_by_field_name('name')
                if name_node:
                    name = content[name_node.start_byte:name_node.end_byte].decode('utf-8')
                    if name == fn_name:
                        target = node
                        return
            for ch in node.children:
                visit(ch)

        visit(root)
        if not target:
            return False
        start = target.start_byte
        end = target.end_byte
        new_bytes = content[:start] + new_fn_code.encode('utf-8') + content[end:]
        with open(file_path, 'wb') as f:
            f.write(new_bytes)
        return True
    except Exception:
        return False


def _apply_model_edits(project_dir, model_text):
    """Parse model output with blocks of the form:
    FILE: <path-from-project-root>
    ```rust
    fn ... { ... }
    ```
    and apply per function replacement.
    """
    print(model_text)
    applied_any = False
    blocks = re.split(r'(?m)^FILE:\s*', model_text)
    print(f"[apply_model_edits] blocks_found={len(blocks)}")
    for idx, blk in enumerate(blocks):
        blk = blk.strip()
        if not blk:
            continue
        first_line_end = blk.find('\n')
        if first_line_end == -1:
            print(f"[apply_model_edits][{idx}] no newline in block header, skip")
            continue
        rel_path = blk[:first_line_end].strip()
        body = blk[first_line_end+1:]
        print(f"[apply_model_edits][{idx}] rel_path='{rel_path}' body_len={len(body)}")
        m = re.search(r'```[a-zA-Z]*\n([\s\S]*?)\n```', body)
        if not m:
            print(f"[apply_model_edits][{idx}] no fenced code block found, skip")
            continue
        code = m.group(1)
        print(f"[apply_model_edits][{idx}] code_len={len(code)}")
        # try get function name
        mname = re.search(r'^\s*(?:pub\s+)?fn\s+([A-Za-z0-9_]+)\b', code, re.M)
        if not mname:
            print(f"[apply_model_edits][{idx}] no fn name found, skip")
            continue
        fn_name = mname.group(1)
        cand1 = os.path.join(project_dir, rel_path)
        cand2 = os.path.join(project_dir, 'src', rel_path)
        file_path = cand1 if os.path.exists(cand1) else cand2
        exists = os.path.exists(file_path)
        print(f"[apply_model_edits][{idx}] target_fn='{fn_name}' file_path='{file_path}' exists={exists}")
        if not exists:
            print(f"[apply_model_edits][{idx}] target file does not exist, skip")
            continue
        if _replace_fn_in_file_with_treesitter(file_path, fn_name, code):
            print(f"[apply_model_edits] Applied model edit to {file_path}::{fn_name}")
            applied_any = True
        else:
            print(f"[apply_model_edits][{idx}] replace failed for {file_path}::{fn_name}")
    print(f"[apply_model_edits] applied_any={applied_any}")
    return applied_any


def _extract_rust_function_from_file(file_path: str, fn_name: str) -> str:
    """Return the exact function/method text for fn_name in file_path using tree-sitter; '' if not found."""
    try:
        with open(file_path, 'rb') as f:
            content = f.read()
        parser = setup_parser()
        tree = parser.parse(content)
        root = tree.root_node
        target = None

        def visit(node):
            nonlocal target
            if target is not None:
                return
            if node.type in ('function_item', 'method_definition'):
                name_node = node.child_by_field_name('name')
                if name_node:
                    name = content[name_node.start_byte:name_node.end_byte].decode('utf-8')
                    if name == fn_name:
                        target = node
                        return
            for ch in node.children:
                visit(ch)

        visit(root)
        if target is None:
            return ''
        return content[target.start_byte:target.end_byte].decode('utf-8', errors='ignore')
    except Exception as e:
        print(f"[_extract_rust_function_from_file] failed for {file_path}:{fn_name} -> {e}")
        return ''


# Global LLM client (DeepSeek)
_client = None

def _get_client():
    global _client
    if _client is not None:
        return _client
    base_url = os.getenv('DEEPSEEK_BASE_URL', 'https://api.deepseek.com/v1')
    api_key = os.getenv('DEEPSEEK_API_KEY')
    _client = OpenAI(base_url=base_url, api_key=api_key)
    return _client


# Optional: translation.json loader via decompose.py
_def_tr_map = None

def _load_translation_seq(path):
    global _def_tr_map
    if not path:
        return None
    try:
        # allow import without package install by extending sys.path
        root_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
        sys.path.append(root_dir)
        # also add pipeline directory because decompose.py imports `analyze` as top-level
        pipeline_dir = os.path.join(root_dir, 'pipeline')
        if pipeline_dir not in sys.path:
            sys.path.append(pipeline_dir)
        from pipeline.decompose.decompose import load_translation_seq as _lts
        tr = _lts(path)
        _def_tr_map = tr
        return tr
    except Exception as e:
        print(f"Failed to load translation.json: {e}")
        return None


def _lookup_from_tr_map(tr_map, name):
    if not tr_map:
        return None
    # direct key
    if name in tr_map:
        return tr_map[name]
    # match by unit.key
    for k, v in tr_map.items():
        try:
            if hasattr(v, 'key') and v.key and v.key == name:
                return v
        except Exception:
            pass
    # suffix match (e.g., main#test)
    for k, v in tr_map.items():
        try:
            if k.endswith(f"#{name}"):
                return v
        except Exception:
            pass
    return None


def fix_the_bug(sus_functions, project_dir, call_stack, err, tr_map=None):
    """
    Build a repair prompt, call deepseek-r1, and apply suggested fixes to Rust translations.
    sus_functions: list[str]
    """
    print("LLM is fixing suspicious functions:", sus_functions)
    if not sus_functions:
        return

    # Collect contexts (C from translation.json if available; Rust from project files by name)
    c_sections = []
    rust_sections = []

    for fn_name in sus_functions:
        unit = _lookup_from_tr_map(tr_map, fn_name) if tr_map else None
        # C source
        if unit:
            c_code = getattr(unit, 'source_code', '') or ''
            c_sections.append((fn_name, getattr(unit, 'file', None), c_code))
        else:
            c_sections.append((fn_name, None, ''))
        # Rust source strictly from project files
        r_found = _find_rust_functions(project_dir, fn_name)
        if r_found:
            abs_path, _ = r_found[0]
            relpath = os.path.relpath(abs_path, project_dir)
            fn_code = _extract_rust_function_from_file(abs_path, fn_name)
            rust_sections.append((fn_name, relpath, fn_code))
        else:
            rust_sections.append((fn_name, None, ''))

    test_file, test_snippet = _extract_failing_test_snippet(err)

    # Compose prompt
    intro = (
        "I would like you to act as an expert in C and Rust programming languages and help with repairing some C-to-Rust translations I have. "
        "I am going to pass you (1) the original C code, (2) the corresponding Rust translations, and (3) the failing test. "
        "Please try to pinpoint the issue given the provided data and only change Rust translations if necessary. \n\n"
    )

    parts = [intro]

    parts.append("Failing run stderr:\n" + (err if err else "") + "\n\n")

    if test_file or test_snippet:
        parts.append("Failing test (context):\n")
        if test_file:
            parts.append(f"FILE: {test_file}\n")
        if test_snippet:
            parts.append("```rust\n" + test_snippet + "\n```\n\n")

    parts.append("Original C code for suspicious functions:\n")
    for fn_name, path, code in c_sections:
        parts.append(f"FUNCTION: {fn_name}\n")
        parts.append(f"FILE: {path or 'UNKNOWN'}\n")
        parts.append("```c\n" + (code if code else "/* not found in translation.json */") + "\n```\n\n")

    parts.append("Rust translations for suspicious functions:\n")
    for fn_name, relpath, code in rust_sections:
        parts.append(f"FUNCTION: {fn_name}\n")
        parts.append(f"FILE: {relpath or 'UNKNOWN'}\n")
        parts.append("```rust\n" + (code if code else "// not found in project files") + "\n```\n\n")

    parts.append(
        "Your task: Diagnose the root cause and provide corrected Rust implementations ONLY for the functions that need changes.\n"
        "Output format: For each changed function, emit a block in the following format to allow precise application:\n"
        "FILE: <project-relative-path-to-rust-file>\n"
        "```rust\n"
        "pub fn <name>(...) { /* full corrected function definition */ }\n"
        "```\n"
        "Do not include any additional commentary. Only include changed functions."
    )

    prompt = ''.join(parts)
    print(prompt)

    # Call model
    try:
        client = _get_client()
        resp = client.chat.completions.create(
            model='deepseek-reasoner',
            messages=[{"role": "user", "content": prompt}],
            stream=False,
            temperature=0.0,
        )
        content = resp.choices[0].message.content
    except Exception as e:
        print(f"LLM call failed: {e}")
        return

    if not content:
        print("Empty LLM response")
        return

    # Apply edits
    applied = _apply_model_edits(project_dir, content)
    if not applied:
        print("No applicable edits found in LLM response")


def get_sus_functions(call_stack, white_list, k):
    sus = []
    for st in reversed(call_stack):
        if k <= 0:
            return sus
        if st in white_list:
            continue
        else:
            sus.append(st)
            k -= 1
    return sus


def run():
    """Walk through the project directory and process all .rs files."""
    args = sys.argv[1:]
    project_dir = args[0]
    exec_path = f"./target/debug/{args[1]}"
    tr_json = args[2] if len(args) > 2 else os.getenv('TRANSLATION_JSON')
    tr_map = _load_translation_seq(tr_json) if tr_json else None

    instrument(project_dir)
    commented_tests = []

    while True:
        build(project_dir)
        call_stack, err, ret = get_call_stack(exec_path)
        print(f"[run] build+run ret={ret} call_stack_len={len(call_stack)} err_len={len(err) if err else 0}")
        if not ret:
            print("Every failed test is commented out")
            break
        file, line_no = disable_panic_test(call_stack, err, project_dir)
        commented_tests.append((file, line_no))
        print("Comment ", file, line_no)
    
    idx = 0
    length = len(commented_tests)
    print("\nStart fixing ...\n")
    white_list = []

    while idx < length:
        f, l = commented_tests[idx]
        print(f"[run] restoring test at {f}:{l}")
        uncomment(f,l)
        build(project_dir)
        call_stack, err, ret = get_call_stack(exec_path)
        if ret == 0:
            idx += 1
            continue
        # Use LLM to suggest fixes for top-3 suspicious functions
        sus = get_sus_functions(call_stack, white_list, 3)
        print(f"[run] sus_candidates={sus}")
        fix_the_bug(sus, project_dir, call_stack, err, tr_map)

        build(project_dir)
        call_stack, err, ret = get_call_stack(exec_path)
        print(f"[run] after-fix ret={ret} call_stack_len={len(call_stack)}")

        if ret:
            print("Fix was not effective")
            comment_out(f,l)
        else:
            print("Fixed")
            white_list.append(call_stack[-1])
        idx += 1
        white_list = list(set(white_list))
        print("white list:", white_list, "\n")
    
    print("Done")


if __name__ == "__main__":
    """ python algorithm.py PROJECT_DIR TEST_NAME [TRANSLATION_JSON] """
    run()
