import os
import json
from c_analysis import extract_functions_and_calls 

def analyze_project(files, output_path):
    file_functions = {}  # Maps each file to its functions
    function_to_file = {}  # Maps each function to the file where it is defined
    caller_callee_pairs = []  # Stores all caller-callee pairs

    # First Pass: Collect all function definitions across provided files
    for file_path in files:
        # Check if it's a .c file and if it is a file (not a directory)
        if file_path.endswith('.c') and os.path.isfile(file_path):
            file_name = os.path.basename(file_path)
            file_key = file_name.split('.')[0]

            # Run extract_functions_and_calls to get function definitions and calls
            with open(file_path, 'r') as f:
                source_code = f.read()
            functions_in_file = extract_functions_and_calls(source_code)
            
            # Record functions defined in this file
            file_functions[file_key] = list(functions_in_file.keys())
            
            # Populate function_to_file with each function’s defining file
            for func in functions_in_file.keys():
                function_to_file[func] = file_key

    # Second Pass: Generate caller-callee pairs using function definitions
    for file_key, functions in file_functions.items():
        # Use the exact file path in the `files` list
        file_path = next((fp for fp in files if os.path.basename(fp).split('.')[0] == file_key), None)
        if not file_path:
            continue  # Skip if file_path is not found for some reason
        
        # Reload source and extract caller-callee relationships
        with open(file_path, 'r') as f:
            source_code = f.read()
        functions_in_file = extract_functions_and_calls(source_code)

        for caller, callees in functions_in_file.items():
            caller_with_prefix = f"{file_key}::{caller}"
            for callee in callees:
                # Determine the prefix for each callee based on its defining file
                callee_prefix = function_to_file.get(callee)
                if callee_prefix:
                    # Prefix with defining file if it's a project-defined function
                    callee_with_prefix = f"{callee_prefix}::{callee}"
                else:
                    # External function, no prefix
                    callee_with_prefix = callee

                caller_callee_pairs.append([caller_with_prefix, callee_with_prefix])

    # Prepare the separate caller-callee lists in the final JSON structure
    final_output = []
    for file_key in file_functions.keys():
        file_path = next((fp for fp in files if os.path.basename(fp).split('.')[0] == file_key), None)
        if not file_path:
            continue

        # Gather callees for functions in this file
        callees = [
            pair for pair in caller_callee_pairs if pair[0].startswith(f"{file_key}::")
        ]

        # Gather callers for functions in this file
        callers = [
            pair for pair in caller_callee_pairs if pair[1].startswith(f"{file_key}::")
        ]

        # Add each file’s data to the output
        file_data = {
            'path': file_path,
            'callers': callers,
            'callees': callees
        }
        final_output.append(file_data)

    # Write to JSON file or return final_output
    with open(output_path, 'w') as f:
        json.dump(final_output, f, indent=4)
    
    return final_output
