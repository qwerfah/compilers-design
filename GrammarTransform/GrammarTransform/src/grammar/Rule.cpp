#include "../../include/grammar/Rule.h"

Rule::Rule(const std::vector<Symbol>& left, const std::vector<Symbol>& right)
{
	if (left.empty() || right.empty())
	{
		throw std::invalid_argument("Left or right part of rule is empty.");
	}

	_left = right;
	_right = right;
}

void Rule::addToLeft(const Symbol& symbol)
{
	_left.push_back(symbol);
}

void Rule::addToRight(const Symbol& symbol)
{
	_right.push_back(symbol);
}

const std::vector<Symbol>& Rule::getLeft() const
{
	return _left;
}

const std::vector<Symbol>& Rule::getRight() const
{
	return _right;
}

