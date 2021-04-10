#pragma once

#include <vector>
#include <stdexcept>
#include <memory>
#include <algorithm>

#include "symbol.h"

/// <summary>
/// Grammar withdrawal rule.
/// </summary>
class Rule
{
public:
	Rule() = default;
	Rule(const std::vector<std::shared_ptr<Symbol>>& left, 
		 const std::vector<std::shared_ptr<Symbol>>& right);

	/// <summary>
	/// Add new symbol to left part of the rule.
	/// </summary>
	/// <param name="symbol"> New symbol. </param>
	void addToLeft(const std::shared_ptr<Symbol>& symbol);

	/// <summary>
	/// Add new symbol to right part of the rule.
	/// </summary>
	/// <param name="symbol"> New symbol. </param>
	void addToRight(const std::shared_ptr<Symbol>& symbol);

	/// <summary>
	/// Get left part of the rule.
	/// </summary>
	/// <returns></returns>
	const std::vector<std::shared_ptr<Symbol>>& getLeft() const;

	/// <summary>
	/// Get right part of the rule.
	/// </summary>
	/// <returns></returns>
	const std::vector<std::shared_ptr<Symbol>>& getRight() const;

	friend bool operator < (const Rule& left, const Rule& right);

private:
	/// <summary>
	/// Left part of the rule.
	/// </summary>
	std::vector<std::shared_ptr<Symbol>> _left{};

	/// <summary>
	/// Right part of the rule.
	/// </summary>
	std::vector<std::shared_ptr<Symbol>> _right{};
};

