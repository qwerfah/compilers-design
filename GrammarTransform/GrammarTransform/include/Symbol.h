#pragma once

#include <string>

#include "enums.h"

class Symbol
{
public:
	Symbol(const std::string& name, const std::string spell, SymbolType type);

	const std::string& getName() const;

	const std::string& getSpell() const;

	SymbolType getType() const;

private:
	std::string _name;
	std::string _spell;
	SymbolType _type;
};

