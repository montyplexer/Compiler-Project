#!/bin/bash

# Run unit tests for the Lexer
# For each test, determine if the actual output matched the expected output

# Test 1 - Determine type of token of a variety of literals (all on a single line)
echo "Test 1"
./test_lexer.exe src1.txt
diff -w src1.exp src1.out

# Test 2 - Checks if single-line comments are ignored AND only a single EOF token is printed
echo "Test 2"
./test_lexer.exe src2.txt
diff -w src2.exp src2.out

# Test 3 - Checks if multi-line comments are ignored AND only a single EOF token is printed
echo "Test 3"
./test_lexer.exe src3.txt
diff -w src3.exp src3.out

# Test 4 - Empty files should produce just one token of type EOF
echo "Test 4"
./test_lexer.exe src4.txt
diff -w src4.exp src4.out

# Test 5 - Test that all operators show up as valid operator tokens, and that operator symbols are ignored in comments
echo "Test 5"
./test_lexer.exe src5.txt
diff -w src5.exp src5.out