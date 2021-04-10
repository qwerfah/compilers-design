#pragma once

#include <algorithm>
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
	const symbol_ptr& getSymbol(const std::string& name) const;

	/// <summary>
	/// Terminal symbols (occur in the output).
	/// </summary>
	symbol_vector terminals{};

	/// <summary>
	/// Nonterminal symbols (occur in left part of grammar rule).
	/// </summary>
	symbol_vector nonTerminals{};

	/// <summary>
	/// Start symbol of grammar.
	/// </summary>
	symbol_ptr axiom{};

	/// <summary>
	/// Set of withdrawal rules.
	/// </summary>
	std::vector<std::shared_ptr<Rule>> rules{};

	/// <summary>
	/// Thramsform algorithms.
	/// </summary>
	transform_map algorithms{};
};

