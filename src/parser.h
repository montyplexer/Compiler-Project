#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <stack>
#include "tokens.h"

/* Represents a node in the abstract syntax tree. 
 */
typedef struct parse_node_t {
    std::string value;
    std::vector<parse_node_t> children;
};



#endif