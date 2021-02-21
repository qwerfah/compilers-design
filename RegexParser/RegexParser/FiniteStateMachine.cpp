#include "FiniteStateMachine.h"
#include <stdexcept>

FiniteStateMachine::FiniteStateMachine()
	: _states(std::set<State>()), _finalStates(std::set<State>()), _currentState(State()), _arcs(std::set<Arc>())
{ }

FiniteStateMachine::FiniteStateMachine(const std::set<State>& states,
									   const std::set<State>& finalStates,
									   const State& currentState,
									   const std::set<Arc>& arcs)
	: _states(states), _finalStates(finalStates), _currentState(currentState), _arcs(arcs)
{ }

void FiniteStateMachine::addState(const State& state)
{
	_states.insert(state);
}

void FiniteStateMachine::addFinalState(const State& state)
{
	_states.insert(state);
	_finalStates.insert(state);
}

void FiniteStateMachine::addArc(const Arc& arc)
{
	_arcs.insert(arc);
}

void FiniteStateMachine::next()
{
	if (_states.empty() || _finalStates.empty() || _arcs.empty())
	{
		throw std::invalid_argument("None of the sets can be empty");
	}

	for (auto& arc : _arcs)
	{
		if (arc.getInitialState() == _currentState)
		{

		}
	}
}
