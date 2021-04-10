#pragma once

#include "grammar_transform.h"

class EpsilonRuleRemove : GrammarTransform
{
public:
	EpsilonRuleRemove(Grammar& grammar);

	virtual void operator()() override;
};

