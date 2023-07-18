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

bool Parser::parse()
{
    /* LR parser stack*/
    std::stack<syntax_node_t> parse_stack = std::stack<syntax_node_t>();
    
    
    /* Continue to parse until encountering an error or until reaching end of token list */
    while(_current().kind != TOKEN_EOF) {
        /* Placeholder node */
        syntax_node_t snode = { SNODE_PLACEHOLDER, token_t(), std::vector<syntax_node_t>() };
        
        switch (_state) {
            case PARSE_INIT:
                /* Parse literals as terminals */
                if (_current().kind == TOKEN_LITERAL_INTEGER ||
                    _current().kind == TOKEN_LITERAL_FLOAT ||
                    _current().kind == TOKEN_LITERAL_BOOLEAN ||
                    _current().kind == TOKEN_LITERAL_CHARACTER ||
                    _current().kind == TOKEN_LITERAL_STRING ) {
                    snode = { SNODE_TERMINAL, _current(), std::vector<syntax_node_t>() };
                    if (_peek().kind == TOKEN_OPERATOR) {

                    }
                    break;
                }
                /* Parse identifiers as terminals */
                if (_current().kind == TOKEN_IDENTIFIER) {
                    snode = { SNODE_TERMINAL, _current(), std::vector<syntax_node_t>() };
                    break;
                }
                /* Parse based on keyword used (only keywords possible at beginning of program)*/
                if (_current().kind == TOKEN_KEYWORD) {
                    std::string keyword = _current().value;
                    if (keyword == "if") {

                    }
                }
            case PARSE_S1:
            }
        parse_stack.push(snode);
        _next();
    }

    return true;
}

void Parser::show_parse_tree() {
    int scope = 0;
    if (_root.kind == SNODE_PLACEHOLDER) {
        std::cout << "Empty Parse Tree" << std::endl;
    } else {
        std::cout << "> Successful Parse" << std::endl;
    }
    if (!_root.children.empty()) {
        for (syntax_node_t child : _root.children ) {
            _rec_print_children(child, 1);
        }
    }
}



/* PRIVATE FUNCTIONS */

void Parser::_reset() {
    token_t placeholder_token = { TOKEN_PLACEHOLDER, 0, 0, 0, std::string() };
    _root = { SNODE_PLACEHOLDER, placeholder_token, std::vector<syntax_node_t>() };
    _tokens = std::vector<token_t>();
    _position = 0;
    _end_of_tokens = false;
    _state = PARSE_INIT;
}

token_t Parser::_last_token() {
    if (_tokens.empty()) { token_t token = {TOKEN_EOF, 0, 0, 0, std::string()}; return token; }
    else { return _tokens.at(_tokens.size()-1); }
}

token_t Parser::_current() {
    if (_position >= _tokens.size()) { return _last_token(); }
    else return _tokens[_position];
}

token_t Parser::_peek() {
    if (_position+1 >= _tokens.size()) { return _last_token(); }
    else return _tokens[_position+1];
}

token_t Parser::_peekn(int n) {
    if (_position+n >= _tokens.size() || _position+n < 0) { _last_token(); }
    else return _tokens.at(_position+n);
}

token_t Parser::_next() { _position++; return _current(); }

token_t Parser::_seekn(int n) { _position += n; return _current(); }

/*
syntax_node_t Parser::_match(token_kind kind) {
    if (kind == _current().kind) {
        return _next();
    }
}*/

void Parser::_rec_print_children(syntax_node_t node, int scope) {
    for (int i = 0; i <= scope; i++) { std::cout << "-"; }
    std::cout << "> Node" << std::endl;
    if (!node.children.empty()) { 
        for (syntax_node_t child : node.children ) {
            _rec_print_children(child, scope+1);
        }
    }
}
