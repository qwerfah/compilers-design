#include "../../include/grammar_transform/left_factorization.h"

LeftFactorization::LeftFactorization(Grammar& grammar) 
	: GrammarTransform(grammar)
{
}

void LeftFactorization::operator()()
{
	symbol_vector symbols{};

	for (auto& symbol : _grammar.nonTerminals)
	{
		for (auto s = _replaceRules(symbol); s != nullptr; symbols.push_back(s), s = _replaceRules(symbol));
	}

	_grammar.nonTerminals.insert(_grammar.nonTerminals.end(), symbols.begin(), symbols.end());
}

symbol_ptr LeftFactorization::_replaceRules(const symbol_ptr& symbol)
{
	rule_set rules{};

	// Find all rules started with current nonterminal
	std::copy_if(_grammar.rules.begin(), _grammar.rules.end(), std::inserter(rules, rules.end()),
		[&](auto& rule)
		{
			return *rule->getLeft().begin() == symbol;
		});

	if (rules.size() < 2) return nullptr;

	// Find max length of right-hand side
	size_t max_length = (*std::max_element(rules.begin(), rules.end(), 
		[&](auto& a, auto& b) 
		{ 
			return a->getRight().size() < b->getRight().size(); 
		}))->getRight().size();

	size_t prefix_length;
	// Determine rules with longest common prefix
	for (prefix_length = 0; prefix_length < max_length; prefix_length++)
	{
		rule_set curr{};

		_findCommonRules(rules, curr, prefix_length);
		if (curr.size() < 2 && !prefix_length) return nullptr;
		if (curr.size() < 2) break;

		rules = curr;
	}

	// Remove all rules with common prefix from grammar
	std::erase_if(_grammar.rules, [&](auto r) {
		return std::find(rules.begin(), rules.end(), r) != rules.end(); });

	// New nonterminal symbol A'
	symbol_ptr new_symbol
	{
		new Symbol
		{
			symbol->getName().substr(0, symbol->getName().rfind('#')) + "#" + std::to_string(*symbol->count),
			symbol->getSpell(),
			symbol->getType(),
			symbol->count
		}
	};

	(*symbol->count)++;

	// New rule A -> aA' where a - common prefix
	decltype(auto) right = (*rules.begin())->getRight();
	symbol_vector new_right{ right.begin(), right.begin() + prefix_length };
	new_right.push_back(new_symbol);
	rule_ptr new_rule{ new Rule{ symbol_vector{ symbol }, new_right } };

	_grammar.rules.push_back(new_rule);

	for (auto& rule : rules)
	{
		symbol_vector new_right
		{
			rule->getRight().begin() + prefix_length, rule->getRight().end()
		};
		rule_ptr new_rule{ new Rule{ symbol_vector{new_symbol}, new_right } };
		_grammar.rules.push_back(new_rule);
	}

	return new_symbol;
}

void LeftFactorization::_findCommonRules(const rule_set& rules, rule_set& result, size_t pos)
{
	for (auto& rule : rules)
	{
		if ((pos >= rule->getRight().size())) continue;

		result.clear();
		auto it = rules.begin();

		while (it != rules.end())
		{
			it = std::find_if(it, rules.end(),
				[&](auto& r)
				{
					return (pos < r->getRight().size()) && (r->getRight()[pos] == rule->getRight()[pos]);
				});

			if (it != rules.end())
			{
				result.insert(*it);
				it++;
			}
		}

		if (result.size() > 1) return;
	}
}
