#include "..\..\include\grammar_transform\left_recursion_remove.h"

LeftRecursionRemove::LeftRecursionRemove(Grammar& grammar)
	: GrammarTransform{ grammar }
{
}

void LeftRecursionRemove::operator()()
{
	symbol_vector symbols;

	for (auto i = _grammar.nonTerminals.begin(); i != _grammar.nonTerminals.end(); i++)
	{
		_unfoldRules(i);
		if (auto symbol = _removeDirectRecursion(i))
		{
			symbols.push_back(symbol);
		}
	}

	_grammar.nonTerminals.insert(_grammar.nonTerminals.end(), symbols.begin(), symbols.end());
}

void LeftRecursionRemove::_unfoldRules(const symbol_iterator& i)
{
	for (auto j = _grammar.nonTerminals.begin(); j != i; j++)
	{
		rule_vector ijRules;
		rule_vector jRules;

		_findIjRules(i, j, ijRules);
		_findIndexedRules(j, jRules);

		std::erase_if(_grammar.rules, [&](auto r) {
			return std::find(ijRules.begin(), ijRules.end(), r) != ijRules.end(); });

		for (auto& ijRule : ijRules)
		{
			for (auto& jRule : jRules)
			{
				symbol_vector right{ jRule->getRight() };
				right.insert(right.end(), ++(ijRule->getRight().begin()), ijRule->getRight().end());
				_grammar.rules.push_back(rule_ptr{ new Rule{ ijRule->getLeft(), right } });
			}
		}
	}
}

symbol_ptr LeftRecursionRemove::_removeDirectRecursion(const symbol_iterator& i)
{
	rule_vector recRules;
	rule_vector indRules;
	// Searching all Ai-rules
	_findRecursiveRules(i, recRules);

	if (recRules.empty())  return nullptr;

	_findIndexedRules(i, indRules);
	// Removing rules of type Ai -> Ai a
	std::erase_if(_grammar.rules, [&](auto r) {
		return std::find(recRules.begin(), recRules.end(), r) != recRules.end(); });
	// Add new nonterminal symbol Ài'
	symbol_ptr symbol{ new Symbol{ (*i)->getName() + "'", (*i)->getSpell(), (*i)->getType()} };
	// Add rules of type Ai -> b Ai'
	for (auto& rule : indRules)
	{
		symbol_vector right{ rule->getRight() };
		right.push_back(symbol);
		_grammar.rules.push_back(rule_ptr{ new Rule{ rule->getLeft(), right } });
	}
	// Add rules of type Ai' -> a | a Ai'
	for (auto& rule : recRules)
	{
		symbol_vector right{};
		right.insert(right.begin(), ++(rule->getRight().begin()), rule->getRight().end());
		_grammar.rules.push_back(rule_ptr{ new Rule{ { symbol }, right } });
		right.push_back(symbol);
		_grammar.rules.push_back(rule_ptr{ new Rule{ { symbol }, right } });
	}

	return symbol;
}

void LeftRecursionRemove::_findRecursiveRules(const symbol_iterator& it, rule_vector& rules)
{
	std::copy_if(_grammar.rules.begin(), _grammar.rules.end(),
		std::back_inserter(rules), [&](auto rule)
		{
			return (rule->getRight().empty())
				? false
				: rule->getLeft()[0] == *it && rule->getRight()[0] == *it;
		});
}

void LeftRecursionRemove::_findIndexedRules(const symbol_iterator& it, rule_vector& rules)
{
	std::copy_if(_grammar.rules.begin(), _grammar.rules.end(), std::back_inserter(rules),
		[&](auto rule)
		{
			if (rule->getRight().empty() || rule->getLeft()[0] != *it) return false;
			auto s = std::find(_grammar.nonTerminals.begin(),
				_grammar.nonTerminals.end(), rule->getRight()[0]);
			return s == _grammar.nonTerminals.end() || s > it;
		});
}

void LeftRecursionRemove::_findIjRules(const symbol_iterator& i, const symbol_iterator& j, rule_vector& rules)
{
	std::copy_if(_grammar.rules.begin(), _grammar.rules.end(), std::back_inserter(rules),
		[&](auto rule)
		{
			return (rule->getRight().empty())
				? false
				: rule->getLeft()[0] == *i && rule->getRight()[0] == *j;
		});
}