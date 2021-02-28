#include "../../include/finite_state_machine/arc.h"

Arc::Arc(const std::shared_ptr<State>& initialState, const std::shared_ptr<State>& finalState, char mark) :
    _initialState(initialState), _finalState(finalState), _mark(mark)
{ }

const std::shared_ptr<State>& Arc::getInitialState() const
{
    return _initialState;
}

const std::shared_ptr<State>& Arc::getIFinalState() const
{
    return _finalState;
}

char Arc::getMark() const
{
    return _mark;
}

bool Arc::operator < (const Arc& arc) const
{
    return this->_initialState < arc._initialState;
}
