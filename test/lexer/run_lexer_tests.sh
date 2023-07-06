#!/bin/bash

# Run unit tests for the Lexer
# For each test, determine if the actual output matched the expected output

# Test 1 - Determine type of token of a variety of literals (all on a single line)
# Test 2 - Checks if single-line comments are ignored AND only a single EOF token is printed
# Test 3 - Checks if multi-line comments are ignored AND only a single EOF token is printed
# Test 4 - Empty files should produce just one token of type EOF
# Test 5 - Test that all operators show up as valid operator tokens, and that operator symbols are ignored in comments

num_of_tests=5

for ((i = 1; i <= $num_of_tests; i++)) do
    echo "Test ${i}"
    ./test_lexer.exe "src${i}.txt"
    if diff -w "src${i}.exp" "src${i}.out"; then
        echo "Passed Test ${i}!"
    else 
        echo "FAILED TEST ${i}!"
        echo "Stopping..."
        exit 1
    fi
done