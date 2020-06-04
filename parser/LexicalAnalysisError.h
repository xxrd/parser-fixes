#pragma once
#include "ParserError.h"

class LexicalAnalysisError : virtual public ParserError {
	using ParserError::ParserError;

};