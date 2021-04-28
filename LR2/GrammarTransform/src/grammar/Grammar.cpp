#include "../../include/grammar/grammar.h"
#include "../../include/grammar_transform/grammar_transform.h"
#include "../../include/grammar_transform/left_recursion_remove.h"
#include "../../include/grammar_transform/epsilon_rule_remove.h"
#include "../../include/grammar_transform/left_factorization.h"

Grammar::Grammar()
{
	algorithms["recursion"] = transform_ptr{ 
		(GrammarTransform*) new LeftRecursionRemove{ *this } };
	algorithms["epsilon"] = transform_ptr{
		(GrammarTransform*) new EpsilonRuleRemove{ *this } };
	algorithms["fact"] = transform_ptr{
		(GrammarTransform*) new LeftFactorization{ *this } };
}

const symbol_ptr& Grammar::getSymbol(const std::string& name) const
{
	for (auto& s : terminals) { if (s->getName() == name) return s; }
	for (auto& s : nonTerminals) { if (s->getName() == name) return s; }

	throw std::invalid_argument{ "No symbol with specified name." };
}


