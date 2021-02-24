#include "RegexParser.h"
#include <stdexcept>

RegularExpression RegexParser::parse(const std::string& regex) const
{
	std::string copy = regex;

	return _parse(copy);
}

RegularExpression RegexParser::_parse(std::string& regex) const
{
	if (regex.empty())
	{
		throw std::invalid_argument("Regular expression string is empty.");
	}


}
