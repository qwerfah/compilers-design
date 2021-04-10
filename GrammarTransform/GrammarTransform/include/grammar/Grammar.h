#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <iterator>

#include "symbol.h"
#include "rule.h"

class GrammarTransform;

/// <summary>
/// Regular grammar.
/// </summary>
class Grammar
{
public:
	Grammar();

	/// <summary>
	/// Get symbol from grammar alphabet by its name.
	/// </summary>
	/// <param name="name"> Name of the symbol. </param>
	/// <returns> Symbol with specified name. </returns>
	const std::shared_ptr<Symbol>& getSymbol(const std::string& name) const;

	/// <summary>
	/// Terminal symbols (occur in the output).
	/// </summary>
	std::vector<std::shared_ptr<Symbol>> terminals{};

	/// <summary>
	/// Nonterminal symbols (occur in left part of grammar rule).
	/// </summary>
	std::vector<std::shared_ptr<Symbol>> nonTerminals{};

	/// <summary>
	/// Start symbol of grammar.
	/// </summary>
	std::shared_ptr<Symbol> axiom{};

	/// <summary>
	/// Set of withdrawal rules.
	/// </summary>
	std::vector<std::shared_ptr<Rule>> rules{};

	/// <summary>
	/// Thramsform algorithms.
	/// </summary>
	std::map<std::string, std::shared_ptr<GrammarTransform>> algorithms{};
};

