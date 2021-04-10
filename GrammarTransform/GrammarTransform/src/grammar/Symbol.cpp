#include "../../include/grammar/symbol.h"

Symbol::Symbol(const std::string& name, const std::string& spell, SymbolType type)
	: _name{ name }, _spell{ spell }, _type{ type }
{
}

Symbol::Symbol(const Symbol& symbol)
{
	_name = symbol._name;
	_spell = symbol._spell;
	_type = symbol._type;
}

Symbol::Symbol(Symbol&& symbol)
{
	_name = std::move(symbol._name);
	_spell = std::move(symbol._spell);
	_type = std::move(symbol._type);
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

bool operator < (const Symbol& left, const Symbol& right)
{
	return left._name < right._name;
}


