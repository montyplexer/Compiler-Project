#ifndef SYNTAX_NODES_H
#define SYNTAX_NODES_H

#include <string>
#include <vector>

/* These are the types of syntax nodes that the Parser can produce:
 * - Literal Nodes (integer, float, char, and string types)
 * - Binary Expression (arithmetic, logic, )
 *
 * */
enum syntax_node_kind {
    SNODE_PLACEHOLDER,
};

/* Represents a node in the abstract syntax tree. 
 */
typedef struct syntax_node_t {
    syntax_node_kind kind;
    std::vector<syntax_node_t> children;
    std::string value;
};

#endif