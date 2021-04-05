#pragma once

#include <vector>
#include <stdexcept>

#include "Symbol.h"

class Rule
{
public:
	Rule() = default;
	Rule(const std::vector<Symbol>& left, const std::vector<Symbol>& right);

	void addToLeft(const Symbol& symbol);
	void addToRight(const Symbol& symbol);

	const std::vector<Symbol>& getLeft() const;
	const std::vector<Symbol>& getRight() const;

private:
	std::vector<Symbol> _left{};
	std::vector<Symbol> _right{};
};

