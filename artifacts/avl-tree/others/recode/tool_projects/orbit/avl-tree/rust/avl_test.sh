#!/bin/bash
# AVL Tree Test Runner
# Builds and runs the comprehensive test suite

set -e  # Exit on error

echo "Building AVL tree test suite..."
cargo build --bin avl_test

echo ""
echo "Running tests..."
echo "================"
./target/debug/avl_test

exit_code=$?

if [ $exit_code -eq 0 ]; then
    echo ""
    echo "All tests passed successfully!"
else
    echo ""
    echo "Tests failed with exit code: $exit_code"
fi

exit $exit_code
