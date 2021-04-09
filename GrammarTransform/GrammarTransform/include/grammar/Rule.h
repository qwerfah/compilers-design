#pragma once

#include <vector>
#include <stdexcept>
#include <memory>
#include <algorithm>

#include "symbol.h"

class Rule
{
public:
	Rule() = default;
	Rule(const std::vector<std::shared_ptr<Symbol>>& left, 
		 const std::vector<std::shared_ptr<Symbol>>& right);

	void addToLeft(const std::shared_ptr<Symbol>& symbol);
	void addToRight(const std::shared_ptr<Symbol>& symbol);

	const std::vector<std::shared_ptr<Symbol>>& getLeft() const;
	const std::vector<std::shared_ptr<Symbol>>& getRight() const;

	friend bool operator < (const Rule& left, const Rule& right);

private:
	std::vector<std::shared_ptr<Symbol>> _left{};
	std::vector<std::shared_ptr<Symbol>> _right{};
};

