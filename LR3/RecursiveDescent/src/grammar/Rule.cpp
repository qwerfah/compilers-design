#include "../../include/grammar/rule.h"

Rule::Rule(const symbol_vector& left,
	       const symbol_vector& right) : Rule()
{
	if (left.empty())
	{ 
		throw std::invalid_argument("Left part of rule is empty.");
	}

	if (std::any_of(left.begin(), left.end(), [&](auto s) {return !s;}))
	{
		throw std::invalid_argument{ "Null pointer in left part of rule." };
	}

	if (std::any_of(right.begin(), right.end(), [&](auto s) {return !s; }))
	{
		throw std::invalid_argument{ "Null pointer in right part of rule." };
	}

	_left = left;
	_right = right;
}

void Rule::addToLeft(const symbol_ptr& symbol)
{
	_left.push_back(symbol);
}

void Rule::addToRight(const symbol_ptr& symbol)
{
	_right.push_back(symbol);
}

const symbol_vector& Rule::getLeft() const
{
	return _left;
}

const symbol_vector& Rule::getRight() const
{
	return _right;
}

bool operator < (const Rule& left, const Rule& right)
{
	return left._left.size() < right._left.size();
}

bool operator==(const Rule& left, const Rule& right)
{
	return (left._left == right._left) && (left._right == right._right);
}
