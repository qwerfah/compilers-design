#include "../../include/grammar/grammar.h"


Grammar::Grammar(
	const symbol_vector& nonTerms, 
	const symbol_vector& terms, 
	const symbol_ptr& start, 
	const rule_vector& prods) : Grammar()
{
	if (!start)
	{
		throw std::invalid_argument{ "Null axiom." };
	}

	if (std::any_of(nonTerms.begin(), nonTerms.end(), [&](auto s) { return !s; }))
	{
		throw std::invalid_argument{ "Null symbol in nonterminals." };
	}

	if (std::any_of(terms.begin(), terms.end(), [&](auto s) { return !s; }))
	{
		throw std::invalid_argument{ "Null symbol in terminals." };
	}

	if (std::any_of(prods.begin(), prods.end(), [&](auto p) { return !p; }))
	{
		throw std::invalid_argument{ "Null rule in prods." };
	}

	nonTerminals = nonTerms;
	terminals = terms;
	axiom = start;
	rules = prods;
}

const symbol_ptr& Grammar::getSymbol(const std::string& name) const
{
	for (auto& s : terminals) { if (s->getName() == name) return s; }
	for (auto& s : nonTerminals) { if (s->getName() == name) return s; }

	throw std::invalid_argument{ "No symbol with specified name." };
}


