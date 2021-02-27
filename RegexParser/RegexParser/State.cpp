#include "State.h"

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


