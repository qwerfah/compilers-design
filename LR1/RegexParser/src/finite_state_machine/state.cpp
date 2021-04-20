#include "../../include/finite_state_machine/state.h"

unsigned State::_globalId = 0;

State::State() : _stateId(_globalId++)
{ }

unsigned State::getId() const
{
	return _stateId;
}

bool State::operator == (const State& state) const
{
	return this->_stateId == state._stateId;
}

bool State::operator < (const State& state) const
{
	return this->_stateId < state._stateId;
}

State& State::operator = (const State& state)
{
	if (this != &state)
	{
		_stateId = state._stateId;
	}

	return *this;
}

void State::addInnerState(const std::shared_ptr<State>& state)
{
	if (!state)
	{
		throw std::invalid_argument("Null state pointer.");
	}

	_innerStates.insert(state);
}

void State::addInnerState(const std::set<std::shared_ptr<State>>& states)
{
	if (std::any_of(states.begin(), states.end(), [&](auto v) { return !v; }))
	{
		throw std::invalid_argument("One of inner states is null pointer.");
	}

	_innerStates.insert(states.begin(), states.end());
}

const std::set<std::shared_ptr<State>>& State::getInnerStates() const
{
	return _innerStates;
}

void State::clearInnerStates()
{
	_innerStates.clear();
}


