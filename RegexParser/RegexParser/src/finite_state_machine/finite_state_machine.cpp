#include "../../include/finite_state_machine/finite_state_machine.h"
#include <stdexcept>

FiniteStateMachine::FiniteStateMachine() :
	_initState(nullptr),
	_finalState(nullptr),
	_currentState(nullptr),
	_arcs(std::set<std::shared_ptr<Arc>>()),
	_states(std::set<std::shared_ptr<State>>())
{
	_engine = std::mt19937(std::random_device()());
	_isInFinalState = false;
}

void FiniteStateMachine::setInitState(const std::shared_ptr<State>& state)
{
	if (state == nullptr)
	{
		throw std::invalid_argument("State ptr is null.");
	}

	_states.insert(state);
	_initState = state;
}

void FiniteStateMachine::setFinalState(const std::shared_ptr<State>& state)
{
	if (state == nullptr)
	{
		throw std::invalid_argument("State ptr is null.");
	}

	_states.insert(state);
	_finalState = state;
}

void FiniteStateMachine::addState(const std::shared_ptr<State>& state)
{
	if (state == nullptr)
	{
		throw std::invalid_argument("State ptr is null.");
	}

	_states.insert(state);
}

void FiniteStateMachine::addArc(const std::shared_ptr<Arc>& arc)
{
	if (arc == nullptr)
	{
		throw std::invalid_argument("Arc ptr is null.");
	}

	_arcs.insert(arc);
	_states.insert({ arc->getInitialState() , arc->getIFinalState() });
}

bool FiniteStateMachine::match(const std::string& expr)
{
	if (!_finalState || !_initState || _states.empty() || _arcs.empty())
	{
		throw std::invalid_argument("Invalid finite-state machine configuration.");
	}

	std::string copy = expr.substr();
	_currentState = _initState;

	while (!_isInFinalState)
	{
		char mark = next();
		if (mark == copy[0] || mark == 0)
		{
			copy = copy.substr(1);
		}
	}

	return copy.empty();
}

char FiniteStateMachine::next()
{
	if (_isInFinalState) return -1;

	if (!_finalState || !_initState || _states.empty() || _arcs.empty())
	{
		throw std::invalid_argument("Invalid finite-state machine configuration.");
	}

	if (_currentState == _finalState)
	{
		_isInFinalState = true;
		return -1;
	}

	auto arcs = std::vector<std::shared_ptr<Arc>>();

	for (auto& arc : _arcs)
	{
		if (arc->getInitialState() == _currentState)
		{
			arcs.push_back(arc);
		}
	}

	switch (arcs.size())
	{
	case 0:
		_isInFinalState = true;
		return -1;
	case 1:
		_currentState = arcs[0]->getIFinalState();
		return arcs[0]->getMark();
	default:
		std::uniform_int_distribution<int> distribution(0, arcs.size());
		std::shared_ptr<Arc> arc = arcs[distribution(_engine)];
		_currentState = arc->getIFinalState();
		return arc->getMark();
	}
}

bool FiniteStateMachine::isInFinalState() const
{
	return _isInFinalState;
}
