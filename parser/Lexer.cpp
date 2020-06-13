#include "Lexer.h";
#include <stdexcept>
#include "LexicalAnalysisError.h"

using namespace std;

Lexer::Lexer(std::ifstream& input) :
	input(input)
{}

char Lexer::peek() const {
	if (input.eof()) return EOF;
	return input.peek();
}

char Lexer::next() {
	if (input.eof()) return EOF;
	input.get();
	return input.peek();
}

long long Lexer::currentPosition() {
	return input.tellg();
}

void Lexer::addToken(TokenType type) {
	addToken(type, "");
}

void Lexer::addToken(TokenType type, const std::string& text) {
	tokens.push_back(Token(type, text));
}

void Lexer::tokenizeName() {
	string buffer;
	char current = peek();

	while (true) {
		if (!isalpha(current) && !isdigit(current) && (current != '_')) {
			break;
		}
		buffer.push_back(current);
		current = next();
	}
	addToken(TokenType::NODE_NAME, buffer);

}

void Lexer::tokenizeValue() {
	string buffer;
	char current = next();

	while (true) {
		if (current == '"') {
			break;
		}
		if (current == '\n') {
			throw LexicalAnalysisError("Unexpected end of line at position " + to_string(currentPosition()) + " of input");
		}
		if (current == EOF) {
			throw LexicalAnalysisError("Not found a closing symbol '\"'");
		}
		buffer.push_back(current);
		current = next();
	}
	addToken(TokenType::NODE_VALUE, buffer);
	next();

}

void Lexer::tokenizeEqual() {
	addToken(TokenType::EQUAL);
	next();
}

void Lexer::tokenizeLBracket() {
	addToken(TokenType::LBRACKET);
	next();
}

void Lexer::tokenizeRBracket() {
	addToken(TokenType::RBRACKET);
	next();
}

const vector<Token>& Lexer::tokenize() {
	while (true) {
		char current = peek();

		if (isalpha(current) || current == '_') {
			tokenizeName();
		}
		else if (current == '=') {
			tokenizeEqual();
		}
		else if (current == '"') {
			tokenizeValue();
		}
		else if (current == '{') {
			tokenizeLBracket();
		}
		else if (current == '}') {
			tokenizeRBracket();
		}
		else if (isspace(current)) {
			next();
		}
		else if (current == EOF) {
			break;
		}
		else {
			throw LexicalAnalysisError("Unknown sybmol at position " + to_string(currentPosition()) + " of input");
		}
	}
	return tokens;

}

