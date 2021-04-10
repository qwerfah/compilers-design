#pragma once

#include "../grammar/grammar.h"

/// <summary>
/// Base class for any grammar transfoirm algorithm.
/// </summary>
class GrammarTransform
{
public:
	GrammarTransform(Grammar& grammar);

	/// <summary>
	/// Transform algorithm implementation incapsulated in parenthesis operator.
	/// </summary>
	virtual void operator()() = 0;

protected:
	/// <summary>
	/// Grammar transform algirithm will be applied to.
	/// </summary>
	Grammar& _grammar;
};

