#include "Parser.h"
#include <stdexcept>
#include "ParsingError.h"

using namespace std;

Parser::Parser(const std::vector<Token>& tokens) : 
	tokens(tokens), 
	size(tokens.size()), 
	pos(0) 
{}

const Token& Parser::get(int relativePosition) const {
	const int position = pos + relativePosition;
	if (position >= size) return END_OF_FILE;
	return tokens.at(position);
}

bool Parser::match(TokenType type) {
	const Token current = get(0);
	if (type != current.getType()) return false;
	pos++;
	return true;
}

Tree::Node* Parser::node() {
	if (size == 0)
		return Tree::makeDummy();

	const Token& nodeNameToken = get(0);

	if (match(TokenType::NODE_NAME)) {

		if (match(TokenType::EQUAL)) {
			const Token& nodeValueToken = get(0);

			if (match(TokenType::NODE_VALUE)) {
				return Tree::makeNode(nodeNameToken.getText(), nodeValueToken.getText());
			}
			else if (match(TokenType::LBRACKET)) {
				if (match(TokenType::RBRACKET)) 
					throw ParsingError("List of nodes cannot be empty, position number "
						+ to_string(pos) + " of the token array");
				
				Tree::Node* currentNode = Tree::makeNode(nodeNameToken.getText());

				while (true) {
					currentNode->appendChild(node());

					if (match(TokenType::RBRACKET)) {
						return currentNode;
					}
				}
			}
			else {
				throw ParsingError("Missing required token 'NODE_VALUE' or 'LBRACKET' at position "
					+ to_string(pos) + " of the token array");
			}
		}
		else {
			throw ParsingError("Missing required token 'EQUAL' at position "
				+ to_string(pos) + " of the token array");
		}
	}
	else if (match(TokenType::END_OF_FILE)) {
		throw ParsingError("Some token 'RBRACKET' is missing");
	}
	else {
		throw ParsingError("Missing required token 'NODE_NAME' at position "
			+ to_string(pos) + " of the token array");
	}

}

Tree* Parser::parse() {
	pos = 0;
	Tree::Node* n = node();
	if (pos < size) 
		throw ParsingError("Excessive tokens found starting from position number "
		+ to_string(pos) + " of the token array");
	return new Tree(n);
}