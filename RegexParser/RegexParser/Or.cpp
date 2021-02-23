#include "Or.h"

Or::Or(const RegularExpression& expr1, const RegularExpression& expr2) : 
	RegularExpression(expr1.getRawString() + OR_STR + expr2.getRawString()),
	_leftExpr(expr1),
	_rightExpr(expr2)
{ }

const RegularExpression& Or::getLeftExpr() const
{
	return _leftExpr;
}

const RegularExpression& Or::getRightExpr() const
{
	return _rightExpr;
}


