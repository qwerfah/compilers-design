#include "..\..\include\grammar_transform\left_recursion_remove.h"

LeftRecursionRemove::LeftRecursionRemove(Grammar& grammar)
	: GrammarTransform{ grammar }
{
}

void LeftRecursionRemove::operator()()
{
	std::vector<std::shared_ptr<Symbol>> symbols;

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

void LeftRecursionRemove::_unfoldRules(const std::vector<std::shared_ptr<Symbol>>::iterator& i)
{
	for (auto j = _grammar.nonTerminals.begin(); j != i; j++)
	{
		std::vector<std::shared_ptr<Rule>> ijRules;
		std::vector<std::shared_ptr<Rule>> jRules;

		_findIjRules(i, j, ijRules);
		_findIndexedRules(j, jRules);

		std::erase_if(_grammar.rules, [&](auto r) {
			return std::find(ijRules.begin(), ijRules.end(), r) != ijRules.end(); });

		for (auto& ijRule : ijRules)
		{
			for (auto& jRule : jRules)
			{
				std::vector<std::shared_ptr<Symbol>> right{ jRule->getRight() };
				right.insert(right.end(), ++(ijRule->getRight().begin()), ijRule->getRight().end());
				_grammar.rules.push_back(std::shared_ptr<Rule>{ new Rule{ ijRule->getLeft(), right } });
			}
		}
	}
}

std::shared_ptr<Symbol> LeftRecursionRemove::_removeDirectRecursion(
	const std::vector<std::shared_ptr<Symbol>>::iterator& i)
{
	std::vector<std::shared_ptr<Rule>> recRules;
	std::vector<std::shared_ptr<Rule>> indRules;
	// Ищем все Ai-правила
	_findRecursiveRules(i, recRules);

	if (recRules.empty())  return nullptr;

	_findIndexedRules(i, indRules);
	// Удаляем правила вида Ai -> Ai a
	std::erase_if(_grammar.rules, [&](auto r) {
		return std::find(recRules.begin(), recRules.end(), r) != recRules.end(); });
	// Добавляем новый нетерминал Аi'
	std::shared_ptr<Symbol> symbol{ new Symbol{
		(*i)->getName() + "'", (*i)->getSpell(), (*i)->getType()} };
	// Добавляем правила вида Ai -> b Ai'
	for (auto& rule : indRules)
	{
		std::vector<std::shared_ptr<Symbol>> right{ rule->getRight() };
		right.push_back(symbol);
		_grammar.rules.push_back(std::shared_ptr<Rule>{ new Rule{ rule->getLeft(), right } });
	}
	// Добавляем правила вида Ai' -> a | a Ai'
	for (auto& rule : recRules)
	{
		std::vector<std::shared_ptr<Symbol>> right{};
		right.insert(right.begin(), ++(rule->getRight().begin()), rule->getRight().end());
		_grammar.rules.push_back(std::shared_ptr<Rule>{ new Rule{ { symbol }, right } });
		right.push_back(symbol);
		_grammar.rules.push_back(std::shared_ptr<Rule>{ new Rule{ { symbol }, right } });
	}

	return symbol;
}

void LeftRecursionRemove::_findRecursiveRules(
	const std::vector<std::shared_ptr<Symbol>>::iterator& it,
	std::vector<std::shared_ptr<Rule>>& rules)
{
	std::copy_if(_grammar.rules.begin(), _grammar.rules.end(),
		std::back_inserter(rules), [&](auto rule)
		{
			return (rule->getRight().empty())
				? false
				: rule->getLeft()[0] == *it && rule->getRight()[0] == *it;
		});
}

void LeftRecursionRemove::_findIndexedRules(
	const std::vector<std::shared_ptr<Symbol>>::iterator& it,
	std::vector<std::shared_ptr<Rule>>& rules)
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

void LeftRecursionRemove::_findIjRules(
	const std::vector<std::shared_ptr<Symbol>>::iterator& i,
	const std::vector<std::shared_ptr<Symbol>>::iterator& j,
	std::vector<std::shared_ptr<Rule>>& rules)
{
	std::copy_if(_grammar.rules.begin(), _grammar.rules.end(), std::back_inserter(rules),
		[&](auto rule)
		{
			return (rule->getRight().empty())
				? false
				: rule->getLeft()[0] == *i && rule->getRight()[0] == *j;
		});
}