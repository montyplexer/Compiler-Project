#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "tokens.h"

class Lexer {

public :

    /* CONSTRUCTORS*/

    /* Default Constructor */
    Lexer() {};
    /* Constructor initialized with certain text */
    Lexer(std::string text) {};

    /* PUBLIC FUNCTIONS */

    /* Change text that Lexer tokenizes */
    void set_text(std::string text);
    /* Get next token */
    token_t next_token() {};

private :
    
    /* PRIVATE FIELDS */

    /* Text being tokenized by the Lexer */
    std::string _text;
    /* Current position of the Lexer */
    int _position;

    /* PRIVATE FUNCTIONS */

    /* Returns the character at the current position */
    char _current() {};
    /* Moves position to next character */
    void _next() {};

};

#endif