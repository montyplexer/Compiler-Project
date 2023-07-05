#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "lexer.h"
#include "tokens.h"

/* CONSTRUCTORS */
Lexer::Lexer() { set_text( std::string() ); }

Lexer::Lexer(std::string text) { set_text( text ); }

/* PUBLIC FUNCTIONS */

void Lexer::set_text(std::string text) { 
    _text = text;
    _position = 0;
    _end_of_file = false;
}

/* Next token will create a new token based on the current position in the following order...
 * - TOKEN_EOF
 * - TOKEN_PUNCTUAL
 * - TOKEN_OPERATOR
 * - TOKEN_KEYWORD and TOKEN_LITERAL_BOOLEAN
 * - TOKEN_IDENTIFIER
 * - TOKEN_LITERAL_INTEGER
 * - TOKEN_LITERAL_FLOAT
 * - TOKEN_LITERAL_CHARACTER
 * - TOKEN_LITERAL_STRING
 * - TOKEN_INVALID
 */
token_t Lexer::next_token() {

    /* Placeholder token will be filled with the appropriate kind of token */
    token_t token = { TOKEN_PLACEHOLDER, _position, std::string()};

    /* This language ignores comments and whitespace tokens */
    while (std::isspace(_current()) || _current() == '#' || _text.substr(_position,2) == "/*") {
        /* Ignore whitespace (don't make whitespace tokens) */
        while (std::isspace(_current())) {
            _next();
        }

        /* Single-line Comments */
        if (_current() == '#') {
            while (!(_current() == '\n')) { 
                _next();
                if (_position >= _text.length()) {
                    token.kind = TOKEN_EOF;
                    _end_of_file = true;
                    return token;
                }
            }
        }

        /* Multi-line Comments */
        if (_text.substr(_position,2) == "/*") {
            _seekn(2);
            while (_text.substr(_position,2) != "*/") { 
                if (_position+2 >= _text.length()) {
                    token.kind = TOKEN_EOF;
                    _end_of_file = true;
                    return token;
                }
                _next();
            }
            _seekn(2);
        }

    }    

    /* END OF FILE */
    if (_position >= _text.length()) {
        token.kind = TOKEN_EOF;
        _end_of_file = true;
        return token;
    }

    /* PUNCTUALS */
    std::vector<char> punctuals_list = { '(', ')', '{', '}', '[', ']', ','};
    for (char punctual : punctuals_list) {
        if (_current() == punctual) {
            token.kind = TOKEN_PUNCTUAL;
            token.value = punctual;
            _next();
            return token;
        }
    }

    /* OPERATORS */
    /* Note the order of the list is important. Longest operators are handled first.
     * There are several types of operators:
     * ARITHMETIC       - Mathematical operators for working with integers and floats.
     * LOGIC & BITWISE  - Digital logic operators for working with Booleans. When used with integers, performs equivalent bitwise operations.
     * COMPARISON       - Equality and inequality operators for working with any built-in types.
     * ASSIGMENT        - Operators for declaration and modification of variables.
     * OTHER            - Miscellaneous operators
     */
    std::vector<std::string> operators_list = 
    {
        
        // 3 char long
        "<<=", // ASSIGMENT - BITWISE LEFT SHIFT ASSIGN
        ">>=", // ASSIGMENT - BITWISE RIGHT SHIFT ASSIGN
        "<->", // COMPARISON - IFF "If and only if": <bln_expr> IFF(<bln_expr>,<bln_expr>)
        
        // 2 char long
        "+=", // ASSIGNMENT - ADDITION ASSIGN
        "-=", // ASSIGNMENT - SUBTRACTION ASSIGN
        "*=", // ASSIGNMENT - MULTIPLICATION ASSIGN
        "/=", // ASSIGNMENT - DIVISION ASSIGN
        "%=", // ASSIGNMENT - REMAINDER ASSIGN
        "&=", // ASSIGNMENT - AND ASSIGN
        "|=", // ASSIGNMENT - OR ASSIGN
        "^=", // ASSIGNMENT - XOR ASSIGN
        "==", // COMPAIRSON - EQUALITY
        "~=", // COMPAIRSON - INEQUALITY
        "<=", // COMPAIRSON - LESS THAN OR EQUAL
        ">=", // COMPAIRSON - GREATER THAN OR EQUAL
        "&&", // LOGIC & BITWISE - AND
        "||", // LOGIC & BITWISE - OR
        "^^", // LOGIC & BITWISE - XOR
        "~&", // LOGIC & BITWISE - NAND
        "~|", // LOGIC & BITWISE - NOR
        "->", // LOGIC & BITWISE - IF
        "<<", // LOGIC & BITWISE - BITWISE LEFT SHIFT 
        ">>", // LOGIC & BITWISE - BITWISE RIGHT SHIFT
        
        // 1 char long
        "=", // ASSIGNMENT - SIMPLE ASSIGN
        "+", // ARITHMETIC - ADDITION
        "-", // ARITHMETIC - SUBTRACTION
        "*", // ARITHMETIC - MULTIPLICATION
        "/", // ARITHMETIC - DIVISION
        "%", // ARITHMETIC - MODULO/REMAINDER
        "^", // ARITHMETIC - EXPONENTIATION
        "<", // COMPARISON - LESS THAN
        ">", // COMPARISON - MORE THAN
        "!", // OTHER - MUTABILITY INDICATOR
        "~", // LOGIC & BITWISE - NOT

    };
    for (std::string opword : operators_list) {
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
        while (std::isdigit(_current())) { _next(); }
        token.kind = TOKEN_LITERAL_FLOAT;
        token.value = _text.substr(start,_position-start);
        return token;
    }

    /* Character Literals */
    // Found opening quotation
    if (_current() == '\'') {
        // Record current position
        int start = _position;
        // Continue until closing quotation
        _next();
        while (!(_current() == '\'')) { 
            _next(); 
            if (_position >= _text.length()) {
                token.kind = TOKEN_INVALID;
                return token;
            }
        }
        _next();
        token.kind = TOKEN_LITERAL_CHARACTER;
        token.value = _text.substr(start+1,_position-start-2);
        return token;
    }

    /* String Literals */
    // Found opening quotation
    if (_current() == '"') {
        // Record current position
        int start = _position;
        // Continue until closing quotation
        _next();
        while (!(_current() == '"')) { 
            _next();
            if (_position >= _text.length()) {
                token.kind = TOKEN_INVALID;
                return token;
            }
        }
        _next();
        token.kind = TOKEN_LITERAL_STRING;
        token.value = _text.substr(start+1,_position-start-2);
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
    else return _text.at(_position+n);
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
    // Check that substring actually matches keyword          //, AND it is followed by whitespace, an alphanumerical, paranthesis or underscore character
    if (_text.substr(_position,opword.length()) == opword ) { //(std::isalnum(end_char) || std::isspace(end_char) || end_char == '_' || end_char == '(' || end_char == ')' || end_char == 0
        token.kind = TOKEN_OPERATOR;
        token.value = _text.substr(_position,opword.length());
        _seekn(opword.length());
    }
    return token;
}

// TODO: token_t Lexer::_form_type_declaration_token(std::string typeword) {}
