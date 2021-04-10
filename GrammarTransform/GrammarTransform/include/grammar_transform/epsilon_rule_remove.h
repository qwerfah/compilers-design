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

	void _replaceEpsilonRules(const symbol_ptr& symbol);
	void _findAllOccurrences(
		const symbol_ptr& symbol,
		const symbol_vector& symbols,
		symbol_iterator_vector& occurrences);
};

