# Architecture Overview

## Compiler Pipeline

Our compiler follows the classic multi-phase compilation architecture. Each phase is implemented as a separate module with well-defined interfaces.

## Pipeline Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                        Source Code (.src)                        │
└─────────────────────────┬───────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────┐
│                     1. LEXER (Scanner)                           │
│  Input:  Raw source text                                        │
│  Output: Token stream                                           │
│  Key:    Regular expressions, DFA-based tokenization             │
└─────────────────────────┬───────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────┐
│                     2. PARSER                                    │
│  Input:  Token stream                                           │
│  Output: Abstract Syntax Tree (AST)                             │
│  Key:    Context-free grammar, recursive descent / LR parsing    │
└─────────────────────────┬───────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────┐
│                 3. SEMANTIC ANALYZER                              │
│  Input:  AST                                                    │
│  Output: Annotated AST                                          │
│  Key:    Type checking, scope resolution, symbol table           │
└─────────────────────────┬───────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────┐
│              4. IR GENERATOR                                     │
│  Input:  Annotated AST                                          │
│  Output: Intermediate Representation (Three-Address Code / SSA)  │
│  Key:    Platform-independent code representation                │
└─────────────────────────┬───────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────┐
│                  5. OPTIMIZER                                    │
│  Input:  IR                                                     │
│  Output: Optimized IR                                           │
│  Key:    Constant folding, dead code elimination, loop opts      │
└─────────────────────────┬───────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────┐
│                6. CODE GENERATOR                                 │
│  Input:  Optimized IR                                           │
│  Output: Target code (assembly / machine code)                   │
│  Key:    Register allocation, instruction selection               │
└─────────────────────────┬───────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────┐
│                    Target Output (.asm / .o)                     │
└─────────────────────────────────────────────────────────────────┘
```

## Module Responsibilities

### Lexer (`src/lexer/`)
- Read source file character by character
- Identify and classify tokens (keywords, identifiers, operators, literals)
- Handle whitespace, comments, and string escaping
- Report lexical errors with line/column numbers

### Parser (`src/parser/`)
- Consume token stream from lexer
- Validate syntax against the language grammar
- Construct Abstract Syntax Tree (AST)
- Report syntax errors with meaningful messages

### Semantic Analyzer (`src/semantic/`)
- Traverse AST to perform semantic checks
- Build and manage symbol table
- Type checking and type inference
- Scope resolution (variable declarations, function signatures)
- Report semantic errors

### IR Generator (`src/ir/`)
- Convert annotated AST to intermediate representation
- Generate three-address code or SSA form
- Maintain platform independence

### Optimizer (`src/optimizer/`)
- Apply optimization passes on IR
- Constant folding and propagation
- Dead code elimination
- Common subexpression elimination
- Loop optimizations

### Code Generator (`src/codegen/`)
- Convert optimized IR to target assembly
- Register allocation
- Instruction selection and scheduling
- Output final assembly or object file

## Data Flow Between Modules

```
Lexer  ──Token──▶  Parser  ──AST──▶  Semantic  ──AST'──▶  IR Gen  ──IR──▶  Optimizer  ──IR'──▶  CodeGen
```

## Error Handling Strategy

Each module reports errors through a centralized error handler (`src/utils/error_handler`):
- **Lexical errors**: Invalid characters, unterminated strings
- **Syntax errors**: Unexpected tokens, malformed expressions
- **Semantic errors**: Type mismatches, undeclared variables
- **Code generation errors**: Unsupported operations

## Design Decisions

| Decision | Choice | Rationale |
|----------|--------|-----------|
| Parsing Strategy | TBD (Recursive Descent / LR) | To be decided by team |
| IR Format | TBD (Three-Address Code / SSA) | To be decided by team |
| Target Architecture | TBD (x86-64 / ARM / LLVM IR) | To be decided by team |
| Language Paradigm | TBD | To be decided by team |

---

*Last Updated: Project Setup Phase*
