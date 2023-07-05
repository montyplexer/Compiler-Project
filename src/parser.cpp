#include <string>
#include <vector>
#include <cctype>
#include "parser.h"
#include "tokens.h"

/* CONSTRUCTORS */
Parser::Parser() { _reset(); }

Parser::Parser(std::vector<token_t> token_list) {
    _reset();
    _tokens = token_list;
}

/* PUBLIC FUNCTIONS */

void Parser::set_tokens(std::vector<token_t> token_list) { 
    _reset();
    _tokens = token_list;
}

/* PRIVATE FUNCTIONS */

void Parser::_reset() {
    _root = { SNODE_PLACEHOLDER, std::vector<syntax_node_t>(), std::string() };
    _tokens = std::vector<token_t>();
    _position = 0;
    _end_of_tokens = false;
}

token_t Parser::_current() {
    /* This condition should never be met if the Parser is used properly, since the Lexer inserts a TOKEN_EOF at the end of the token list. 
     * Nonetheless, this check prevents an error or undefined behavior if the Parser is abused. */
    if (_position >= _tokens.size()) { token_t token = {TOKEN_EOF,0,std::string()}; return token_t(); }
    else return _tokens[_position];
}

token_t Parser::_peek() {
    if (_position+1 >= _tokens.size()) { token_t token = {TOKEN_EOF,0,std::string()}; return token_t(); }
    else return _tokens[_position+1];
}

token_t Parser::_peekn(int n) {
    if (_position+n >= _tokens.size() || _position+n < 0) { token_t token = {TOKEN_EOF,0,std::string()}; return token_t(); }
    else return _tokens.at(_position+n);
}

void Parser::_next() { _position++; }

void Parser::_seekn(int n) { _position += n; }



