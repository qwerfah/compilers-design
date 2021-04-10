#include "..\..\include\grammar_transform\epsilon_rule_remove.h"

EpsilonRuleRemove::EpsilonRuleRemove(Grammar& grammar)
	: GrammarTransform{ grammar }
{
}

void EpsilonRuleRemove::operator()()
{
	symbol_set ne{};

	_buildNeSet(ne);

	for (auto& s : ne)
	{
		_replaceEpsilonRules(s);
	}
}

void EpsilonRuleRemove::_buildNeSet(symbol_set& ne)
{
	size_t prev{ 0 };

	ne.clear();

	do
	{
		prev = ne.size();
		rule_vector rules;
		// Find all the rules whose right side is empty or consists of symbols from prev
		std::copy_if(_grammar.rules.begin(), _grammar.rules.end(), 
			std::back_inserter(rules), [&](auto r) 
			{
				return r->getRight().empty() || std::all_of(
					r->getRight().begin(), r->getRight().end(), [&](auto s)
					{
						return ne.contains(s);
					});
			});

		for (auto& rule : rules)
		{
			ne.insert(rule->getLeft()[0]);
		}
	} 
	while (prev != ne.size());
}

void EpsilonRuleRemove::_replaceEpsilonRules(const symbol_ptr& symbol)
{
	rule_vector rules{};

	for (auto& rule : _grammar.rules)
	{
		symbol_iterator_vector occurrences{};
		_findAllOccurrences(symbol, rule->getRight(), occurrences);
	}
}

void EpsilonRuleRemove::_findAllOccurrences(
	const symbol_ptr& symbol, 
	const symbol_vector& symbols, 
	symbol_iterator_vector& occurrences)
{
	if (!symbol)
	{
		throw std::invalid_argument{ "Null symbol pointer." };
	}

	if (std::any_of(symbols.begin(), symbols.end(), [&](auto s) { return !s; }))
	{
		throw std::invalid_argument{ "Null pointer in symbol vector." };
	}

	occurrences.clear();

	auto it = symbols.begin();

	while (symbols.end() != (it = std::find(it, symbols.end(), symbol)))
	{
		occurrences.push_back(it++);
	}
}

