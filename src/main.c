/**
 * @file main.c
 * @brief Entry point for the compiler
 * @date 2026-05-21
 * 
 * This is the main driver for the compiler. It processes command-line
 * arguments, reads the input source file, and orchestrates the
 * compilation pipeline.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Include module headers as they are implemented
// #include "lexer/lexer.h"
// #include "parser/parser.h"
// #include "semantic/analyzer.h"
// #include "ir/ir_generator.h"
// #include "optimizer/optimizer.h"
// #include "codegen/codegen.h"

void print_usage(const char *program_name) {
    printf("Usage: %s [options] <source-file>\n", program_name);
    printf("\nOptions:\n");
    printf("  -o <file>    Output file name\n");
    printf("  -S           Output assembly only\n");
    printf("  --tokens     Print token stream (debug)\n");
    printf("  --ast        Print AST (debug)\n");
    printf("  --ir         Print IR (debug)\n");
    printf("  -v           Verbose output\n");
    printf("  -h, --help   Show this help message\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    // Parse command-line arguments
    const char *input_file = NULL;
    const char *output_file = NULL;
    int show_tokens = 0;
    int show_ast = 0;
    int show_ir = 0;
    int verbose = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "--tokens") == 0) {
            show_tokens = 1;
        } else if (strcmp(argv[i], "--ast") == 0) {
            show_ast = 1;
        } else if (strcmp(argv[i], "--ir") == 0) {
            show_ir = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (argv[i][0] != '-') {
            input_file = argv[i];
        } else {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }

    if (!input_file) {
        fprintf(stderr, "Error: No input file specified\n");
        print_usage(argv[0]);
        return 1;
    }

    if (verbose) {
        printf("Compiler v0.1.0\n");
        printf("Input:  %s\n", input_file);
        printf("Output: %s\n", output_file ? output_file : "(default)");
    }

    // TODO: Implement compilation pipeline
    // 1. Read source file
    // 2. Lexical analysis  → Token stream
    // 3. Parsing            → AST
    // 4. Semantic analysis  → Annotated AST
    // 5. IR generation      → Intermediate code
    // 6. Optimization       → Optimized IR
    // 7. Code generation    → Target output

    printf("Compiler is under construction!\n");
    printf("Input file: %s\n", input_file);

    // Suppress unused variable warnings during development
    (void)output_file;
    (void)show_tokens;
    (void)show_ast;
    (void)show_ir;

    return 0;
}
