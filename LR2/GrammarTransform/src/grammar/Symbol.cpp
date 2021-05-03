#include "../../include/grammar/symbol.h"

Symbol::Symbol(
	const std::string& name, 
	const std::string& spell, 
	SymbolType type,
	const std::shared_ptr<uint8_t>& c
)
	: _name{ name }, _spell{ spell }, _type{ type }, count{ c }
{
	if (!count)
	{
		count = std::shared_ptr<uint8_t>{ new uint8_t };
		*count = 0;
	}
}

Symbol::Symbol(const Symbol& symbol)
{
	_name  = symbol._name;
	_spell = symbol._spell;
	_type  = symbol._type;
	count  = count;
}

Symbol::Symbol(Symbol&& symbol)
{
	_name  = std::move(symbol._name);
	_spell = std::move(symbol._spell);
	_type  = std::move(symbol._type);
	count  = std::move(symbol.count);
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


