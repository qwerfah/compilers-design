#pragma once

#include <vector>

#include "Symbol.h"
#include "Rule.h"

class Grammar
{
public:
	Grammar() = default;

	void setAxiom(const Symbol& symbol);
	void addTerminal(const Symbol& symbol);
	void addNonTerminal(const Symbol& symbol);
	void addRule(const Rule& rule);

	const Symbol& getAxiom() const;
	const std::vector<Symbol>& getTerminals() const;
	const std::vector<Symbol>& getNonTerminals() const;
	const std::vector<Rule>& getRules() const;
	
private:
	std::vector<Symbol> _terminals{};
	std::vector<Symbol> _nonTerminals{};
	Symbol _axiom{};
	std::vector<Rule> _rules{};
};

