# Language Specification

## Overview

This document defines the grammar and syntax rules for our custom programming language.

> **Status**: Draft — Under Development

---

## 1. Lexical Structure

### 1.1 Character Set
- UTF-8 encoding
- Case-sensitive

### 1.2 Comments
```
// Single-line comment

/* 
   Multi-line
   comment 
*/
```

### 1.3 Whitespace
- Spaces, tabs, newlines are ignored (not significant)
- Used only to separate tokens

---

## 2. Grammar (BNF Notation)

```bnf
<program>       ::= <statement>*

<statement>     ::= <var_decl>
                  | <func_decl>
                  | <if_stmt>
                  | <while_stmt>
                  | <for_stmt>
                  | <return_stmt>
                  | <expr_stmt>
                  | <block>

<var_decl>      ::= ("var" | "let" | "const") IDENTIFIER (":" <type>)? ("=" <expression>)? ";"

<func_decl>     ::= "function" IDENTIFIER "(" <param_list>? ")" (":" <type>)? <block>

<param_list>    ::= <param> ("," <param>)*
<param>         ::= IDENTIFIER ":" <type>

<if_stmt>       ::= "if" "(" <expression> ")" <block> ("else" <block>)?

<while_stmt>    ::= "while" "(" <expression> ")" <block>

<for_stmt>      ::= "for" "(" <var_decl>? ";" <expression>? ";" <expression>? ")" <block>

<return_stmt>   ::= "return" <expression>? ";"

<expr_stmt>     ::= <expression> ";"

<block>         ::= "{" <statement>* "}"

<type>          ::= "int" | "float" | "char" | "string" | "bool" | "void"
                  | <type> "[]"

<expression>    ::= <assignment>

<assignment>    ::= IDENTIFIER "=" <expression>
                  | <logic_or>

<logic_or>      ::= <logic_and> ("||" <logic_and>)*
<logic_and>     ::= <equality> ("&&" <equality>)*
<equality>      ::= <comparison> (("==" | "!=") <comparison>)*
<comparison>    ::= <addition> (("<" | ">" | "<=" | ">=") <addition>)*
<addition>      ::= <multiplication> (("+" | "-") <multiplication>)*
<multiplication>::= <unary> (("*" | "/" | "%") <unary>)*
<unary>         ::= ("!" | "-") <unary> | <call>
<call>          ::= <primary> ("(" <arg_list>? ")")*
<primary>       ::= INTEGER | FLOAT | STRING | "true" | "false" | "null"
                  | IDENTIFIER | "(" <expression> ")"

<arg_list>      ::= <expression> ("," <expression>)*
```

---

## 3. Type System

### 3.1 Primitive Types
| Type | Description | Size |
|------|-------------|------|
| `int` | Integer | 4 bytes |
| `float` | Floating-point | 8 bytes |
| `char` | Character | 1 byte |
| `string` | String | Variable |
| `bool` | Boolean | 1 byte |
| `void` | No type | 0 bytes |

### 3.2 Type Rules
- Implicit conversions: `int → float`
- Explicit casting required for other conversions
- `bool` cannot be mixed with arithmetic types

---

## 4. Example Programs

### Hello World
```
function main(): void {
    print("Hello, World!");
}
```

### Fibonacci
```
function fibonacci(n: int): int {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

function main(): void {
    var result: int = fibonacci(10);
    print(result);
}
```

### Variables and Control Flow
```
function main(): void {
    var x: int = 10;
    var y: int = 20;
    
    if (x < y) {
        print("x is less than y");
    } else {
        print("x is greater or equal to y");
    }
    
    var sum: int = 0;
    for (var i: int = 0; i < 10; i = i + 1) {
        sum = sum + i;
    }
    print(sum);
}
```

---

## 5. Reserved Words

```
int, float, char, string, bool, void,
if, else, while, for, do, return,
break, continue, true, false, null,
function, var, let, const, class, struct,
import, export, print, new
```

---

*This specification is a living document. Update as the language evolves.*
