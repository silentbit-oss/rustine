#!/bin/bash

# Find all .c and .h files (case-insensitive) and replace assert( with my_assert(
find . -type f \( -iname "*.c" -o -iname "*.h" \) -exec sed -i '' 's/assert(/my_assert(/g' {} +

CODE_TO_ADD="#include <assert.h>\n#include <stdio.h>\n#define my_assert(expr) do { printf(\"assert_called\\\n\"); assert(expr);} while (0)\n"

# Find all .c files in the current directory and its subdirectories, and add the code
find . -name "*.c" -print0 | while IFS= read -r -d $'\0' file; do
    echo "Adding code to: $file"
    sed -i '' "1s/^/$CODE_TO_ADD/" "$file"
done

echo "Replacement of assert( with my_assert( and macro addition completed."
