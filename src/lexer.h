#pragma once
#include "token.h"
#include <vector>
#include <string>

using namespace std;
class Lexer {
	public:
	Lexer(string source);
	vector<Token> tokenize();
	
	private:
	string src;
	int pos,line,col;
	
	char current();
	char peek();
	char advance();
	void skipWhitespace();
	
	Token readNumber();
	Token readString();
	Token readChar();
	Token readIdentifierOrKeyword();
	Token readOperator();
	TokenType lookupKeyword(string word);
	
};