# Parser Design Document

## Overview

The parser is the second phase of the compiler. It takes a stream of tokens from the lexer and constructs an Abstract Syntax Tree (AST).

## Parsing Strategy

**TBD** — The team needs to decide between:

| Strategy | Pros | Cons |
|----------|------|------|
| Recursive Descent | Simple, easy to debug, good error messages | May need left-recursion elimination |
| LR(1) | Handles larger class of grammars | More complex, harder error messages |
| LALR(1) | Efficient, well-understood | Requires parser generator |
| Pratt Parsing | Excellent for expressions | Less conventional |

## AST Node Types

### Statements
- Program
- VariableDeclaration
- FunctionDeclaration
- IfStatement
- WhileStatement
- ForStatement
- ReturnStatement
- ExpressionStatement
- Block

### Expressions
- BinaryExpression (a + b, x * y)
- UnaryExpression (-x, !flag)
- Literal (42, "hello", true)
- Identifier (variable references)
- FunctionCall (foo(x, y))
- Assignment (x = 5)
- ArrayAccess (arr[i])
- MemberAccess (obj.field)

## AST Structure

```c
typedef enum {
    NODE_PROGRAM,
    NODE_VAR_DECL,
    NODE_FUNC_DECL,
    NODE_IF_STMT,
    NODE_WHILE_STMT,
    NODE_FOR_STMT,
    NODE_RETURN_STMT,
    NODE_BLOCK,
    NODE_BINARY_EXPR,
    NODE_UNARY_EXPR,
    NODE_LITERAL,
    NODE_IDENTIFIER,
    NODE_FUNC_CALL,
    NODE_ASSIGNMENT,
    // ... more as needed
} NodeType;

typedef struct ASTNode {
    NodeType type;
    int line;
    int column;
    union {
        // Node-specific data
    } data;
    struct ASTNode **children;
    int child_count;
} ASTNode;
```

## Error Recovery

- Panic mode: skip tokens until synchronization point (`;`, `}`)
- Error productions: handle common mistakes gracefully
- Report multiple errors per compilation

## Files

| File | Purpose |
|------|---------|
| `parser.h` | Parser API, AST node definitions |
| `parser.c` | Parser implementation |
| `ast.h` | AST node types and structures |
| `ast.c` | AST construction and utilities |
| `ast_printer.c` | AST visualization for debugging |

---

*Status: Specification Phase*
