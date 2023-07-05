#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "tokens.h"
#include "syntax_nodes.h"

/* The parser is the second phase of a compiler. It's purpose is to build an abstract syntax tree (AST) from the tokens produced by the lexer.
 * By applying production rules while building the AST, the parser also checks that the code is syntactically correct. 
 * If the tree cannot be built, then the code has a syntax error.
 *
 * @author Monty
 */

class Parser {

public:

    /* Default constructor */
    Parser();
    /* Create with ready token list */
    Parser(std::vector<token_t> token_list);

    /* Gives the Parser a new set of tokens with which to attempt to generate a new AST */
    void set_tokens(std::vector<token_t> token_list);

private:

    /* PRIVATE FIELDS */

    /* The parser is given a list of tokens as input */
    std::vector<token_t> _tokens;
    /* Root node of the abstract syntax tree */
    syntax_node_t _root;
    /* Current position in the token list */
    int _position;
    /* Is at end of token list? */
    int _end_of_tokens = false;

    /* PRIVATE FUNCTIONS */

    /* Changes state of Parser back to default, and disconnects any token stream */
    void _reset();

    /* Returns the token at the current position */
    token_t _current();
    /* Moves position to next the token */
    void _next();
    /* Looks at next token */
    token_t _peek();
    /* Looks at n token ahead of current token */
    token_t _peekn(int n);
    /* Move position over by n tokens */
    void _seekn(int n);

};

#endif