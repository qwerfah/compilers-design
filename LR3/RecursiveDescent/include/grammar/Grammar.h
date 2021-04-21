#pragma once

#include <algorithm>
#include <iterator>

#include "symbol.h"
#include "rule.h"

/// <summary>
/// Regular grammar.
/// </summary>
class Grammar
{
public:
	Grammar() noexcept = default;

	Grammar(
		const symbol_vector& nonTerms, 
		const symbol_vector& terms, 
		const symbol_ptr& start, 
		const rule_vector& prods);

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
	rule_vector rules{};
};

