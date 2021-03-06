#pragma once

#include "grammar_transform.h"

/// <summary>
/// Left recursion delition algorithm.
/// </summary>
class LeftRecursionRemove : GrammarTransform
{
public:
	LeftRecursionRemove(Grammar& grammar);
	/// <summary>
	/// Left recursion delition algorithm implementation.
	/// </summary>
	virtual void operator()() override;

private:
	/// <summary>
	/// Unfold indirect recursion.
	/// </summary>
	/// <param name="i"> Nonterminal from which starts unfolding. </param>
	void _unfoldRules(const symbol_iterator& i);
	
	/// <summary>
	/// Remove direct recursion starting from specified nonterminal.
	/// </summary>
	/// <param name="i"> Nonterminal from which starts delition. </param>
	/// <returns> New nonterminal produced as the result of delition
	/// or nullptr if there were no direct recursive rules. </returns>
	symbol_ptr _removeDirectRecursion(const symbol_iterator& i);

	/// <summary>
	/// Find rules with direct recursion.
	/// </summary>
	/// <param name="it"> Nonterminal for which searching recursive rules. </param>
	/// <param name="rules"> Vector to save the result. </param>
	void _findRecursiveRules(const symbol_iterator& it, rule_vector& rules);

	/// <summary>
	/// Find rules of type Ai -> B, where B starts from terminal or Ak and k > i.
	/// </summary>
	/// <param name="it"> Nonterminal Ai. </param>
	/// <param name="rules"> Vector to save the result. </param>
	void _findIndexedRules(const symbol_iterator& it, rule_vector& rules);

	/// <summary>
	/// Find rules of type Ai -> Aj B.
	/// </summary>
	/// <param name="i"> Iterator for nonterminal Ai. </param>
	/// <param name="j"> Iterator for nonterminal Aj.</param>
	/// <param name="rules"> Vector to save the result. </param>
	void _findIjRules(const symbol_iterator& i, const symbol_iterator& j, rule_vector& rules);
};

