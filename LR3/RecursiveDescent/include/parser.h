#pragma once

#include "grammar/grammar.h"

class Parser
{
public:
	Parser() noexcept = default;
	Parser(const grammar_ptr& grammar);

private:
	grammar_ptr _grammar = nullptr;
};

