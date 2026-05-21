/**
 * @file error_handler.c
 * @brief Error reporting implementation
 */
#include "error_handler.h"
#include <stdio.h>

static int error_count = 0;
static int warning_count = 0;

void report_error(ErrorCategory category, int line, int column, const char *message) {
    const char *cat_name;
    switch (category) {
        case ERROR_LEXER:    cat_name = "Lexer"; break;
        case ERROR_PARSER:   cat_name = "Parser"; break;
        case ERROR_SEMANTIC: cat_name = "Semantic"; break;
        case ERROR_CODEGEN:  cat_name = "CodeGen"; break;
        default:             cat_name = "Internal"; break;
    }
    fprintf(stderr, "[%s Error] Line %d, Col %d: %s\n", cat_name, line, column, message);
    error_count++;
}

void report_warning(int line, int column, const char *message) {
    fprintf(stderr, "[Warning] Line %d, Col %d: %s\n", line, column, message);
    warning_count++;
}

int get_error_count(void) { return error_count; }
void reset_errors(void) { error_count = 0; warning_count = 0; }
