#ifndef LEXER_H
#define LEXER_H

/* The lexer/tokenizer is the first phase of a compiler. It's purpose is to derived the smallest units of meaning from the source code.
 * It is also called the scanner because it traverses the source code line-by-line, creating tokens for the next phase, the parser.
 *
 * @author Monty
 */

#include <string>
#include "tokens.h"

class Lexer {

public :

    /* CONSTRUCTORS*/

    /* Default Constructor */
    Lexer();
    /* Constructor initialized with certain text */
    Lexer(std::string text);

    /* PUBLIC FUNCTIONS */

    /* Change text that Lexer tokenizes */
    void set_text(std::string text);
    /* Get next token */
    token_t next_token();
    /* Print out contents of a token made by the Lexer */
    static std::string print_token(token_t token);
    /* Returns the state of the Lexer (whether it is still lexing) */
    bool is_lexing();

private :
    
    /* PRIVATE FIELDS */

    /* Text being tokenized by the Lexer */
    std::string _text;
    /* Current position of the Lexer */
    int _position;
    /* Is at end of text? */
    int _end_of_file = false;

    /* PRIVATE FUNCTIONS */

    /* Returns the character at the current position */
    char _current();
    /* Moves position to next character */
    void _next();
    /* Looks at next character */
    char _peek();
    /* Looks at n characters ahead of current */
    char _peekn(int n);
    /* Move position over by n */
    void _seekn(int n);
    /* Utility function to check for a given keyword at current position
     * If forming the keyword fails, the function returns a placeholder token. */
    token_t _form_keyword_token(std::string keyword);
    /* Utility function to check for a given operator at current position
     * If forming the operator fails, the function returns a placeholder token. */
    token_t _form_operator_token(std::string opword);
    // TODO: token_t _form_type_declaration_token(std::string typeword);
};

#endif