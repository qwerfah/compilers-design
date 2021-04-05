#include "../../include/grammar/Symbol.h"

Symbol::Symbol(const std::string& name, const std::string& spell, SymbolType type)
	: _name{ name }, _spell{ spell }, _type{ type }
{
}

const std::string& Symbol::getName() const
{
	return _name;
}

const std::string& Symbol::getSpell() const
{
	return _spell;
}

SymbolType Symbol::getType() const
{
	return _type;
}
