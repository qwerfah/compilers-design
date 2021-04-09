#pragma once

#include "grammar_transform.h"
#include "../grammar/grammar.h"

class LeftRecursionRemove : GrammarTransform
{
public:
	LeftRecursionRemove(Grammar& grammar);

	virtual void operator()() override;

private:
	void _unfoldRules(const std::vector<std::shared_ptr<Symbol>>::iterator& i);
	
	std::shared_ptr<Symbol> _removeDirectRecursion(
		const std::vector<std::shared_ptr<Symbol>>::iterator& i);

	void _findRecursiveRules(
		const std::vector<std::shared_ptr<Symbol>>::iterator& it,
		std::vector<std::shared_ptr<Rule>>& rules);

	void _findIndexedRules(
		const std::vector<std::shared_ptr<Symbol>>::iterator& it,
		std::vector<std::shared_ptr<Rule>>& rules);

	void _findIjRules(
		const std::vector<std::shared_ptr<Symbol>>::iterator& i,
		const std::vector<std::shared_ptr<Symbol>>::iterator& j,
		std::vector<std::shared_ptr<Rule>>& rules);
};

