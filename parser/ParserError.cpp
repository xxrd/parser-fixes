#include "ParserError.h"

using namespace std;

ParserError::ParserError(const std::string& msg) :
    error_message(msg)
{}

ParserError::~ParserError() {}

const char* ParserError::what() const  noexcept  {
    return error_message.c_str();
}
