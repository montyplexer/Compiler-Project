#ifndef TOKENS_H
#define TOKENS_H

#include <string>

/* This header defines the token types created by the lexer/tokenizer. The token structure is also defined here. 
 * Tokens can be thought of as words in a human language. Much like we build words out of letters, the lexer builds tokens out of characters in the source code.
 * @author Monty
 */

enum token_kind {
    TOKEN_PLACEHOLDER,
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_LITERAL_INTEGER,
    TOKEN_LITERAL_FLOAT,
    TOKEN_LITERAL_BOOLEAN,
    TOKEN_LITERAL_CHARACTER,
    TOKEN_LITERAL_STRING,
    TOKEN_OPERATOR,
    TOKEN_PUNCTUAL,
    TOKEN_INVALID,
    TOKEN_EOF,
};

/* Used for debugging */
std::string print_token_kind(token_kind kind) {
    switch (kind) {
        case TOKEN_PLACEHOLDER: return "PLACEHOLDER";
        case TOKEN_KEYWORD: return "KEYWORD";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_LITERAL_INTEGER: return "INTEGER";
        case TOKEN_LITERAL_FLOAT: return "FLOAT";
        case TOKEN_LITERAL_BOOLEAN: return "BOOLEAN";
        case TOKEN_LITERAL_CHARACTER: return "CHARACTER";
        case TOKEN_LITERAL_STRING: return "STRING";
        case TOKEN_OPERATOR: return "OPERATOR";
        case TOKEN_PUNCTUAL: return "PUNCTUAL";
        case TOKEN_INVALID: return "INVALID";
        case TOKEN_EOF: return "EOF";

        default: return "Add kind to debug function...";
    }
}

/* Represents a "word" in our language. 
 * Essentially, a unit of meaning.
 */
typedef struct token_t {
    token_kind kind;
    int position;
    std::string value;
};

#endif