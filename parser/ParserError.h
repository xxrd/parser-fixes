#pragma once
#include <stdexcept>

class ParserError : virtual public std::runtime_error {
	using std::runtime_error::runtime_error;

};