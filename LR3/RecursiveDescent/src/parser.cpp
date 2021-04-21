#include "../include/parser.h"

Parser::Parser(const grammar_ptr& grammar) : Parser()
{
	if (!grammar)
	{
		throw std::invalid_argument{ "Null grammar pointer." };
	}

	_grammar = grammar;
}
