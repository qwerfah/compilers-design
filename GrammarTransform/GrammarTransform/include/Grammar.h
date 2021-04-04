#pragma once

#include <set>

#include "Symbol.h"
#include "Rule.h"

class Grammar
{
public:
	Grammar() = default;
	
private:
	std::set<Symbol> _terminals;
	std::set<Symbol> _nonTerminals;
	Symbol _axiom;
	std::set<Rule> _rules;
};

