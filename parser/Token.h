#pragma once
#include "TokenType.h"
#include <string>

class Token {
private:
	TokenType type;
	std::string text;

public:
	Token(TokenType type, const std::string& text);
	void setText(const std::string& text) noexcept;
	void setType(TokenType type) noexcept;
	const std::string& getText() const noexcept;
	const TokenType& getType() const noexcept;

};