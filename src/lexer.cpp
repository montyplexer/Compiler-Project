#include <string>
#include <cctype>
#include "lexer.h"
#include "tokens.h"

/* CONSTRUCTORS */
Lexer::Lexer() {
    _text = "";
    _position = 0;
}

Lexer::Lexer(std::string text) {
    _text = text;
    _position = 0;
}

/* PUBLIC FUNCTIONS */

void Lexer::set_text(std::string text) { 
    _text = text;
    _position = 0;
}

token_t Lexer::next_token() {

    token_t token = { TOKEN_PLACEHOLDER, _position, std::string()};

    /* Numeral Literals */
    if (std::isdigit(_current())) {
        int start = _position;

        while (std::isdigit(_current())) {
            _next();
        }

        /* Integer Literal */
        if (std::isspace(_current())) {
            token.kind = TOKEN_LITERAL_INTEGER;
            token.value = _text.substr(start,_position-start);
            return token;
        }

        /* Float Literal */
        if (_current() == '.') {
            while (std::isdigit(_current())) {
                _next();
            }

            if (std::isspace(_current())) {
                token.kind = TOKEN_LITERAL_FLOAT;
                token.value = _text.substr(start,_position-start);
                return token;
        }

        }
    }
 }

/* PRIVATE FUNCTIONS */

char Lexer::_current() {
    if (_position >= _text.length()) { return '\0'; }
    else return _text[_position];
}

void Lexer::_next() { _position++; }
