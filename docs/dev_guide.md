# Development Guide

## Setup

### 1. Clone the Repository

```bash
git clone https://github.com/<your-username>/NeelKant.git
cd NeelKant
```

### 2. Verify Prerequisites

```bash
# Check GCC
gcc --version

# Check Make
make --version

# Check Git
git --version
```

### 3. Build the Project

```bash
make build
```

### 4. Run Tests

```bash
make test
```

---

## Development Workflow

### Starting a New Feature

```bash
# 1. Make sure you're on develop
git checkout develop
git pull origin develop

# 2. Create a feature branch
git checkout -b feature/your-feature-name

# 3. Make changes and commit
git add .
git commit -m "feat(module): description"

# 4. Push your branch
git push origin feature/your-feature-name

# 5. Open a Pull Request on GitHub
```

### Code Organization

- Place source files in the appropriate `src/<module>/` directory
- Place header files in `include/<module>/`
- Place tests in `tests/<module>/`
- Add test programs in `tests/test_programs/`

### Debugging Tips

- Use `make CFLAGS="-g -O0"` for debug builds
- AST printer (`ast_printer.c`) can visualize parse trees
- Lexer can be tested independently by printing tokens

---

## IDE Setup

### VS Code
Install recommended extensions:
- C/C++ (Microsoft)
- C/C++ Extension Pack
- GitLens
- Markdown Preview Enhanced

### CLion
- Open the project directory
- Configure the Makefile toolchain

---

## Useful Resources

- [Crafting Interpreters](https://craftinginterpreters.com/) — Excellent reference
- [Dragon Book](https://en.wikipedia.org/wiki/Compilers:_Principles,_Techniques,_and_Tools) — Classic textbook
- [Engineering a Compiler](https://www.elsevier.com/books/engineering-a-compiler/cooper/978-0-12-815412-0) — Modern approach
- [LLVM Tutorial](https://llvm.org/docs/tutorial/) — LLVM-based compiler tutorial
