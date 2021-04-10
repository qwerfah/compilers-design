#include "..\..\include\grammar_transform\epsilon_rule_remove.h"

EpsilonRuleRemove::EpsilonRuleRemove(Grammar& grammar)
	: GrammarTransform{ grammar }
{
}

void EpsilonRuleRemove::operator()()
{
}

void EpsilonRuleRemove::_buildNeSet(std::set<std::shared_ptr<Symbol>>& ne)
{
	size_t prev{ 0 };

	do
	{
		prev = ne.size();
		std::set<std::shared_ptr<Rule>> rules;
		// Find all the rules whose right side is empty or consists of symbols from prev
		std::copy_if(_grammar.rules.begin(), _grammar.rules.end(), 
			std::inserter(rules, rules.end()), [&](auto r) 
			{
				return r->getRight().empty() || std::all_of(
					r->getRight().begin(), r->getRight().end(), [&](auto s)
					{
						return ne.contains(s);
					});
			});

		for (auto& rule : rules)
		{
			ne.insert(rule->getRight()[0]);
		}
	} 
	while (prev != ne.size());
}
