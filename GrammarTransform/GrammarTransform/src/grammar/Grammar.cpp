#include "../../include/grammar/grammar.h"
#include "../../include/grammar_transform/grammar_transform.h"
#include "../../include/grammar_transform/left_recursion_remove.h"
#include "../../include/grammar_transform/epsilon_rule_remove.h"

Grammar::Grammar()
{
	algorithms["leftRecursionRemove"] = transform_ptr{ 
		(GrammarTransform*) new LeftRecursionRemove{ *this } };
	algorithms["epsilonRuleRemove"] = transform_ptr{
		(GrammarTransform*) new EpsilonRuleRemove{ *this } };
}

const symbol_ptr& Grammar::getSymbol(const std::string& name) const
{
	for (auto& s : terminals) { if (s->getName() == name) return s; }
	for (auto& s : nonTerminals) { if (s->getName() == name) return s; }

	throw std::invalid_argument{ "No symbol with specified name." };
}


