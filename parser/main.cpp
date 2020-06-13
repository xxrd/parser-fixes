#include <iostream>
#include <fstream>
#include "Tree.h"
#include "Lexer.h"
#include "Parser.h"
#include "LexicalAnalysisError.h"
#include "ParsingError.h"

using namespace std;

int main(int argc, char *argv[]) {

	ifstream in;
	in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	ofstream out;
	out.exceptions(std::ofstream::failbit | std::ofstream::badbit);

	try {
		if (argc != 3) throw ParserError("The number of command line parameters is not equal to two");

		in.open(argv[1]);
		out.open(argv[2]);

		Lexer lexer(in);
		const vector<Token>& tokens = lexer.tokenize();

		Parser parser(tokens);
		shared_ptr<Tree> tree(parser.parse());

		out << *tree;

	}
	catch (const LexicalAnalysisError& e) {
		cout << "Invalid data format" << " (Lexer error: " << e.what() << ")" << endl;
	}
	catch (const ParsingError& e) {
		cout << "Invalid data format" << " (Parser error: " << e.what() << ")" << endl;
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}

}