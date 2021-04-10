#pragma once

#include <stdexcept>
#include <algorithm>

#include "symbol.h"
#include "../typedefs.h"

/// <summary>
/// Grammar withdrawal rule.
/// </summary>
class Rule
{
public:
	Rule() = default;
	Rule(const symbol_vector& left, 
		 const symbol_vector& right);

	/// <summary>
	/// Add new symbol to left part of the rule.
	/// </summary>
	/// <param name="symbol"> New symbol. </param>
	void addToLeft(const symbol_ptr& symbol);

	/// <summary>
	/// Add new symbol to right part of the rule.
	/// </summary>
	/// <param name="symbol"> New symbol. </param>
	void addToRight(const symbol_ptr& symbol);

	/// <summary>
	/// Get left part of the rule.
	/// </summary>
	/// <returns></returns>
	const symbol_vector& getLeft() const;

	/// <summary>
	/// Get right part of the rule.
	/// </summary>
	/// <returns></returns>
	const symbol_vector& getRight() const;

	friend bool operator < (const Rule& left, const Rule& right);

private:
	/// <summary>
	/// Left part of the rule.
	/// </summary>
	symbol_vector _left{};

	/// <summary>
	/// Right part of the rule.
	/// </summary>
	symbol_vector _right{};
};

