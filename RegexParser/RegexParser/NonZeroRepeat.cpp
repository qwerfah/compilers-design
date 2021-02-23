#include "NonZeroRepeat.h"

NonZeroRepeat::NonZeroRepeat(const RegularExpression& expr) : 
	RegularExpression(expr.getRawString() + NON_ZERO_REPEAT_STR),
	_expr(expr)
{ }

const RegularExpression& NonZeroRepeat::getExpr() const
{
	return _expr;
}


