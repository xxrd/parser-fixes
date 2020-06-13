#pragma once
#include <vector>
#include <string>
#include "TokenType.h"
#include "Token.h"
#include <fstream>

class Lexer {
private:
	const std::vector<TokenType> tokenTypes = {
		TokenType::NODE_NAME, TokenType::NODE_VALUE,
		TokenType::EQUAL, TokenType::LBRACKET,
		TokenType::RBRACKET
	};
	std::ifstream& input;
	std::vector<Token> tokens;

	char peek() const;
	char next();
	long long currentPosition();
	void addToken(TokenType type);
	void addToken(TokenType type, const std::string& text);
	void tokenizeName();
	void tokenizeValue();
	void tokenizeEqual();
	void tokenizeLBracket();
	void tokenizeRBracket();

public:
	explicit Lexer(std::ifstream& input);
	const std::vector<Token>& tokenize();

};