#include "UrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& errorText)
	: std::invalid_argument(errorText)
{
}
