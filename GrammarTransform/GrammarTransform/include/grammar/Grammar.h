#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <iterator>

#include "Symbol.h"
#include "Rule.h"

class Grammar
{
public:
	Grammar() = default;

	Grammar(Grammar&& grammar);

	void setAxiom(const std::shared_ptr<Symbol>& symbol);
	void addTerminal(const std::shared_ptr<Symbol>& symbol);
	void addNonTerminal(const std::shared_ptr<Symbol>& symbol);
	void addRule(const std::shared_ptr<Rule>& rule);

	const std::shared_ptr<Symbol>& getAxiom() const;
	const std::vector<std::shared_ptr<Symbol>>& getTerminals() const;
	const std::vector<std::shared_ptr<Symbol>>& getNonTerminals() const;
	const std::vector<std::shared_ptr<Rule>>& getRules() const;

	const std::shared_ptr<Symbol>& getSymbol(const std::string& name) const;

	void removeRecursion();
	void removeEpsilon();
	
private:
	std::vector<std::shared_ptr<Symbol>> _terminals{};
	std::vector<std::shared_ptr<Symbol>> _nonTerminals{};
	std::shared_ptr<Symbol> _axiom{};
	std::vector<std::shared_ptr<Rule>> _rules{};

	void _unfoldRules(const std::vector<std::shared_ptr<Symbol>>::iterator& i);
	std::shared_ptr<Symbol> _removeDirectRecursion(
		const std::vector<std::shared_ptr<Symbol>>::iterator& i);

	void _findRecursiveRules(
		const std::vector<std::shared_ptr<Symbol>>::iterator& it,
		std::vector<std::shared_ptr<Rule>>& rules);

	void _findIndexedRules(
		const std::vector<std::shared_ptr<Symbol>>::iterator& it,
		std::vector<std::shared_ptr<Rule>>& rules);

	void _findIjRules(
		const std::vector<std::shared_ptr<Symbol>>::iterator& i,
		const std::vector<std::shared_ptr<Symbol>>::iterator& j,
		std::vector<std::shared_ptr<Rule>>& rules);
};

