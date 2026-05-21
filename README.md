# 🛠️ NeelKant Compiler

> A from-scratch compiler implementation built collaboratively by our team.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)]()
[![Contributors](https://img.shields.io/badge/contributors-welcome-blue)]()

---

## 📖 Table of Contents

- [Overview](#overview)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Build & Run](#build--run)
- [Testing](#testing)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [Team](#team)
- [License](#license)

---

## Overview

This project is a custom-built compiler designed and implemented from scratch. It covers the full compilation pipeline:

1. **Lexical Analysis (Lexer/Scanner)** — Tokenizes source code into meaningful tokens.
2. **Syntax Analysis (Parser)** — Builds an Abstract Syntax Tree (AST) from tokens.
3. **Semantic Analysis** — Type checking, scope resolution, and validation.
4. **Intermediate Representation (IR)** — Generates an intermediate code representation.
5. **Optimization** — Applies optimization passes on the IR.
6. **Code Generation** — Produces target machine code or assembly.

---

## Architecture

```
Source Code
    │
    ▼
┌──────────┐     ┌──────────┐     ┌──────────────────┐
│  Lexer   │ ──▶ │  Parser  │ ──▶ │ Semantic Analyzer│
└──────────┘     └──────────┘     └──────────────────┘
                                          │
                                          ▼
                                  ┌──────────────┐
                                  │   IR Gen     │
                                  └──────────────┘
                                          │
                                          ▼
                                  ┌──────────────┐
                                  │  Optimizer   │
                                  └──────────────┘
                                          │
                                          ▼
                                  ┌──────────────┐
                                  │  Code Gen    │
                                  └──────────────┘
                                          │
                                          ▼
                                   Target Output
```

---

## Project Structure

```
NeelKant/
├── src/                    # Source code
│   ├── lexer/              # Lexical analysis module
│   ├── parser/             # Syntax analysis & AST
│   ├── semantic/           # Semantic analysis
│   ├── ir/                 # Intermediate representation
│   ├── optimizer/          # Optimization passes
│   ├── codegen/            # Code generation
│   └── utils/              # Shared utilities
├── include/                # Header files (if using C/C++)
├── tests/                  # Test suite
│   ├── lexer/              # Lexer tests
│   ├── parser/             # Parser tests
│   ├── semantic/           # Semantic analysis tests
│   ├── integration/        # End-to-end tests
│   └── test_programs/      # Sample programs for testing
├── docs/                   # Project documentation
│   ├── design/             # Design documents & specs
│   ├── grammar/            # Language grammar specification
│   ├── meeting-notes/      # Team meeting notes
│   └── references/         # Reference materials
├── examples/               # Example programs in our language
├── tools/                  # Build tools & scripts
├── .github/                # GitHub collaboration config
│   ├── ISSUE_TEMPLATE/     # Issue templates
│   ├── PULL_REQUEST_TEMPLATE.md
│   └── workflows/          # CI/CD workflows
├── CONTRIBUTING.md         # Contribution guidelines
├── CODE_OF_CONDUCT.md      # Code of conduct
├── CHANGELOG.md            # Version changelog
├── Makefile                # Build configuration
├── LICENSE                 # MIT License
└── README.md               # This file
```

---

## Getting Started

### Prerequisites

- **GCC/G++** (version 11+) or **Clang** (version 14+)
- **Make** (GNU Make 4.0+)
- **Git** (for version control)
- **Python 3** (optional, for test scripts)

### Clone the Repository

```bash
git clone https://github.com/<your-username>/NeelKant.git
cd NeelKant
```

### Build & Run

```bash
# Build the compiler
make build

# Run the compiler on a source file
./bin/compiler examples/hello.src

# Clean build artifacts
make clean
```

---

## Testing

```bash
# Run all tests
make test

# Run specific module tests
make test-lexer
make test-parser
make test-semantic

# Run integration tests
make test-integration
```

---

## Documentation

Detailed documentation is available in the [`docs/`](docs/) directory:

| Document | Description |
|----------|-------------|
| [Language Specification](docs/grammar/language_spec.md) | Full grammar and language rules |
| [Design Overview](docs/design/architecture.md) | Architectural design decisions |
| [Lexer Design](docs/design/lexer_design.md) | Lexer module design details |
| [Parser Design](docs/design/parser_design.md) | Parser & AST design details |
| [Meeting Notes](docs/meeting-notes/) | Team meeting records |
| [Development Guide](docs/dev_guide.md) | Setup and development workflow |

---

## Contributing

We welcome contributions from all team members! Please read our [Contributing Guide](CONTRIBUTING.md) before submitting changes.

**Quick workflow:**
1. Create a branch from `develop` for your feature/fix
2. Make your changes with clear, descriptive commits
3. Write/update tests for your changes
4. Open a Pull Request and request review
5. Address review feedback and merge

---

## Team

| Name | Role | Module |
|------|------|--------|
| TBD  | Team Lead | Overall Architecture |
| TBD  | Developer | Lexer |
| TBD  | Developer | Parser |
| TBD  | Developer | Semantic Analysis |
| TBD  | Developer | IR & Code Generation |
| TBD  | Developer | Testing & QA |

---

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---

## Milestones

- [ ] **Phase 1**: Language specification & grammar design
- [ ] **Phase 2**: Lexer implementation
- [ ] **Phase 3**: Parser & AST construction
- [ ] **Phase 4**: Semantic analysis
- [ ] **Phase 5**: IR generation
- [ ] **Phase 6**: Optimization passes
- [ ] **Phase 7**: Code generation
- [ ] **Phase 8**: Testing & documentation

---

<p align="center">
  <i>Built with ❤️ by our compiler team</i>
</p>
