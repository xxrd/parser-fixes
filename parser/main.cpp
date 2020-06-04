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

		const string inStr((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

		Lexer lexer(inStr);
		vector<Token> tokens = lexer.tokenize();

		Parser parser(tokens);
		shared_ptr<Tree> tree(parser.parse());
		
		out << *tree;
		
		in.close();
		out.close();
	}
	catch (const LexicalAnalysisError& e) {
		cout << "Invalid data format" << endl;
		in.close();
		out.close();
	}
	catch (const ParsingError& e) {
		cout << "Invalid data format" << endl;
		in.close();
		out.close();
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		in.close();
		out.close();
	}


}