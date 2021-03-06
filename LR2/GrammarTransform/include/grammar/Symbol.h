#pragma once

#include <string>
#include <memory>

#include "../enums.h"

/// <summary>
/// Symbol of grammar alphabet.
/// </summary>
class Symbol
{
public:
	Symbol(
		const std::string& name = "", 
		const std::string& spell = "", 
		SymbolType type = SymbolType::NonTerminal, 
		const std::shared_ptr<uint8_t>& c = nullptr
	);
	Symbol(const Symbol& symbol);
	Symbol(Symbol&& symbol);

	/// <summary>
	/// Get name of the symbol.
	/// </summary>
	/// <returns></returns>
	const std::string& getName() const;

	/// <summary>
	/// Get spell of the symbol.
	/// </summary>
	/// <returns></returns>
	const std::string& getSpell() const;

	/// <summary>
	/// Get type of the symbol.
	/// </summary>
	/// <returns></returns>
	SymbolType getType() const;

	friend bool operator < (const Symbol& left, const Symbol& right);

	std::shared_ptr<uint8_t> count = nullptr;

private:
	/// <summary>
	/// Name of the symbol.
	/// </summary>
	std::string _name{};

	/// <summary>
	/// Spell of the symbol.
	/// </summary>
	std::string _spell{};

	/// <summary>
	/// Type of the symbol.
	/// </summary>
	SymbolType _type{};
};

