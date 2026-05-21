/**
 * @file lexer.h
 * @brief Lexer module interface
 * @date 2026-05-21
 * 
 * Defines the token types, token structure, and lexer API
 * for the lexical analysis phase of the compiler.
 */

#ifndef LEXER_H
#define LEXER_H

/* ============================================
 * Token Type Definitions
 * ============================================ */
typedef enum {
    // Literals
    TOKEN_INTEGER_LITERAL,
    TOKEN_FLOAT_LITERAL,
    TOKEN_STRING_LITERAL,
    TOKEN_CHAR_LITERAL,

    // Identifier
    TOKEN_IDENTIFIER,

    // Keywords
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_CHAR,
    TOKEN_STRING,
    TOKEN_BOOL,
    TOKEN_VOID,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_DO,
    TOKEN_RETURN,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL_KEYWORD,
    TOKEN_FUNCTION,
    TOKEN_VAR,
    TOKEN_LET,
    TOKEN_CONST,
    TOKEN_PRINT,

    // Operators
    TOKEN_PLUS,         // +
    TOKEN_MINUS,        // -
    TOKEN_STAR,         // *
    TOKEN_SLASH,        // /
    TOKEN_PERCENT,      // %
    TOKEN_EQUAL,        // =
    TOKEN_EQUAL_EQUAL,  // ==
    TOKEN_NOT_EQUAL,    // !=
    TOKEN_LESS,         // <
    TOKEN_GREATER,      // >
    TOKEN_LESS_EQUAL,   // <=
    TOKEN_GREATER_EQUAL,// >=
    TOKEN_AND,          // &&
    TOKEN_OR,           // ||
    TOKEN_NOT,          // !
    TOKEN_PLUS_EQUAL,   // +=
    TOKEN_MINUS_EQUAL,  // -=
    TOKEN_STAR_EQUAL,   // *=
    TOKEN_SLASH_EQUAL,  // /=
    TOKEN_PLUS_PLUS,    // ++
    TOKEN_MINUS_MINUS,  // --

    // Delimiters
    TOKEN_LPAREN,       // (
    TOKEN_RPAREN,       // )
    TOKEN_LBRACE,       // {
    TOKEN_RBRACE,       // }
    TOKEN_LBRACKET,     // [
    TOKEN_RBRACKET,     // ]
    TOKEN_SEMICOLON,    // ;
    TOKEN_COMMA,        // ,
    TOKEN_COLON,        // :
    TOKEN_DOT,          // .
    TOKEN_ARROW,        // ->

    // Special
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

/* ============================================
 * Token Structure
 * ============================================ */
typedef struct {
    TokenType type;
    char *lexeme;       // The actual text of the token
    int line;           // Source line number
    int column;         // Source column number
    union {
        int int_val;
        double float_val;
        char *string_val;
    } literal;
} Token;

/* ============================================
 * Lexer Structure
 * ============================================ */
typedef struct {
    const char *source;  // Source code string
    int start;           // Start of current lexeme
    int current;         // Current position
    int line;            // Current line number
    int column;          // Current column number
} Lexer;

/* ============================================
 * Lexer API
 * ============================================ */

/**
 * @brief Initialize the lexer with source code
 * @param lexer Pointer to lexer struct
 * @param source Source code string
 */
void lexer_init(Lexer *lexer, const char *source);

/**
 * @brief Scan and return the next token
 * @param lexer Pointer to lexer struct
 * @return The next token from the source
 */
Token lexer_next_token(Lexer *lexer);

/**
 * @brief Get a human-readable name for a token type
 * @param type The token type
 * @return String name of the token type
 */
const char *token_type_name(TokenType type);

/**
 * @brief Free memory associated with a token
 * @param token Pointer to token to free
 */
void token_free(Token *token);

#endif /* LEXER_H */
