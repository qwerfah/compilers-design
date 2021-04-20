#pragma once

#include <map>

enum class SymbolType
{
	Terminal = 0,
	NonTerminal = 1,
	Eps = 2
};

template <class TEnum = SymbolType>
class Convertor
{
public:
	std::map<TEnum, std::string> map;

	std::string convert(TEnum value)
	{
		return map[value];
	}

protected:
	Convertor(std::map<TEnum, std::string> map)
	{
		this->map = map;
	}
};

class SymbolTypeToString: public Convertor<SymbolType>
{
public: 
	SymbolTypeToString() : Convertor<SymbolType>(
	{ 
		{SymbolType::Terminal, "term"}, 
		{SymbolType::NonTerminal, "nonterm"},
		{SymbolType::Eps, "eps"}
	}) {}
};