#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "lexer.h"
#include "tokens.h"

/* CONSTRUCTORS */
Lexer::Lexer() {
    _text = "";
    _position = 0;
    _end_of_file = false;
}

Lexer::Lexer(std::string text) {
    _text = text;
    _position = 0;
    _end_of_file = false;
}

/* PUBLIC FUNCTIONS */

void Lexer::set_text(std::string text) { 
    _text = text;
    _position = 0;
    _end_of_file = false;
}

/* Next token will generate either a...
 * - TOKEN_IDENTIFIER
 * - TOKEN_OPERATOR
 * - TOKEN_LITERAL
 * - TOKEN_KEYWORD
 * - TOKEN_PUNCTUAL
 */
token_t Lexer::next_token() {

    //printf("HERE ");

    /* Placeholder token will be filled with the appropriate kind of token */
    token_t token = { TOKEN_PLACEHOLDER, _position, std::string()};

    /* END OF FILE */
    if (_position >= _text.length()) {
        token.kind = TOKEN_EOF;
        _end_of_file = true;
        return token;
    }

    /* Ignore whitespace (don't make whitespace tokens) */
    while (std::isspace(_current())) {
        _next();
    }

    /* PUNCTUALS */
    if (_current() == ';' || _current() == '(' || _current() == ')') {
        token.kind = TOKEN_PUNCTUAL;
        token.value = _current();
        return token;
    }

    /* OPERATORS */
    // Note the order of the list is important. Longest operators are handled first.

    /* Logic operators*/
    std::vector<std::string> logic_operators_list = {"<->", // 3 char long
                                                "&&", "||", "^^", "!&", "!|", "->", // 2 char long
                                                "!", // 1 char long
                                                };
    for (std::string opword : logic_operators_list) {
        token = _form_operator_token(opword);
        if (token.kind != TOKEN_PLACEHOLDER) {
            return token;
        }
    }

    /* Arithmetic operators */
    std::vector<std::string> arithmetic_operators_list = {"<<", ">>", // 2 char long
                                                     "+", "-", "*", "/", "%", "^" // 1 char long
                                                    };
    for (std::string opword : arithmetic_operators_list) {
        token = _form_operator_token(opword);
        if (token.kind != TOKEN_PLACEHOLDER) {
            return token;
        }
    }

    /* Comparison operators */
    std::vector<std::string> comparison_operators_list = {"==", "!=", "<=", ">=", // 2 char long
                                                     "<", ">" // 1 char long
                                                     };
    for (std::string opword : comparison_operators_list) {
        token = _form_operator_token(opword);
        if (token.kind != TOKEN_PLACEHOLDER) {
            return token;
        }
    }

    /* Keywords */
    // TODO: make separate tokens for type declaration (we need to account for pointers and mutability with '*' and '!')
    std::vector<std::string> keyword_list = { "true", "false", // boolean literals (not being treated like keywords)
                                         "if", "else", // control flow
                                         "int", "i8", "i16", "i32", "i64", // integer declaration
                                         "uns", "u8", "u16", "u32", "u64", // unsigned integer declaration
                                         "flt", "f8", "f16", "f32", "f64", // float declaration
                                         };
    
    for (std::string keyword : keyword_list) {
        token = _form_keyword_token(keyword);
        if (token.kind != TOKEN_PLACEHOLDER) {
            if (token.value == "true" || token.value == "false") { token.kind = TOKEN_LITERAL_BOOLEAN; }
            return token;
        }
    }


    /* Identifiers */
    // REGEX: /(?<!\S)([A-Z]|[a-z]|[_])+([A-Z]|[a-z]|[_]|[0-9])*(?!\S)*/
    if (std::isalpha(_current()) || _current() == '_') {
        int start = _position;
        while (std::isalpha(_current()) ||
               std::isdigit(_current()) ||
               _current() == '_') {
            _next();
        }
        token.kind = TOKEN_IDENTIFIER;
        token.value = _text.substr(start,_position-start);
        return token;
    }

    /* Numeral Literals */
    /* There are three cases: 
     * 1. starts with digit and has no period (integer)
     *  - (?<!\S)([0-9])+(?!\S)
     * 2. starts with digit and has one period (float)
     *  - (?<!\S)[0-9]+[.][0-9]*(?!\S)
     * 3. starts with period and ends with a digit (float)
     *  - (?<!\S)[.][0-9]+(?!\S)
     * */
    /* Case 1 and 2 */
    if (std::isdigit(_current())) {
        // Record current position
        int start = _position;
        // Continue until end of number
        while (std::isdigit(_current())) {
            _next();
        }
        // Numeral does not terminate with period, so it must be a whole number
        if (!(_current() == '.')) {
            token.kind = TOKEN_LITERAL_INTEGER;
            token.value = _text.substr(start,_position-start);
            return token;
        // Otherwise, this numeral is a float
        } else {
            // Skip over period
            _next();
            // Continue over fractional part of decimal number
            while (std::isdigit(_current())) {
                _next();
            }
            token.kind = TOKEN_LITERAL_FLOAT;
            token.value = _text.substr(start,_position-start);
            return token;
        }
    }
    /* Case 3 */
    if (_current() == '.' && std::isdigit(_peek())) {
        // Record current position
        int start = _position;
        // Skip over period
        _next();
        // Continue until end of fractional number
        while (std::isdigit(_current())) {
            _next();
        }
        token.kind = TOKEN_LITERAL_FLOAT;
        token.value = _text.substr(start,_position-start);
        return token;
    }
    

    /* Something went wrong! */
    token.kind = TOKEN_INVALID;
    token.value = _current();
    _next();
    return token;
 }

/* PRIVATE FUNCTIONS */

char Lexer::_current() {
    if (_position >= _text.length()) { return '\0'; }
    else return _text[_position];
}

char Lexer::_peek() {
    if (_position+1 >= _text.length()) { return '\0'; }
    else return _text[_position+1];
}

char Lexer::_peekn(int n) {
    if (_position+n >= _text.length() || _position+n < 0) { return '\0'; }
    else return _text[_position+n];
}

void Lexer::_next() { _position++; }

void Lexer::_seekn(int n) { _position += n; }

bool Lexer::is_lexing() { return !_end_of_file; }

std::string Lexer::print_token(token_t token) {
    std::string str_rep = "<" + std::to_string(token.position) + ":" + print_token_kind(token.kind);
    if (token.value != "") {
        str_rep += ":" + token.value;
    }
    str_rep += ">";
    return str_rep;
}

token_t Lexer::_form_keyword_token(std::string keyword) {
    token_t token = { TOKEN_PLACEHOLDER, _position, std::string() };
    char end_char = _peekn(keyword.length());
    // Check that substring actually matches keyword, AND it is not followed by an alphanumerical or underscore character
    if (_text.substr(_position,keyword.length()) == keyword && 
        !std::isalnum(end_char) &&
        end_char != '_') {
        token.kind = TOKEN_KEYWORD;
        token.value = _text.substr(_position,keyword.length());
        _seekn(keyword.length());
    }
    return token;
}

token_t Lexer::_form_operator_token(std::string opword) {
    token_t token = { TOKEN_PLACEHOLDER, _position, std::string() };
    char end_char = _peekn(opword.length());
    // Check that substring actually matches keyword, AND it is followed by whitespace, an alphanumerical, paranthesis or underscore character
    if (_text.substr(_position,opword.length()) == opword && 
        (std::isalnum(end_char) || std::isspace(end_char) || end_char == '_' || end_char == '(' || end_char == ')')) {
        token.kind = TOKEN_OPERATOR;
        token.value = _text.substr(_position,opword.length());
        _seekn(opword.length());
    }
    return token;
}

// TODO: token_t Lexer::_form_type_declaration_token(std::string typeword) {}

