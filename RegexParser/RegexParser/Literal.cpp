#include "Literal.h"

Literal::Literal(char c) : RegularExpression(std::string({ c })), _c(c)
{ }

char Literal::getChar() const
{
	return _c;
}
