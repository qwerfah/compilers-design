#pragma once

#include "State.h"

class Arc
{
public:
	Arc(const State& initialState, const State& finalState, char mark);

	const State& getInitialState() const;
	const State& getIFinalState() const;
	char getMark() const;

private:
	const State& _initialState;
	const State& _finalState;
	const char _mark;
};

