#include "Or.h"

Or::Or(std::shared_ptr<RegularExpression>& expr1, std::shared_ptr<RegularExpression>& expr2) :
	RegularExpression(expr1->getRawString() + OR_STR + expr2->getRawString()),
	_leftExpr(expr1),
	_rightExpr(expr2)
{ }

Or::Or(std::shared_ptr<RegularExpression>&& expr1, std::shared_ptr<RegularExpression>&& expr2) :
	RegularExpression(expr1->getRawString() + OR_STR + expr2->getRawString()),
	_leftExpr(expr1),
	_rightExpr(expr2)
{ }

const std::shared_ptr<RegularExpression>& Or::getLeftExpr() const
{
	return _leftExpr;
}

const std::shared_ptr<RegularExpression>& Or::getRightExpr() const
{
	return _rightExpr;
}

RegularExpression& Or::operator = (const RegularExpression& other)
{
	if (this != &other)
	{
		auto orExpr = static_cast<const Or&>(other);
		RegularExpression::operator = (other);

		_leftExpr = orExpr._leftExpr;
		_rightExpr = orExpr._rightExpr;
	}

	return *this;
}


