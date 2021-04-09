#include "../../include/grammar/Symbol.h"

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

Symbol& Symbol::operator = (Symbol&& symbol)
{
	if (this == &symbol) 
	{
		return *this;
	}

	_name = std::move(symbol._name);
	_spell = std::move(symbol._spell);
	_type = std::move(symbol._type);

	return *this;
}

Symbol& Symbol::operator=(const Symbol& symbol)
{
	if (this == &symbol)
	{
		return *this;
	}

	_name = symbol._name;
	_spell = symbol._spell;
	_type = symbol._type;

	return *this;
}

bool operator < (const Symbol& left, const Symbol& right)
{
	return left._name < right._name;
}


