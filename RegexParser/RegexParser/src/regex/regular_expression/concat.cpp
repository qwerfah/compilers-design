#include "../../../include/regex/regular_expression/concat.h"

Concat::Concat(std::shared_ptr<RegularExpression>& expr1, std::shared_ptr<RegularExpression>& expr2) :
	RegularExpression(expr1->getRawString() + expr2->getRawString()),
	_leftExpr(expr1),
	_rightExpr(expr2)
{
}

Concat::Concat(std::shared_ptr<RegularExpression>&& expr1, std::shared_ptr<RegularExpression>&& expr2) :
	RegularExpression(expr1->getRawString() + expr2->getRawString()),
	_leftExpr(expr1),
	_rightExpr(expr2)
{ }

const std::shared_ptr<RegularExpression>& Concat::getLeftExpr() const
{
	return _leftExpr;
}

const std::shared_ptr<RegularExpression>& Concat::getRightExpr() const
{
	return _rightExpr;
}

RegularExpression& Concat::operator = (const RegularExpression& other)
{
	if (this != &other)
	{
		auto concat = static_cast<const Concat&>(other);
		RegularExpression::operator = (other);

		_leftExpr = concat._leftExpr;
		_rightExpr = concat._rightExpr;
	}

	return *this;
}
