#include "../../../include/regex/regular_expression/literal.h"

Literal::Literal(char c, LiteralType type) : 
	RegularExpression(std::string({ c })), _c(c), _type(type)
{
}

char Literal::getChar() const
{
	return _c;
}

LiteralType Literal::getType() const
{
	return _type;
}
