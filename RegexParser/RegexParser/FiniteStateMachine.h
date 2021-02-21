#pragma once

#include "State.h"
#include "Arc.h"
#include <set>

class FiniteStateMachine
{
public:
	FiniteStateMachine();
	FiniteStateMachine(const std::set<State>& states,
					   const std::set<State>& finalStates,
					   const State& currentState,
					   const std::set<Arc>& arcs);

	void addState(const State& state);
	void addFinalState(const State& state);
	void addArc(const Arc& arc);

	void next();


private:
	const State& _currentState;
	std::set<State> _states;
	std::set<State> _finalStates;
	std::set<Arc> _arcs;
};

