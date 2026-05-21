/**
 * @file analyzer.h
 * @brief Semantic analysis module interface (stub)
 * @date 2026-05-21
 * 
 * TODO: Implement semantic analysis (type checking, scope resolution).
 */

#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "../parser/parser.h"

/**
 * @brief Perform semantic analysis on the AST
 * @param root Root of the AST
 * @return 0 on success, non-zero on error
 */
int semantic_analyze(ASTNode *root);

#endif /* SEMANTIC_ANALYZER_H */
