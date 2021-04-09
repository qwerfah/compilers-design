#include "../../include/grammar/Grammar.h"

Grammar::Grammar(Grammar&& grammar)
{
	_terminals = std::move(grammar._terminals);
	_nonTerminals = std::move(grammar._nonTerminals);
	_rules = std::move(grammar._rules);
	_axiom = std::move(grammar._axiom);
}

void Grammar::setAxiom(const std::shared_ptr<Symbol>& symbol)
{
	_axiom = symbol;
}

void Grammar::addTerminal(const std::shared_ptr<Symbol>& symbol)
{
	_terminals.push_back(symbol);
}

void Grammar::addNonTerminal(const std::shared_ptr<Symbol>& symbol)
{
	_nonTerminals.push_back(symbol);
}

void Grammar::addRule(const std::shared_ptr<Rule>& rule)
{
	_rules.push_back(rule);
}

const std::shared_ptr<Symbol>& Grammar::getAxiom() const
{
	return _axiom;
}

const std::vector<std::shared_ptr<Symbol>>& Grammar::getTerminals() const
{
	return _terminals;
}

const std::vector<std::shared_ptr<Symbol>>& Grammar::getNonTerminals() const
{
	return _nonTerminals;
}

const std::vector<std::shared_ptr<Rule>>& Grammar::getRules() const
{
	return _rules;
}

const std::shared_ptr<Symbol>& Grammar::getSymbol(const std::string& name) const
{
	for (auto& s : _terminals) { if (s->getName() == name) return s; }
	for (auto& s : _nonTerminals) { if (s->getName() == name) return s; }

	throw std::invalid_argument{ "No symbol with specified name." };
}

void Grammar::removeRecursion()
{
	std::vector<std::shared_ptr<Symbol>> symbols;

	for (auto i = _nonTerminals.begin(); i != _nonTerminals.end(); i++)
	{
		_unfoldRules(i);
		symbols.push_back(_removeDirectRecursion(i));
	}

	_nonTerminals.insert(_nonTerminals.end(), symbols.begin(), symbols.end());
}

void Grammar::removeEpsilon()
{
}

void Grammar::_unfoldRules(const std::vector<std::shared_ptr<Symbol>>::iterator& i)
{
	for (auto j = _nonTerminals.begin(); j != i; j++)
	{
		std::vector<std::shared_ptr<Rule>> ijRules;
		std::vector<std::shared_ptr<Rule>> jRules;

		_findIjRules(i, j, ijRules);
		_findIndexedRules(j, jRules);

		std::erase_if(_rules, [&](auto r) {
			return std::find(ijRules.begin(), ijRules.end(), r) != ijRules.end(); });

		for (auto& ijRule : ijRules)
		{
			for (auto& jRule : jRules)
			{
				std::vector<std::shared_ptr<Symbol>> right{ jRule->getRight() };
				right.insert(right.begin(), jRule->getRight().begin(), jRule->getRight().end());
				right.insert(right.end(), ++(ijRule->getRight().begin()), ijRule->getRight().end());
				_rules.push_back(std::shared_ptr<Rule>{ new Rule{ ijRule->getLeft(), right } });
			}
		}
	}
}

std::shared_ptr<Symbol> Grammar::_removeDirectRecursion(
	const std::vector<std::shared_ptr<Symbol>>::iterator& i)
{
	std::vector<std::shared_ptr<Rule>> recRules;
	std::vector<std::shared_ptr<Rule>> indRules;
	// Ищем все Ai-правила
	_findRecursiveRules(i, recRules);
	_findIndexedRules(i, indRules);
	// Удаляем правила вида Ai -> Ai a
	std::erase_if(_rules, [&](auto r) {
		return std::find(recRules.begin(), recRules.end(), r) != recRules.end(); });
	// Добавляем новый нетерминал Аi'
	std::shared_ptr<Symbol> symbol{ new Symbol{
		(*i)->getName() + "'", (*i)->getSpell(), (*i)->getType()} };
	// Добавляем правила вида Ai -> b Ai'
	for (auto& rule : indRules)
	{
		std::vector<std::shared_ptr<Symbol>> right{ rule->getRight() };
		right.push_back(symbol);
		_rules.push_back(std::shared_ptr<Rule>{ new Rule{ rule->getLeft(), right } });
	}
	// Добавляем правила вида Ai' -> a | a Ai'
	for (auto& rule : recRules)
	{
		std::vector<std::shared_ptr<Symbol>> right{};
		right.insert(right.begin(), ++(rule->getRight().begin()), rule->getRight().end());
		_rules.push_back(std::shared_ptr<Rule>{ new Rule{ { symbol }, right } });
		right.push_back(symbol);
		_rules.push_back(std::shared_ptr<Rule>{ new Rule{ { symbol }, right } });
	}

	return symbol;
}

void Grammar::_findRecursiveRules(
	const std::vector<std::shared_ptr<Symbol>>::iterator& it, 
	std::vector<std::shared_ptr<Rule>>& rules)
{
	std::copy_if(_rules.begin(), _rules.end(),
		std::back_inserter(rules), [&](auto rule)
		{
			return (rule->getRight().empty())
				? false
				: rule->getLeft()[0] == *it && rule->getRight()[0] == *it;
		});
}

void Grammar::_findIndexedRules(
	const std::vector<std::shared_ptr<Symbol>>::iterator& it, 
	std::vector<std::shared_ptr<Rule>>& rules)
{
	std::copy_if(_rules.begin(), _rules.end(), std::back_inserter(rules), 
		[&](auto rule)
		{
			if (rule->getRight().empty() || rule->getLeft()[0] != *it) return false;
			auto s = std::find(_nonTerminals.begin(), 
				_nonTerminals.end(), rule->getRight()[0]);
			return s == _nonTerminals.end() || s > it;
		});
}

void Grammar::_findIjRules(
	const std::vector<std::shared_ptr<Symbol>>::iterator& i, 
	const std::vector<std::shared_ptr<Symbol>>::iterator& j, 
	std::vector<std::shared_ptr<Rule>>& rules)
{
	std::copy_if(_rules.begin(), _rules.end(), std::back_inserter(rules), 
		[&](auto rule)
		{
			return (rule->getRight().empty()) 
				? false 
				: rule->getLeft()[0] == *i && rule->getRight()[0] == *j;
		});
}


