# Contributing Guide

Thank you for contributing to our Compiler Project! This document provides guidelines and best practices for team collaboration.

---

## 📋 Table of Contents

- [Branch Strategy](#branch-strategy)
- [Commit Guidelines](#commit-guidelines)
- [Pull Request Process](#pull-request-process)
- [Code Style](#code-style)
- [Issue Tracking](#issue-tracking)
- [Code Review](#code-review)
- [Development Workflow](#development-workflow)

---

## Branch Strategy

We follow a **Git Flow** branching model:

```
main          ← stable releases only
  └── develop ← integration branch (all features merge here)
        ├── feature/lexer-tokenizer    ← feature branches
        ├── feature/parser-ast         ← feature branches
        ├── bugfix/token-error         ← bug fix branches
        └── docs/grammar-spec         ← documentation branches
```

### Branch Naming Convention

| Type | Format | Example |
|------|--------|---------|
| Feature | `feature/<module>-<description>` | `feature/lexer-string-literals` |
| Bug Fix | `bugfix/<description>` | `bugfix/parser-null-check` |
| Documentation | `docs/<description>` | `docs/grammar-specification` |
| Hotfix | `hotfix/<description>` | `hotfix/codegen-segfault` |
| Refactor | `refactor/<description>` | `refactor/ast-node-hierarchy` |

### Creating a Branch

```bash
# Always branch from develop
git checkout develop
git pull origin develop
git checkout -b feature/your-feature-name
```

---

## Commit Guidelines

We use **Conventional Commits** for clear, structured commit messages.

### Format

```
<type>(<scope>): <short description>

[optional body]

[optional footer]
```

### Types

| Type | Description |
|------|-------------|
| `feat` | A new feature |
| `fix` | A bug fix |
| `docs` | Documentation changes |
| `test` | Adding or updating tests |
| `refactor` | Code refactoring (no feature/fix) |
| `style` | Code style changes (formatting, etc.) |
| `build` | Build system changes |
| `ci` | CI/CD configuration changes |

### Examples

```bash
feat(lexer): add support for string literal tokenization
fix(parser): handle empty expression in if-statement
docs(grammar): add specification for loop constructs
test(lexer): add unit tests for numeric literals
refactor(ast): simplify node visitor pattern
```

### Rules
- Keep the subject line under **72 characters**
- Use the **imperative mood** ("add" not "added")
- Do **not** end the subject line with a period
- Separate subject from body with a blank line

---

## Pull Request Process

### Before Opening a PR

1. ✅ Ensure your code compiles without errors
2. ✅ Run the full test suite and all tests pass
3. ✅ Update documentation if needed
4. ✅ Rebase your branch on the latest `develop`
5. ✅ Self-review your changes

### PR Requirements

- **Title**: Use the conventional commit format
- **Description**: Fill out the PR template completely
- **Labels**: Add appropriate labels (feature, bugfix, docs, etc.)
- **Reviewers**: Assign at least **1 team member** for review
- **Linked Issues**: Reference related issues using `Closes #<issue-number>`

### Review & Merge

- At least **1 approval** is required to merge
- All CI checks must pass
- Resolve all review comments before merging
- Use **Squash and Merge** for feature branches
- Delete the branch after merging

---

## Code Style

### General Rules

- Use **4 spaces** for indentation (no tabs)
- Maximum line length: **100 characters**
- Add comments for complex logic
- Use meaningful variable and function names
- Each file should have a header comment describing its purpose

### File Header Template

```c
/**
 * @file filename.c
 * @brief Brief description of the file's purpose
 * @author Your Name
 * @date YYYY-MM-DD
 * 
 * Detailed description if needed.
 */
```

### Function Documentation

```c
/**
 * @brief Brief description of what the function does
 * @param param1 Description of parameter 1
 * @param param2 Description of parameter 2
 * @return Description of return value
 */
ReturnType function_name(Type param1, Type param2) {
    // implementation
}
```

---

## Issue Tracking

### Creating Issues

Use the provided issue templates:

1. **Bug Report** — For reporting bugs
2. **Feature Request** — For proposing new features
3. **Task** — For general development tasks
4. **Documentation** — For documentation updates

### Labels

| Label | Description | Color |
|-------|-------------|-------|
| `bug` | Something isn't working | 🔴 Red |
| `feature` | New feature request | 🟢 Green |
| `enhancement` | Improvement to existing feature | 🔵 Blue |
| `documentation` | Documentation updates | 📘 Light Blue |
| `lexer` | Related to lexer module | 🟡 Yellow |
| `parser` | Related to parser module | 🟠 Orange |
| `semantic` | Related to semantic analysis | 🟣 Purple |
| `codegen` | Related to code generation | 🟤 Brown |
| `good-first-issue` | Good for newcomers | 💚 |
| `priority-high` | High priority | 🔴 |
| `priority-medium` | Medium priority | 🟡 |
| `priority-low` | Low priority | 🟢 |

---

## Code Review

### Reviewer Checklist

- [ ] Code follows our style guidelines
- [ ] Logic is correct and handles edge cases
- [ ] Tests are included and pass
- [ ] No unnecessary complexity
- [ ] Documentation is updated
- [ ] No security vulnerabilities
- [ ] Performance is acceptable

### Giving Feedback

- Be **constructive** and **respectful**
- Explain **why** a change is needed, not just what
- Use GitHub's suggestion feature for small fixes
- Distinguish between blocking issues and optional suggestions

---

## Development Workflow

### Daily Workflow

```bash
# 1. Start your day - sync with develop
git checkout develop
git pull origin develop

# 2. Switch to your feature branch (or create one)
git checkout feature/your-feature
git rebase develop

# 3. Make changes, commit frequently
git add .
git commit -m "feat(module): description"

# 4. Push your branch
git push origin feature/your-feature

# 5. When ready, open a Pull Request on GitHub
```

### Weekly Team Sync

- Review open PRs and issues
- Update project board
- Discuss blockers and dependencies
- Plan upcoming tasks

---

## Questions?

If you have any questions about the contribution process, reach out to the team lead or open a discussion in the GitHub Discussions tab.
