#ifndef TOKENS_H
#define TOKENS_H

#include <string>

/* This header defines the token types created by the Lexer/Tokenizer. */
/* The token structure is also defined. */

enum token_kind {
    /* PLACEHOLDER VALUE */
    TOKEN_PLACEHOLDER,

    /* KEYWORDS */
    /* Control Flow */
    TOKEN_IF,
    TOKEN_ELSE,
    /* Debugging */
    TOKEN_ASSERT,
    TOKEN_AFFIRM,
    /* Data Types */
    TOKEN_INTEGER_DEFAULT,
    TOKEN_INTEGER_8,
    TOKEN_INTEGER_16,
    TOKEN_INTEGER_32,
    TOKEN_INTEGER_64,
    TOKEN_UNSIGNED_INTEGER_DEFAULT,
    TOKEN_UNSIGNED_INTEGER_8,
    TOKEN_UNSIGNED_INTEGER_16,
    TOKEN_UNSIGNED_INTEGER_32,
    TOKEN_UNSIGNED_INTEGER_64,
    TOKEN_FLOAT_DEFAULT,
    TOKEN_FLOAT_8,
    TOKEN_FLOAT_16,
    TOKEN_FLOAT_32,
    TOKEN_FLOAT_64,
    TOKEN_CHARACTER,
    TOKEN_BOOLEAN,

    /* OPERATORS */
    /* Arithmetic */
    TOKEN_ADDITION,
    TOKEN_SUBTRACTION,
    TOKEN_MULTIPLICATION,
    TOKEN_DIVISION,
    TOKEN_EXPONENTIATION,
    TOKEN_LOGARITHM,
    TOKEN_SHIFT_LEFT,
    TOKEN_SHIFT_RIGHT,
    /* Logic */
    TOKEN_LOGIC_NOT,
    TOKEN_LOGIC_AND,
    TOKEN_LOGIC_OR,
    TOKEN_LOGIC_XOR,
    TOKEN_LOGIC_NAND,
    TOKEN_LOGIC_NOR,
    TOKEN_LOGIC_IF,
    TOKEN_LOGIC_IFF,

    /* IDENTIFIERS */
    TOKEN_IDENTIFIER,

    /* NUMERAL LITERALS */
    TOKEN_LITERAL_INTEGER,
    TOKEN_LITERAL_UNSIGNED_INTEGER,
    TOKEN_LITERAL_FLOAT,
    TOKEN_LITERAL_CHARACTER,
    TOKEN_LITERAL_BOOLEAN,

    /* STRING LITERALS */
    TOKEN_LITERAL_STRING,

    /* WHITESPACE AND COMMENTS */
    TOKEN_WHITESPACE,
    TOKEN_SINGLE_COMMENT,
    TOKEN_MULTI_COMMENT,

    /* OTHER */
    /* For tokens that do not match any valid token kind. */
    TOKEN_INVALID,
    TOKEN_EOF,
};

/* Represents a "word" in our language. 
 * Essentially, a unit of meaning.
 */
typedef struct token_t {
    token_kind kind;
    int position;
    std::string value;
};

#endif