#include "..\..\include\grammar_transform\epsilon_rule_remove.h"

EpsilonRuleRemove::EpsilonRuleRemove(Grammar& grammar)
	: GrammarTransform{ grammar }
{
}

void EpsilonRuleRemove::operator()()
{
}
