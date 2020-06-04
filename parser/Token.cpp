#include "Token.h";
#include <string>

using namespace std;

Token::Token(TokenType type, const std::string& text) : 
	type(type), 
	text(text) 
{}

void Token::setText(const std::string& text) noexcept {
	this->text = text;
}

void Token::setType(TokenType type) noexcept {
	this->type = type;
}

const std::string& Token::getText() const noexcept {
	return text;
}

const TokenType& Token::getType() const noexcept {
	return type;
}
