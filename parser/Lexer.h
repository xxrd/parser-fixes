#pragma once
#include <vector>
#include <string>
#include "TokenType.h"
#include "Token.h"

class Lexer {
private:
	const std::vector<TokenType> tokenTypes = {
		TokenType::NODE_NAME, TokenType::NODE_VALUE,
		TokenType::EQUAL, TokenType::LBRACKET,
		TokenType::RBRACKET
	};
	const std::string input;
	std::vector<Token> tokens;
	int pos;
	int length;

	char peek(int relativePosition) const;
	char next();
	void addToken(TokenType type);
	void addToken(TokenType type, const std::string& text);
	void tokenizeName();
	void tokenizeValue();
	void tokenizeEqual();
	void tokenizeLBracket();
	void tokenizeRBracket();

public:
	explicit Lexer(const std::string& input);
	std::vector<Token> tokenize();

};