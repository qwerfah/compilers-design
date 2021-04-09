#include "../../include/grammar/grammar.h"
#include "../../include/grammar_transform/grammar_transform.h"

Grammar::Grammar(
	const std::shared_ptr<GrammarTransform>& removeRec, 
	const std::shared_ptr<GrammarTransform>& removeEps)
	: removeLeftRecursion{ removeRec }, removeEpsilon{ removeEps }
{
}

const std::shared_ptr<Symbol>& Grammar::getSymbol(const std::string& name) const
{
	for (auto& s : terminals) { if (s->getName() == name) return s; }
	for (auto& s : nonTerminals) { if (s->getName() == name) return s; }

	throw std::invalid_argument{ "No symbol with specified name." };
}


