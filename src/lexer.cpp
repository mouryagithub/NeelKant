#include "lexer.h"
#include <stdexcept>
using namespace std;

Lexer::Lexer(string source) {
	src = source;
	pos = 0;
	line = 1;
	col = 1;
}

char Lexer::current() {
	if(pos < src.size()) {
		return src[pos];
	}	
	else {
		return '\0';
	}
}

char Lexer::peek() {
	if(pos+1 < src.size()) {
		return src[pos+1];
	}	
	else {
		return '\0';
	}
}

char Lexer::advance() {
	char c = src[pos];
	pos++;
	if(c == '\n') {
		line++;
		col = 1;
	}
	else {
		col++;
	}
	return c;
}

void Lexer::skipWhitespace() {
	while(current() == ' ' || current() == '\t' || current() == '\n' || current() == '\r') {
		advance();
	}
}

Token Lexer::readNumber() {
	string num="";
	bool isFloat = false;
	
	while(isdigit(current())) {
		num += advance();
	}
	if(current() == '.' && isdigit(peek())) {
		isFloat = true;
		num += advance();
		while(isdigit(current())) {
			num += advance();
		}
	}
	
	Token t;
	t.value = num;
	t.line = line;
	t.col = col;
	t.type = (isFloat) ?TokenType::LIT_FLOAT : TokenType::LIT_INT;
	return t;
}

Token Lexer::readString() {
	string value="";
	advance();
	while(current() != '"' && current() != '\0') {
		value += advance();
	}
	advance();
	Token t;
	t.value = value;
	t.line = line;
	t.col = col;
	t.type = TokenType::LIT_STRING;
	return t;
}

Token Lexer::readChar() {
	string value = "";
	advance();
	while(current() != '\'' && current() != '\0') {
		value += advance();
	}
	advance();
	Token t;
	t.value = value;
	t.line = line;
	t.col = col;
	t.type = TokenType::LIT_CHAR;
	return t;
}

Token Lexer::readIdentifierOrKeyword() {
	string word = "";
	while(isdigit(current()) || isalpha(current()) || current() == '_') {
		word += advance();
	}
	TokenType type = lookupKeyword(word);
	Token t;
	t.value = word;
	t.line = line;
	t.col = col;
	t.type = type;
	return t;
}

TokenType Lexer::lookupKeyword(string word) {
	for(int i = 0; i < word.size(); i++) {
		word[i] = toupper(word[i]);
	}
	
	if(word == "U8") {
		return TokenType::U8;
	}
	if(word == "U16") {
		return TokenType::U16;
	}
	if(word == "U32") {
		return TokenType::U32;
	}
	if(word == "U64") {
		return TokenType::U64;
	}
	if(word == "I8") {
		return TokenType::I8;
	}
	if(word == "I16") {
		return TokenType::I16;
	}
	if(word == "I32") {
		return TokenType::I32;
	}
	if(word == "I64") {
		return TokenType::I64;
	}
	if(word == "F32") {
		return TokenType::F32;
	}
	if(word == "F64") {
		return TokenType::F64;
	}
	if(word == "BOOL") {
		return TokenType::BOOL;
	}
	if(word == "CHAR") {
		return TokenType::CHAR;
	}
	if(word == "STRING") {
		return TokenType::STRING;
	}
	if(word == "VOID") {
		return TokenType::VOID;
	}
	if(word == "TRUE") {
		return TokenType::TRUEVAL;
	}
	if(word == "FALSE") {
		return TokenType::FALSEVAL;
	}
	if(word == "NULL") {
		return TokenType::NULLVAL;
	}
	if(word == "CONST") {
		return TokenType::CONST;
	}
	if(word == "IF") {
		return TokenType::IF;
	}
	if(word == "ELSE") {
		return TokenType::ELSE;
	}
	if(word == "CASE") {
		return TokenType::CASE;
	}
	if(word == "DEFAULT") {
		return TokenType::DEFAULT;
	}
	if(word == "FOR") {
		return TokenType::FOR;
	}
	if(word == "DO") {
		return TokenType::DO;
	}
	if(word == "WHILE") {
		return TokenType::WHILE;
	}
	if(word == "PRI") {
		return TokenType::PRI;
	}
	if(word == "PRO") {
		return TokenType::PRO;
	}
	if(word == "PUB") {
		return TokenType::PUB;
	}
	if(word == "FN") {
		return TokenType::FN;
	}
	if(word == "RETURN") {
		return TokenType::RETURN;
	}
	
	return TokenType::IDENTIFIER;
}

Token Lexer::readOperator() {
	char c = advance();
	char n = current();
	Token t;
	t.line = line;
	t.col = col;
	
	switch(c) {
		case '+' : t.type = TokenType::PLUS; t.value = "+"; break;
		case '-' : t.type = TokenType::MINUS; t.value = "-"; break;
		case '*' : if(n == '*') { advance(); t.type = TokenType::EXPONENT; t.value = "**";} else {t.type = TokenType::STAR; t.value = "*";} break;
		case '/' : if(n == '/') { advance(); t.type = TokenType::INT_DIV; t.value = "//";} else {t.type = TokenType::SLASH; t.value = "/";} break;
		case '%' : t.type = TokenType::PERCENT; t.value = "%"; break;
		case '&' : if(n == '&') { advance(); t.type = TokenType::AND; t.value = "&&";} else {t.type = TokenType::BIT_AND; t.value = "&";} break;
		case '|' : if(n == '|') { advance(); t.type = TokenType::OR; t.value = "||";} else {t.type = TokenType::BIT_OR; t.value = "|";} break;
		case '!' : if(n == '=') { advance(); t.type = TokenType::NEQ; t.value = "!=";} else {t.type = TokenType::NOT; t.value = "!";} break;
		case '~' : t.type = TokenType::BIT_NOT; t.value = "~"; break;
		case '^' : t.type = TokenType::BIT_XOR; t.value = "^"; break;
		case '=' : if(n == '=') { advance(); t.type = TokenType::EQ; t.value = "==";} else {t.type = TokenType::ASSIGN; t.value = "=";} break;
		case '>' : if(n == '=') { advance(); t.type = TokenType::GTEQ; t.value = ">=";} else {t.type = TokenType::GT; t.value = ">";} break;
		case '<' : if(n == '=') { advance(); t.type = TokenType::LTEQ; t.value = "<=";} else {t.type = TokenType::LT; t.value = "<";} break;
		case ':' : t.type = TokenType::COLON; t.value = ":"; break;
		case ';' : t.type = TokenType::SEMICOLON; t.value = ";"; break;
		case ',' : t.type = TokenType::COMMA; t.value = ","; break;
		case '(' : t.type = TokenType::LPAREN; t.value = "("; break;
		case ')' : t.type = TokenType::RPAREN; t.value = ")"; break;
		case '{' : t.type = TokenType::LBRACE; t.value = "{"; break;
		case '}' : t.type = TokenType::RBRACE; t.value = "}"; break;
		case '[' : t.type = TokenType::LBRACKET; t.value = "["; break;
		case ']' : t.type = TokenType::RBRACKET; t.value = "]"; break;
		default:
    throw runtime_error("Unknown character '" + string(1, c) + "' at line " + to_string(line) + ", col " + to_string(col));
	}
	return t;
}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;

    while(current() != '\0') {
        skipWhitespace();
        if(current() == '\0') break;

        if(isdigit(current())) {
            tokens.push_back(readNumber());
        } else if(current() == '"') {
            tokens.push_back(readString());
        } else if(current() == '\'') {
            tokens.push_back(readChar());
        } else if(isalpha(current()) || current() == '_') {
            tokens.push_back(readIdentifierOrKeyword());
        } else {
            tokens.push_back(readOperator());
        }
    }

    Token eof;
    eof.type = TokenType::END_OF_FILE;
    eof.value = "";
    eof.line = line;
    eof.col = col;
    tokens.push_back(eof);

    return tokens;
}