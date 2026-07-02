#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../token.h"

// The abstract base class for all nodes in the tree
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual ASTNode* clone() const = 0;
};

// Class for the variables
class VarDecLastNode: public ASTNode {
    public:
    std::string name; // name of the variable
    std::string type; //type of the variable
    int arraySize;
    bool isConst;     //is it a constant or not
    ASTNode* value;   //what is the value it is storing

    //Constructor
    VarDecLastNode (std::string name, std::string type, int arraySize, bool isConst, ASTNode* value){
        this->name = name;
        this->type = type;
        this->arraySize = arraySize;
        this->isConst = isConst;
        this->value = value;
    }

    //deconstructor for the VarDecLASTNode class
    virtual ~VarDecLastNode() {
        if(value != nullptr){delete value;}
    }

    // for later stages of the compiler we will need the whole thing to be replicated then we use it.
    virtual ASTNode* clone() const override{
        ASTNode* clonedValue = (value!=nullptr) ? value->clone() : nullptr;
        return new VarDecLastNode(name, type, arraySize, isConst, clonedValue);
    }
};

// Class for the assignment (Value assignment or modification after decelaration)
class AssignmentStmtASTNode: public ASTNode {
    public:
    std::string name; //variable name
    ASTNode* value;   //value of the variable

    //Constructor
    AssignmentStmtASTNode (std::string name, ASTNode* value){
        this->name = name;
        this->value = value;
    }

    //destructor for the AssignmentStmtASTNode class
    virtual ~AssignmentStmtASTNode() {
        if(value != nullptr){delete value;}
    }

    // for later stages of the compiler we will need the whole thing to be replicated then we use it.
    virtual ASTNode* clone() const override{
        ASTNode* clonedValue = (value!=nullptr) ? value->clone() : nullptr;
        return new AssignmentStmtASTNode(name,clonedValue);
    }
};

// Class for holding the block of statements weather it may be for if,else,for,while,do while etc.
class BlockStmtASTNode: public ASTNode{
    public:
    std::vector<ASTNode*> statements;

    //constructor
    BlockStmtASTNode(std::vector<ASTNode*> statements){
        this->statements = statements;
    }

    //destructor
    virtual ~BlockStmtASTNode() {
        for(int i = 0; i != statements.size(); i++){
            delete statements[i];
        }
    }

    // for later stages of the compiler we will need the whole thing to be replicated then we use it.
    virtual ASTNode* clone() const override{
        std::vector<ASTNode*> clonedStatements(statements.size());
        for(int i = 0; i != statements.size(); i++){
            clonedStatements[i] = statements[i]->clone();
        }
        return new BlockStmtASTNode(clonedStatements);
    }

};

class IfStmtASTNode: public ASTNode{
    public:
    ASTNode* condition;
    ASTNode* body;
    ASTNode* elseBody;

    IfStmtASTNode (ASTNode* condition, ASTNode* body, ASTNode* elseBody = nullptr){
        this->condition = condition;
        this->body = body;
        this->elseBody = elseBody;
    }

    virtual ~IfStmtASTNode(){
        delete condition;
        delete body;
        if(elseBody != nullptr) delete elseBody;
    }

    virtual ASTNode* clone() const override {
        ASTNode* clonedCondition = (condition != nullptr) ? condition->clone() : nullptr;
        ASTNode* clonedBody = (body != nullptr) ? body->clone() : nullptr;
        ASTNode* clonedElseBody = (elseBody != nullptr) ? elseBody->clone() : nullptr;
        return new IfStmtASTNode(clonedCondition, clonedBody, clonedElseBody);
    }
};

// Class for handling while loops (e.g., while(condition) { ... })
class WhileStmtASTNode : public ASTNode {
public:
    ASTNode* condition; // The loop terminal evaluation condition
    ASTNode* body;      // The block or statement executed within the loop

    // Constructor
    WhileStmtASTNode(ASTNode* condition, ASTNode* body) {
        this->condition = condition;
        this->body = body;
    }

    // Destructor to clean up inner components safely
    virtual ~WhileStmtASTNode() {
        if (condition != nullptr) delete condition;
        if (body != nullptr) delete body;
    }

    // Clone method for deep-copying loop branches safely
    virtual ASTNode* clone() const override {
        ASTNode* clonedCondition = (condition != nullptr) ? condition->clone() : nullptr;
        ASTNode* clonedBody = (body != nullptr) ? body->clone() : nullptr;
        return new WhileStmtASTNode(clonedCondition, clonedBody);
    }
};

// Class for handling for loops (e.g., for(init; condition; increment) { ... })
class ForStmtASTNode : public ASTNode {
public:
    ASTNode* variableDeceleration; // e.g., variable declaration like "i : i32 = 0" 
    ASTNode* condition;      // The truth evaluation constraint
    ASTNode* increment;      // The counter alteration statement (e.g., assignment)
    ASTNode* body;           // The block or statement executed within the loop

    // Constructor
    ForStmtASTNode(ASTNode* initialization, ASTNode* condition, ASTNode* increment, ASTNode* body) {
        this->variableDeceleration = initialization;
        this->condition = condition;
        this->increment = increment;
        this->body = body;
    }

    // Destructor ensuring zero memory leaks for all four pointers
    virtual ~ForStmtASTNode() {
        if (variableDeceleration != nullptr) delete variableDeceleration;
        if (condition != nullptr) delete condition;
        if (increment != nullptr) delete increment;
        if (body != nullptr) delete body;
    }

    // Clone method implementing complete subtree duplication
    virtual ASTNode* clone() const override {
        ASTNode* clonedInit = (variableDeceleration != nullptr) ? variableDeceleration->clone() : nullptr;
        ASTNode* clonedCond = (condition != nullptr) ? condition->clone() : nullptr;
        ASTNode* clonedInc  = (increment != nullptr) ? increment->clone() : nullptr;
        ASTNode* clonedBody = (body != nullptr) ? body->clone() : nullptr;
        return new ForStmtASTNode(clonedInit, clonedCond, clonedInc, clonedBody);
    }
};

class ReturnStmtASTNode : public ASTNode {
public:
    ASTNode* value; // Points to Person 3's expression, or nullptr if empty "return;"

    ReturnStmtASTNode(ASTNode* value = nullptr) {
        this->value = value;
    }

    virtual ~ReturnStmtASTNode() {
        if (value != nullptr) delete value;
    }

    virtual ASTNode* clone() const override {
        ASTNode* clonedValue = (value != nullptr) ? value->clone() : nullptr;
        return new ReturnStmtASTNode(clonedValue);
    }
};

class DoWhileStmtASTNode : public ASTNode {
public:
    ASTNode* body;       // The code block executed inside the loop
    ASTNode* condition;  // The termination check expression evaluated at the bottom

    DoWhileStmtASTNode(ASTNode* body, ASTNode* condition) {
        this->body = body;
        this->condition = condition;
    }

    virtual ~DoWhileStmtASTNode() {
        if (body != nullptr) delete body;
        if (condition != nullptr) delete condition;
    }

    virtual ASTNode* clone() const override {
        ASTNode* clonedBody = (body != nullptr) ? body->clone() : nullptr;
        ASTNode* clonedCondition = (condition != nullptr) ? condition->clone() : nullptr;
        return new DoWhileStmtASTNode(clonedBody, clonedCondition);
    }
};

class CaseStmtASTNode : public ASTNode {
public:
    std::string matchVariable;           // The variable name being evaluated (e.g., "x")
    std::vector<ASTNode*> caseValues;   // The literal constants (e.g., 1, 2, 3)
    std::vector<ASTNode*> caseBodies;   // The corresponding code blocks to execute
    ASTNode* defaultBody;               // Fallback code block, or nullptr if none

    CaseStmtASTNode(std::string var, std::vector<ASTNode*> values, std::vector<ASTNode*> bodies, ASTNode* defaultBlock = nullptr) {
        this->matchVariable = var;
        this->caseValues = values;
        this->caseBodies = bodies;
        this->defaultBody = defaultBlock;
    }

    virtual ~CaseStmtASTNode() {
        for (size_t i = 0; i < caseValues.size(); i++) {
            if (caseValues[i] != nullptr) delete caseValues[i];
        }
        for (size_t i = 0; i < caseBodies.size(); i++) {
            if (caseBodies[i] != nullptr) delete caseBodies[i];
        }
        if (defaultBody != nullptr) delete defaultBody;
    }

    virtual ASTNode* clone() const override {
        std::vector<ASTNode*> clonedValues(caseValues.size());
        std::vector<ASTNode*> clonedBodies(caseBodies.size());
        
        for (size_t i = 0; i < caseValues.size(); i++) {
            clonedValues[i] = (caseValues[i] != nullptr) ? caseValues[i]->clone() : nullptr;
        }
        for (size_t i = 0; i < caseBodies.size(); i++) {
            clonedBodies[i] = (caseBodies[i] != nullptr) ? caseBodies[i]->clone() : nullptr;
        }
        ASTNode* clonedDefault = (defaultBody != nullptr) ? defaultBody->clone() : nullptr;

        return new CaseStmtASTNode(matchVariable, clonedValues, clonedBodies, clonedDefault);
    }
};

