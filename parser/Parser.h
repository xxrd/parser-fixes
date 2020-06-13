#pragma once
#include "Token.h"
#include "TokenType.h"
#include <vector>
#include "Tree.h"

class Parser {
private:
	const Token END_OF_FILE = Token(TokenType::END_OF_FILE, "");
	const std::vector<Token>& tokens;
	int pos;
	int size;

	const Token& get(int relativePosition) const;
	bool match(TokenType type);
	Tree::Node* node();

public:
	explicit Parser(const std::vector<Token>& tokens);
	Tree* parse();

};