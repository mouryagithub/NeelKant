/**
 * @file parser.c
 * @brief Parser implementation (stub)
 * @date 2026-05-21
 * 
 * TODO: Implement the parser after the lexer is complete.
 */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================
 * AST Node Operations
 * ============================================ */

ASTNode *ast_node_create(NodeType type, int line, int column) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->line = line;
    node->column = column;
    node->children = NULL;
    node->child_count = 0;
    node->child_capacity = 0;
    node->name = NULL;
    node->token = NULL;
    return node;
}

void ast_node_add_child(ASTNode *parent, ASTNode *child) {
    if (parent->child_count >= parent->child_capacity) {
        parent->child_capacity = parent->child_capacity == 0 ? 4 : parent->child_capacity * 2;
        parent->children = (ASTNode **)realloc(parent->children,
                                                sizeof(ASTNode *) * parent->child_capacity);
    }
    parent->children[parent->child_count++] = child;
}

void ast_node_free(ASTNode *node) {
    if (!node) return;
    for (int i = 0; i < node->child_count; i++) {
        ast_node_free(node->children[i]);
    }
    free(node->children);
    free(node->name);
    free(node);
}

void ast_print(ASTNode *node, int indent) {
    if (!node) return;
    
    for (int i = 0; i < indent; i++) printf("  ");
    
    // TODO: Add node type names
    printf("Node(type=%d", node->type);
    if (node->name) printf(", name=%s", node->name);
    printf(")\n");
    
    for (int i = 0; i < node->child_count; i++) {
        ast_print(node->children[i], indent + 1);
    }
}

/* ============================================
 * Parser Implementation
 * ============================================ */

ASTNode *parser_parse(Lexer *lexer) {
    // TODO: Implement recursive descent (or chosen strategy) parser
    // 
    // Suggested implementation order:
    // 1. Expression parsing (literals, binary ops)
    // 2. Statement parsing (var decl, if, while)
    // 3. Function declarations
    // 4. Program structure
    
    (void)lexer; // suppress unused warning
    
    printf("Parser: Not yet implemented\n");
    return ast_node_create(NODE_PROGRAM, 0, 0);
}
