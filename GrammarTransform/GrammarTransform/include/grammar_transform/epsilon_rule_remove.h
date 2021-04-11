#pragma once

#include "../grammar/symbol.h"
#include "../grammar/rule.h"
#include "grammar_transform.h"

/// <summary>
/// Epsilon-rule delition algorithm.
/// </summary>
class EpsilonRuleRemove : GrammarTransform
{
public:
	EpsilonRuleRemove(Grammar& grammar);

	/// <summary>
	/// Epsilon-rule delition algorithm implementation.
	/// </summary>
	virtual void operator()() override;

private:
	/// <summary>
	/// Build Ne set of nonterminals from which an empty chain is reachable.
	/// </summary>
	/// <param name="ne"> Set of nonterminals from which an empty chain is reachable. </param>
	void _buildNeSet(symbol_set& ne);

	/// <summary>
	/// Replace all rules that contain any of epsilon symbols.
	/// </summary>
	/// <param name="symbols"> Symbols from which empty chain is reachable. </param>
	void _replaceEpsilonRules(const symbol_set& symbols);

	/// <summary>
	/// Find all occurrences of symbols from first vector in the given right part of the rule.
	/// </summary>
	/// <param name="symbols"> Symbols to search. </param>
	/// <param name="right"> Rigth part of the rule. </param>
	/// <param name="occurrences"> Vector to save the result in. </param>
	void _findAllOccurrences(
		const symbol_set& symbols,
		const symbol_vector& right,
		index_vector& occurrences);

	/// <summary>
	/// Find all combinations of symbols from vector and put it into last argument.
	/// </summary>
	void _findAllCombinations(const index_vector& indexes, index_combination_vector& combinations);
};

