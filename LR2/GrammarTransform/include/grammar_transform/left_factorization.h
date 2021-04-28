#pragma once

#include "grammar_transform.h"

class LeftFactorization : GrammarTransform
{
public:
	LeftFactorization(Grammar& grammar);

	/// <summary>
	/// Left factorization algorithm implementation.
	/// </summary>
	virtual void operator()() override;
};

