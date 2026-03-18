import json
import argparse
from readability_c import parse_c_code, metrics_r2i
from readability_rust import parse_rust_code,metrics_r2i_rust
from safety_check import analyze_rust_code_for_raw_pointers,extract_function_calls,get_rust_function_definitions
import re
from error_parser import count_warnings_by_class,process_file,get_msg_from_line,count_errors_by_class
import os
def extract_extern_c_functions(source_code):
    """
    Extracts function names from an `extern "C"` block in Rust code.
    """
    extern_c_functions = []
    # Pattern to match the extern "C" block
    pattern = r'extern "C" {([^}]*)}'
    match = re.search(pattern, source_code, re.MULTILINE | re.DOTALL)
    
    if match:
        extern_block = match.group(1)
        # Pattern to find function definitions within the extern block
        function_pattern = r'fn\s+(\w+)\s*\('
        extern_c_functions = re.findall(function_pattern, extern_block)

    
    return extern_c_functions


# Define the command-line argument parser
parser = argparse.ArgumentParser(description='Analyze application.json for code metrics.')
parser.add_argument('--app', type=str, help='Path to the application.json file', required=True)
parser.add_argument('--compile_result', type=str, help='Path to the compile result text file', required=True)
parser.add_argument('--src_dir', type=str, help='Path to the src_dir', required=True)
# Parse the command-line arguments
args = parser.parse_args()

# Read the application.json file
with open(args.app, 'r') as file:
    application_data = json.load(file)

with open(args.compile_result, 'r') as compile_file:
    compile_log = compile_file.read()

warning_positions = count_warnings_by_class(compile_log)
for file in list(warning_positions.keys()):
    full_path = os.path.join(args.src_dir, f"{file}.rs")
    warning_positions[full_path] = warning_positions.pop(file)

error_positions= count_errors_by_class(compile_log)
for file in list(error_positions.keys()):
    full_path = os.path.join(args.src_dir, f"{file}.rs")
    error_positions[full_path] = error_positions.pop(file)


# Process each code fragment
for item in application_data:
    code = item.get("c_code")
    tree = parse_c_code(code)
    metrics = metrics_r2i(tree, code)
    item["C-properties"] = metrics
    transpilation = item.get("transpilation", [])
    if transpilation and transpilation[0]:
        rust_code = transpilation[0]
        tree = parse_rust_code(rust_code) # Take the first transpilation entry
        metrics = metrics_r2i_rust(tree,rust_code)  # Apply the Rust code analysis
        item["Transpilation-properties"] = metrics 
        total_raw_pointer_count = analyze_rust_code_for_raw_pointers(rust_code) # Add the results to the item
        item["Transpilation-properties"]['total_raw_pointer_count'] = total_raw_pointer_count
        function_calls = extract_function_calls(rust_code)
        file_path = transpilation[1] 
        with open(file_path, 'r') as rust_file:
                rust_file_content = rust_file.read()
                extern_c_functions = extract_extern_c_functions(rust_file_content)
            
            # Check if any extern "C" functions are called in the main transpilation code
        called_extern_functions = [func for func in extern_c_functions if func in function_calls]
            
            # Add the results to "Transpilation-properties"
        item["Transpilation-properties"]["called_extern_functions"] =  called_extern_functions
        function_names=get_rust_function_definitions(rust_code)
        if file_path in warning_positions and item.get("fragment_type")=="Function":
            _, warning_matches = process_file(file_path, warning_positions[file_path], compile_log)
            warnings_by_function = [
                {
                "function_name": func_name.decode('utf-8') if isinstance(func_name, bytes) else func_name,
                "warning_message": get_msg_from_line(compile_log, pos[2]) 
                }
                for match_group in warning_matches.values()
                for pos, func_name, ns, ne in match_group
            ]
            
            # Append warnings to the matching functions in Transpilation-properties
            for func_warning in warnings_by_function:
                func_name = func_warning["function_name"]
                if func_name in function_names:
                    
                    if "warnings" not in item["Transpilation-properties"]:
                        item["Transpilation-properties"]["warnings"] = []
                    item["Transpilation-properties"]["warnings"].append(func_warning)
        if file_path in error_positions and item.get("fragment_type")=="Function":
            _, error_matches = process_file(file_path,error_positions[file_path], compile_log)
            errors_by_function = [
                {
                "function_name": func_name.decode('utf-8') if isinstance(func_name, bytes) else func_name,
                "error_message": get_msg_from_line(compile_log, pos[2]) 
                }
                for match_group in error_matches.values()
                for pos, func_name, ns, ne in match_group
            ]
            
            # Append warnings to the matching functions in Transpilation-properties
            for func_error in errors_by_function:
                func_name = func_error["function_name"]
                if func_name in function_names:
                    
                    if "errors" not in item["Transpilation-properties"]:
                        item["Transpilation-properties"]["errors"] = []
                    item["Transpilation-properties"]["errors"].append(func_error)


# Print or save the modified data (optional)
output_file = args.app
with open(output_file, 'w') as file:
    json.dump(application_data, file, indent=4)

# print(f"Analysis complete. Output saved to {output_file}")
