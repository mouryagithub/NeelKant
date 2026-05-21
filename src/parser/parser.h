/**
 * @file parser.h
 * @brief Parser module interface
 * @date 2026-05-21
 * 
 * Defines the AST node types, structures, and parser API.
 * TODO: Implement after lexer is complete.
 */

#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"

/* ============================================
 * AST Node Types
 * ============================================ */
typedef enum {
    NODE_PROGRAM,
    NODE_VAR_DECL,
    NODE_FUNC_DECL,
    NODE_IF_STMT,
    NODE_WHILE_STMT,
    NODE_FOR_STMT,
    NODE_RETURN_STMT,
    NODE_BLOCK,
    NODE_EXPR_STMT,
    NODE_BINARY_EXPR,
    NODE_UNARY_EXPR,
    NODE_LITERAL,
    NODE_IDENTIFIER,
    NODE_FUNC_CALL,
    NODE_ASSIGNMENT,
    NODE_ARRAY_ACCESS,
} NodeType;

/* ============================================
 * AST Node Structure
 * ============================================ */
typedef struct ASTNode {
    NodeType type;
    int line;
    int column;
    struct ASTNode **children;
    int child_count;
    int child_capacity;
    // Node-specific data - extend as needed
    char *name;         // For identifiers, function names
    Token *token;       // Associated token
} ASTNode;

/* ============================================
 * Parser API
 * ============================================ */

/**
 * @brief Parse a token stream into an AST
 * @param lexer Initialized lexer to read tokens from
 * @return Root node of the AST (program node)
 */
ASTNode *parser_parse(Lexer *lexer);

/**
 * @brief Create a new AST node
 * @param type Node type
 * @param line Source line
 * @param column Source column
 * @return Newly allocated AST node
 */
ASTNode *ast_node_create(NodeType type, int line, int column);

/**
 * @brief Add a child node to a parent
 * @param parent Parent node
 * @param child Child node to add
 */
void ast_node_add_child(ASTNode *parent, ASTNode *child);

/**
 * @brief Free an AST node and all its children
 * @param node Node to free
 */
void ast_node_free(ASTNode *node);

/**
 * @brief Print the AST for debugging
 * @param node Root node to print
 * @param indent Current indentation level
 */
void ast_print(ASTNode *node, int indent);

#endif /* PARSER_H */
