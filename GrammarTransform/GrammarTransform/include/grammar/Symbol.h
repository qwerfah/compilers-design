#pragma once

#include <string>

#include "../enums.h"

class Symbol
{
public:
	Symbol(const std::string& name = "", const std::string& spell = "", SymbolType type = SymbolType::NonTerminal);
	Symbol(const Symbol& symbol);
	Symbol(Symbol&& symbol);

	const std::string& getName() const;

	const std::string& getSpell() const;

	SymbolType getType() const;

	friend bool operator < (const Symbol& left, const Symbol& right);

	Symbol& operator = (Symbol&& symbol);
	Symbol& operator = (const Symbol& symbol);

private:
	std::string _name{};
	std::string _spell{};
	SymbolType _type{};
};

