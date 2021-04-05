#include "../../include/grammar/Grammar.h"

void Grammar::setAxiom(const Symbol& symbol)
{
	_axiom = symbol;
}

void Grammar::addTerminal(const Symbol& symbol)
{
	_terminals.push_back(symbol);
}

void Grammar::addNonTerminal(const Symbol& symbol)
{
	_nonTerminals.push_back(symbol);
}

void Grammar::addRule(const Rule& rule)
{
	_rules.push_back(rule);
}

const Symbol& Grammar::getAxiom() const
{
	return _axiom;
}

const std::vector<Symbol>& Grammar::getTerminals() const
{
	return _terminals;
}

const std::vector<Symbol>& Grammar::getNonTerminals() const
{
	return _nonTerminals;
}

const std::vector<Rule>& Grammar::getRules() const
{
	return _rules;
}
