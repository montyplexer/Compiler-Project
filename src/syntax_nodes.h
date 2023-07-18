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
    SNODE_TERMINAL,
    SNODE_EXPRESSION,
    SNODE_STATEMENT,
};

/* Represents a node in the abstract syntax tree. 
 */
struct syntax_node_t {
    /* Kind of syntax node enum (what this node represents, i.e. binary expression) */
    syntax_node_kind kind;
    /* Token associated with this syntax node */
    token_t token;
    /* A list of children associated with this kind of syntax node */
    std::vector<syntax_node_t> children;
};

#endif