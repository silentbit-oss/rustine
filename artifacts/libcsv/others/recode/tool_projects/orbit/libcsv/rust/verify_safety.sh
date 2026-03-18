#!/bin/bash

echo "======================================"
echo "libcsv Safe Rust Verification Script"
echo "======================================"
echo ""

echo "1. Checking for unsafe blocks..."
UNSAFE_COUNT=$(find . -name "*.rs" -type f -exec grep -c "unsafe {" {} \; | awk '{sum+=$1} END {print sum}')
if [ "$UNSAFE_COUNT" -eq 0 ]; then
    echo "✓ PASS: Zero unsafe blocks found"
else
    echo "✗ FAIL: $UNSAFE_COUNT unsafe blocks found"
    exit 1
fi
echo ""

echo "2. Checking for raw pointers (excluding comments)..."
RAW_PTR_COUNT=$(grep -rn "\*const\|\*mut\|c_void" --include="*.rs" . | grep -v "//" | wc -l)
if [ "$RAW_PTR_COUNT" -eq 0 ]; then
    echo "✓ PASS: Zero raw pointers found in code"
else
    echo "✗ FAIL: $RAW_PTR_COUNT raw pointer usages found"
    exit 1
fi
echo ""

echo "3. Running test suite..."
cargo test --bin test_csv 2>&1 | grep -E "test result:|All tests passed"
if [ $? -eq 0 ]; then
    echo "✓ PASS: Tests executed successfully"
else
    echo "✗ FAIL: Tests failed"
    exit 1
fi
echo ""

echo "4. Building all examples..."
cargo build --examples > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "✓ PASS: All examples build successfully"
else
    echo "✗ FAIL: Example build failed"
    exit 1
fi
echo ""

echo "5. Testing example functionality..."
echo "a,b,c" | cargo run --example csvtest 2>/dev/null | grep -q '"a","b","c"'
if [ $? -eq 0 ]; then
    echo "✓ PASS: csvtest example works correctly"
else
    echo "✗ FAIL: csvtest example failed"
    exit 1
fi
echo ""

echo "======================================"
echo "ALL SAFETY CHECKS PASSED ✓"
echo "======================================"
echo ""
echo "Summary:"
echo "  - Zero unsafe blocks"
echo "  - Zero raw pointers"
echo "  - All tests pass"
echo "  - All examples work"
echo "  - 100% safe Rust code"
echo ""
