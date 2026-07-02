#include "ast.h"

class Parser {
private:
    std::vector<Token> tokens;
    int current = 0;

    bool isAtEnd() {
        return current >= tokens.size() || tokens[current].type == TokenType::END_OF_FILE;
    }

public:
    Parser(std::vector<Token> tokens) {
        this->tokens = tokens;
    }

    virtual ~Parser() = default;

    Token peek() {
        if (isAtEnd()) return tokens.back();
        return tokens[current];
    }

    Token advance() {
        if (!isAtEnd()) current++;
        return tokens[current - 1];
    }

    bool match(TokenType expectedType) {
        if (isAtEnd()) return false;
        if (tokens[current].type == expectedType) {
            advance();
            return true;
        }
        return false;
    }

    ASTNode* parse();

private:
    ASTNode* parseStatement();
    ASTNode* parseVarDecl(bool isConst, bool isDynamic);
    ASTNode* parseAssignment();
    ASTNode* parseBlock();
    ASTNode* parseIfStatement();
    ASTNode* parseWhileStatement();
    ASTNode* parseForStatement();
    ASTNode* parseDoWhileStatement();
    ASTNode* parseReturnStatement();
    ASTNode* parseCaseStatement();
    void synchronize();
};