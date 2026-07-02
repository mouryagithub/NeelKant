#include "parser.h"

ASTNode* Parser::parseStatement() {
    Token currentToken = peek();

    switch (currentToken.type) {
        case TokenType::VAR:
            advance();
            return parseVarDecl(false, true);

        case TokenType::CONST:
            advance();
            return parseVarDecl(true, false);

        case TokenType::IDENTIFIER: {
            bool isDeclaration = false;
            if (current + 1 < tokens.size()) {
                TokenType nextType = tokens[current + 1].type;
                if (nextType == TokenType::COLON || nextType == TokenType::COMMA) {
                    isDeclaration = true;
                }
            }
            if (isDeclaration) {
                return parseVarDecl(false, false);
            }
            return parseAssignment();
        }

        default:
            return nullptr;
    }
}

ASTNode* Parser::parseVarDecl(bool isConst, bool isDynamic) {
    std::vector<std::string> names;

    if (peek().type == TokenType::IDENTIFIER) {
        names.push_back(advance().value);
    }

    while (match(TokenType::COMMA)) {
        if (peek().type == TokenType::IDENTIFIER) {
            names.push_back(advance().value);
        }
    }

    std::string type = "variant";
    int arraySize = -1;

    if (!isDynamic) {
        match(TokenType::COLON);
        if (peek().type != TokenType::ASSIGN && peek().type != TokenType::SEMICOLON) {
            type = advance().value;
        }

        if (match(TokenType::LBRACKET)) {
            arraySize = std::stoi(advance().value);
            match(TokenType::RBRACKET);
        }
    }

    ASTNode* initialValue = nullptr;
    if (match(TokenType::ASSIGN)) {
        initialValue = parseExpression(); 
    }

    match(TokenType::SEMICOLON);

    std::vector<ASTNode*> declNodes;
    for (size_t i = 0; i < names.size(); i++) {
        ASTNode* nodeValue = (i == 0 || initialValue == nullptr) ? initialValue : initialValue->clone();
        declNodes.push_back(new VarDecLastNode(names[i], type, arraySize, isConst, nodeValue));
    }

    if (declNodes.size() == 1) {
        return declNodes[0];
    }
    return new BlockStmtASTNode(declNodes);
}

ASTNode* Parser::parseAssignment(){
    std::string name;
    ASTNode* assignment = nullptr;
    if(peek().type == TokenType::IDENTIFIER){
        name = advance().value;
    }
    if(match(TokenType::ASSIGN)){
        ASTNode* expression = parseExpression();
        if(match(TokenType::SEMICOLON)){
            assignment = new AssignmentStmtASTNode(name,expression);
        }else{
            delete expression;
        }
    }
    return assignment;
}

ASTNode* Parser::parseBlock(){
    std::vector<ASTNode*>statements;
    if(match(TokenType::LBRACE)){
        while(peek().type != TokenType::RBRACE && peek().type != TokenType::END_OF_FILE){
            ASTNode* stmt = parseStatement();
            if(stmt != nullptr) statements.push_back(stmt);
        }
        if(match(TokenType::RBRACE)){
            return new BlockStmtASTNode(statements);
        }
        else{
            for (size_t i = 0; i < statements.size(); i++) {
            delete statements[i];
        }
        return nullptr;
        }
    }
    else{
        return nullptr;
    }
}

ASTNode* Parser::parseWhileStatement() {
    if (!match(TokenType::LPAREN)) {
        return nullptr;
    }

    ASTNode* condition = parseExpression();
    if (condition == nullptr) {
        return nullptr;
    }

    if (!match(TokenType::RPAREN)) {
        delete condition;
        return nullptr;
    }

    ASTNode* body = parseBlock();
    if (body == nullptr) {
        delete condition;
        return nullptr;
    }

    return new WhileStmtASTNode(condition, body);
}

ASTNode* Parser::parseDoWhileStatement() {
    ASTNode* body = parseBlock();
    if (body == nullptr) {
        return nullptr;
    }

    if (!match(TokenType::WHILE)) {
        delete body;
        return nullptr;
    }

    if (!match(TokenType::LPAREN)) {
        delete body;
        return nullptr;
    }

    ASTNode* condition = parseExpression();
    if (condition == nullptr) {
        delete body;
        return nullptr;
    }

    if (!match(TokenType::RPAREN)) {
        delete body;
        delete condition;
        return nullptr;
    }

    if (!match(TokenType::SEMICOLON)) {
        delete body;
        delete condition;
        return nullptr;
    }

    return new DoWhileStmtASTNode(body, condition);
}

