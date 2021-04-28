#pragma once

#include "grammar_transform.h"

/// <summary>
/// Functional object that implements left factorization algorithm.
/// </summary>
class LeftFactorization : GrammarTransform
{
public:
	/// <param name="grammar"> Grammar object to apply left factorization. </param>
	LeftFactorization(Grammar& grammar);

	/// <summary>
	/// Left factorization algorithm implementation.
	/// </summary>
	virtual void operator()() override;

private:
	/// <summary>
	/// Find and replace first set of rules with common prefix in right-hand side.
	/// </summary>
	/// <param name="symbol"> Nonterminal symbol that expected 
	/// in left-hand side of the rule. </param>
	/// <returns></returns>
	symbol_ptr _replaceRules(const symbol_ptr& symbol);

	/// <summary>
	/// Find all rules with common symbol on specified position in right-hand side.
	/// </summary>
	/// <param name="rules"> Set of rules to search. </param>
	/// /// <param name="result"> Set to save the result. </param>
	/// <param name="pos"> Position of symbol in right-hand side of the rule. </param>
	void _findCommonRules(const rule_set& rules, rule_set& result, size_t pos);
};

