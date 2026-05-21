# Lexer Design Document

## Overview

The lexer (lexical analyzer / scanner) is the first phase of our compiler. It reads raw source code as a stream of characters and produces a stream of tokens.

## Token Categories

### Keywords
```
int, float, char, string, bool, void,
if, else, while, for, do, return,
break, continue, true, false, null,
function, var, let, const, class, struct,
import, export, print
```

### Operators
| Category | Tokens |
|----------|--------|
| Arithmetic | `+`, `-`, `*`, `/`, `%` |
| Comparison | `==`, `!=`, `<`, `>`, `<=`, `>=` |
| Logical | `&&`, `\|\|`, `!` |
| Assignment | `=`, `+=`, `-=`, `*=`, `/=` |
| Bitwise | `&`, `\|`, `^`, `~`, `<<`, `>>` |
| Other | `++`, `--`, `->`, `.` |

### Delimiters
```
( ) { } [ ] ; , :
```

### Literals
- **Integer**: `42`, `0xFF`, `0b1010`, `0o77`
- **Float**: `3.14`, `1.0e10`, `.5`
- **String**: `"hello world"`, `"escape\n"`
- **Character**: `'a'`, `'\n'`
- **Boolean**: `true`, `false`

### Identifiers
- Start with letter or underscore
- Followed by letters, digits, or underscores
- Case-sensitive

## Token Structure

```c
typedef struct {
    TokenType type;       // Token category
    char *lexeme;         // Actual text from source
    int line;             // Line number
    int column;           // Column number
    union {               // Literal value (if applicable)
        int int_val;
        double float_val;
        char *string_val;
    } value;
} Token;
```

## Algorithm

1. Read character from input
2. Skip whitespace and comments
3. Match longest possible token (maximal munch)
4. Create token with position info
5. Return token to parser
6. Repeat until EOF

## Error Handling

- Unknown characters → report error with line:column
- Unterminated strings → report error
- Invalid number formats → report error
- Continue scanning after error (error recovery)

## Files

| File | Purpose |
|------|---------|
| `lexer.h` | Token types, token struct, lexer API |
| `lexer.c` | Lexer implementation |
| `token.h` | Token definitions and utilities |
| `token.c` | Token helper functions |

---

*Status: Specification Phase*
