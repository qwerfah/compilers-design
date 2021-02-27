#include "Repeat.h"

Repeat::Repeat(std::shared_ptr<RegularExpression>& expr, RepeatType type) :
	RegularExpression(expr->getRawString() + REPEAT_STR),
	_expr(expr), _type(type)
{ }

Repeat::Repeat(std::shared_ptr<RegularExpression>&& expr, RepeatType type) :
	RegularExpression(expr->getRawString() + REPEAT_STR),
	_expr(expr), _type(type)
{ }

const std::shared_ptr<RegularExpression>& Repeat::getExpr() const
{
	return _expr;
}

RepeatType Repeat::getType() const
{
	return _type;
}

RegularExpression& Repeat::operator = (const RegularExpression& other)
{
	if (this != &other)
	{
		auto repeat = static_cast<const Repeat&>(other);
		RegularExpression::operator = (other);

		_expr = repeat._expr;
	}

	return *this;
}


