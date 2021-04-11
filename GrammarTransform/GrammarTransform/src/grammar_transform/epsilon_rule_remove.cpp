#include "..\..\include\grammar_transform\epsilon_rule_remove.h"

EpsilonRuleRemove::EpsilonRuleRemove(Grammar& grammar)
	: GrammarTransform{ grammar }
{
}

void EpsilonRuleRemove::operator()()
{
	symbol_set ne{};

	_buildNeSet(ne);
	_replaceEpsilonRules(ne);
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

void EpsilonRuleRemove::_replaceEpsilonRules(const symbol_set& symbols)
{
	rule_vector rules{};
	size_t size = _grammar.rules.size();

	for (size_t i = 0; i < size; i++)
	{
		index_vector occurrences{};
		index_combination_vector combinations{};

		_findAllOccurrences(symbols, _grammar.rules[i]->getRight(), occurrences);
		_findAllCombinations(occurrences, combinations);

		for (auto& combination : combinations)
		{
			symbol_vector right{ _grammar.rules[i]->getRight() };

			for (auto index : combination)
			{
				right.erase(right.begin() + index);
			}

			rule_ptr rule{ new Rule{ _grammar.rules[i]->getLeft(), right } };
			_grammar.rules.push_back(rule);
		}
	}
}

void EpsilonRuleRemove::_findAllOccurrences(
	const symbol_set& symbols,
	const symbol_vector& right,
	index_vector& occurrences)
{
	if (!std::any_of(symbols.begin(), symbols.end(), [&](auto s) { return !s; }))
	{
		throw std::invalid_argument{ "Null symbol pointer in symbol vector." };
	}

	if (std::any_of(right.begin(), right.end(), [&](auto s) { return !s; }))
	{
		throw std::invalid_argument{ "Null pointer in right part vector." };
	}

	occurrences.clear();

	for (auto& symbol : symbols)
	{
		auto it = right.begin();

		while (right.end() != (it = std::find(it, right.end(), symbol)))
		{
			occurrences.push_back(it - right.begin());
			it++;
		}
	}
}

void EpsilonRuleRemove::_findAllCombinations(
	const index_vector& indexes, 
	index_combination_vector& combinations)
{
	int n = indexes.size(); 
	for (int r = 1; r <= n; r++)
	{
		std::vector<bool> v(n);
		std::fill(v.begin(), v.begin() + r, true);

		do
		{
			index_vector combination{};

			for (int i = 0; i < n; i++)
			{
				if (v[i]) combination.push_back(indexes[i]);
			}

			combinations.push_back(combination);
		} while (std::prev_permutation(v.begin(), v.end()));
	}
}

