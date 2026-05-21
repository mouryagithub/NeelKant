/**
 * @file lexer.c
 * @brief Lexer implementation
 * @date 2026-05-21
 * 
 * Implements the lexical analyzer that converts source code
 * into a stream of tokens.
 */

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ============================================
 * Lexer Initialization
 * ============================================ */

void lexer_init(Lexer *lexer, const char *source) {
    lexer->source = source;
    lexer->start = 0;
    lexer->current = 0;
    lexer->line = 1;
    lexer->column = 1;
}

/* ============================================
 * Helper Functions
 * ============================================ */

static int is_at_end(Lexer *lexer) {
    return lexer->source[lexer->current] == '\0';
}

static char advance(Lexer *lexer) {
    lexer->column++;
    return lexer->source[lexer->current++];
}

static char peek(Lexer *lexer) {
    return lexer->source[lexer->current];
}

static char peek_next(Lexer *lexer) {
    if (is_at_end(lexer)) return '\0';
    return lexer->source[lexer->current + 1];
}

static int match(Lexer *lexer, char expected) {
    if (is_at_end(lexer)) return 0;
    if (lexer->source[lexer->current] != expected) return 0;
    lexer->current++;
    lexer->column++;
    return 1;
}

/* ============================================
 * Token Creation
 * ============================================ */

static Token make_token(Lexer *lexer, TokenType type) {
    Token token;
    token.type = type;
    int length = lexer->current - lexer->start;
    token.lexeme = (char *)malloc(length + 1);
    strncpy(token.lexeme, &lexer->source[lexer->start], length);
    token.lexeme[length] = '\0';
    token.line = lexer->line;
    token.column = lexer->column - length;
    return token;
}

static Token error_token(Lexer *lexer, const char *message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.lexeme = strdup(message);
    token.line = lexer->line;
    token.column = lexer->column;
    return token;
}

/* ============================================
 * Whitespace & Comments
 * ============================================ */

static void skip_whitespace(Lexer *lexer) {
    for (;;) {
        char c = peek(lexer);
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance(lexer);
                break;
            case '\n':
                lexer->line++;
                lexer->column = 0;
                advance(lexer);
                break;
            case '/':
                if (peek_next(lexer) == '/') {
                    // Single-line comment
                    while (peek(lexer) != '\n' && !is_at_end(lexer))
                        advance(lexer);
                } else if (peek_next(lexer) == '*') {
                    // Multi-line comment
                    advance(lexer); // skip /
                    advance(lexer); // skip *
                    while (!is_at_end(lexer)) {
                        if (peek(lexer) == '\n') {
                            lexer->line++;
                            lexer->column = 0;
                        }
                        if (peek(lexer) == '*' && peek_next(lexer) == '/') {
                            advance(lexer);
                            advance(lexer);
                            break;
                        }
                        advance(lexer);
                    }
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

/* ============================================
 * Token Scanning
 * ============================================ */

// TODO: Implement keyword checking
// TODO: Implement string literal scanning
// TODO: Implement number literal scanning
// TODO: Implement identifier scanning

Token lexer_next_token(Lexer *lexer) {
    skip_whitespace(lexer);
    lexer->start = lexer->current;

    if (is_at_end(lexer)) {
        return make_token(lexer, TOKEN_EOF);
    }

    char c = advance(lexer);

    // TODO: Add complete token scanning logic
    // This is a placeholder implementation

    switch (c) {
        case '(': return make_token(lexer, TOKEN_LPAREN);
        case ')': return make_token(lexer, TOKEN_RPAREN);
        case '{': return make_token(lexer, TOKEN_LBRACE);
        case '}': return make_token(lexer, TOKEN_RBRACE);
        case '[': return make_token(lexer, TOKEN_LBRACKET);
        case ']': return make_token(lexer, TOKEN_RBRACKET);
        case ';': return make_token(lexer, TOKEN_SEMICOLON);
        case ',': return make_token(lexer, TOKEN_COMMA);
        case ':': return make_token(lexer, TOKEN_COLON);
        case '.': return make_token(lexer, TOKEN_DOT);
        case '+': return make_token(lexer, TOKEN_PLUS);
        case '-': return make_token(lexer, TOKEN_MINUS);
        case '*': return make_token(lexer, TOKEN_STAR);
        case '/': return make_token(lexer, TOKEN_SLASH);
        case '%': return make_token(lexer, TOKEN_PERCENT);
        case '=':
            return make_token(lexer, match(lexer, '=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '!':
            return make_token(lexer, match(lexer, '=') ? TOKEN_NOT_EQUAL : TOKEN_NOT);
        case '<':
            return make_token(lexer, match(lexer, '=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>':
            return make_token(lexer, match(lexer, '=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        default:
            break;
    }

    return error_token(lexer, "Unexpected character");
}

/* ============================================
 * Utility Functions
 * ============================================ */

const char *token_type_name(TokenType type) {
    switch (type) {
        case TOKEN_INTEGER_LITERAL: return "INTEGER";
        case TOKEN_FLOAT_LITERAL:   return "FLOAT";
        case TOKEN_STRING_LITERAL:  return "STRING";
        case TOKEN_IDENTIFIER:      return "IDENTIFIER";
        case TOKEN_PLUS:            return "PLUS";
        case TOKEN_MINUS:           return "MINUS";
        case TOKEN_STAR:            return "STAR";
        case TOKEN_SLASH:           return "SLASH";
        case TOKEN_EQUAL:           return "EQUAL";
        case TOKEN_SEMICOLON:       return "SEMICOLON";
        case TOKEN_EOF:             return "EOF";
        case TOKEN_ERROR:           return "ERROR";
        // TODO: Add remaining token type names
        default:                    return "UNKNOWN";
    }
}

void token_free(Token *token) {
    if (token && token->lexeme) {
        free(token->lexeme);
        token->lexeme = NULL;
    }
}
