# Compiler Project Makefile
# ========================

# Compiler settings
CC      := gcc
CXX     := g++
CFLAGS  := -Wall -Wextra -std=c11 -Iinclude
CXXFLAGS:= -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS :=

# Directories
SRC_DIR   := src
BUILD_DIR := build
BIN_DIR   := bin
TEST_DIR  := tests

# Output binary
TARGET := $(BIN_DIR)/compiler

# Find all source files
C_SOURCES   := $(shell find $(SRC_DIR) -name '*.c' 2>/dev/null)
CPP_SOURCES := $(shell find $(SRC_DIR) -name '*.cpp' 2>/dev/null)
OBJECTS     := $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) \
               $(CPP_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
.PHONY: all
all: build

# Build the compiler
.PHONY: build
build: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^
	@echo "✅ Build successful: $(TARGET)"

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile C++ files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Run all tests
.PHONY: test
test: build
	@echo "🧪 Running all tests..."
	@echo "TODO: Add test runner"

# Run lexer tests
.PHONY: test-lexer
test-lexer: build
	@echo "🧪 Running lexer tests..."
	@echo "TODO: Add lexer tests"

# Run parser tests
.PHONY: test-parser
test-parser: build
	@echo "🧪 Running parser tests..."
	@echo "TODO: Add parser tests"

# Run semantic tests
.PHONY: test-semantic
test-semantic: build
	@echo "🧪 Running semantic analysis tests..."
	@echo "TODO: Add semantic tests"

# Run integration tests
.PHONY: test-integration
test-integration: build
	@echo "🧪 Running integration tests..."
	@echo "TODO: Add integration tests"

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "🧹 Cleaned build artifacts"

# Show help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  build            - Build the compiler"
	@echo "  test             - Run all tests"
	@echo "  test-lexer       - Run lexer tests"
	@echo "  test-parser      - Run parser tests"
	@echo "  test-semantic    - Run semantic analysis tests"
	@echo "  test-integration - Run integration tests"
	@echo "  clean            - Remove build artifacts"
	@echo "  help             - Show this help message"
