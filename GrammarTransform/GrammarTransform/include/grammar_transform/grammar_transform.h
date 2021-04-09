#pragma once

#include "../grammar/grammar.h"

class GrammarTransform
{
public:
	GrammarTransform(Grammar& grammar);
	virtual void operator()() = 0;

protected:
	Grammar& _grammar;
};

