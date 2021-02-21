#include "Arc.h"

Arc::Arc(const State& initialState, const State& finalState, char mark)
    : _initialState(initialState), _finalState(finalState), _mark(mark)
{ }

const State& Arc::getInitialState() const
{
    return _initialState;
}

const State& Arc::getIFinalState() const
{
    return _finalState;
}

char Arc::getMark() const
{
    return _mark;
}
