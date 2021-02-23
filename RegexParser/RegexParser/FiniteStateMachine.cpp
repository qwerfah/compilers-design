#include "FiniteStateMachine.h"
#include <stdexcept>

FiniteStateMachine::FiniteStateMachine() :
	_states(std::set<State>()), 
	_finalStates(std::set<State>()),
	_currentState(nullptr), 
	_arcs(std::set<Arc>())
{ 
	_engine = std::mt19937(std::random_device()());
	_isInFinalState = false;
}

FiniteStateMachine::FiniteStateMachine(const std::set<State>& states,
									   const std::set<State>& finalStates,
									   const State& currentState,
									   const std::set<Arc>& arcs) : 
	_states(states), 
	_finalStates(finalStates), 
	_currentState(std::unique_ptr<const State>(&currentState)), 
	_arcs(arcs)
{
	_engine = std::mt19937(std::random_device()());
	_isInFinalState = false;
}

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
	_states.insert({ arc.getInitialState() , arc.getIFinalState() });
}

void FiniteStateMachine::next()
{
	if (_isInFinalState) return;

	if (_states.empty() || _finalStates.empty() || _arcs.empty())
	{
		throw std::invalid_argument("None of the sets can be empty");
	}

	if (_finalStates.find(*_currentState) != _finalStates.end())
	{
		_isInFinalState = true;
		return;
	}

	auto nextStates = std::vector<State>();

	for (auto& arc : _arcs)
	{
		if (arc.getInitialState() == *_currentState)
		{
			nextStates.push_back(arc.getIFinalState());
		}
	}

	switch (nextStates.size())
	{
	case 0:
		_isInFinalState = true;
	case 1:
		_currentState = std::unique_ptr<const State>(&nextStates[0]);
	default:
		std::uniform_int_distribution<int> distribution(0, nextStates.size());
		_currentState = std::unique_ptr<const State>(&nextStates[distribution(_engine)]);
		break;
	}
}

bool FiniteStateMachine::isInFinalState() const
{
	return _isInFinalState;
}
