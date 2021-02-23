#include "Repeat.h"

Repeat::Repeat(const RegularExpression& expr) : 
	RegularExpression(expr.getRawString() + REPEAT_STR),
	_expr(expr)
{ }

const RegularExpression& Repeat::getExpr() const
{
	return _expr;
}


