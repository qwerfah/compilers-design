#pragma once

#include <set>
#include <algorithm>
#include <iterator>

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
	void _buildNeSet(std::set<std::shared_ptr<Symbol>>& ne);
};
