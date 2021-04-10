#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <iterator>

#include "symbol.h"
#include "rule.h"

class GrammarTransform;

class Grammar
{
public:
	Grammar();
	const std::shared_ptr<Symbol>& getSymbol(const std::string& name) const;

	std::vector<std::shared_ptr<Symbol>> terminals{};
	std::vector<std::shared_ptr<Symbol>> nonTerminals{};
	std::shared_ptr<Symbol> axiom{};
	std::vector<std::shared_ptr<Rule>> rules{};
	std::map<std::string, std::shared_ptr<GrammarTransform>> algorithms{};
};

