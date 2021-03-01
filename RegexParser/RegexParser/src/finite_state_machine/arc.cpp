#include "../../include/finite_state_machine/arc.h"
#include "../../include/finite_state_machine/finite_state_machine.h"

Arc::Arc(const std::shared_ptr<State>& initialState, 
         const std::shared_ptr<State>& finalState, char mark) :
    _mark(mark)
{
    if (!initialState || !finalState)
    {
        throw std::invalid_argument("State ptr is null.");
    }

    _initialState = initialState;
    _finalState = finalState;
}

Arc::Arc(const std::shared_ptr<FiniteStateMachine>& machine,
         const std::shared_ptr<State>& finalState, char mark) :
    _mark(mark)
{
    if (!machine->getFinalState() || !finalState)
    {
        throw std::invalid_argument("State ptr is null.");
    }

    _initialState = machine->getFinalState();
    _finalState = finalState;
}

Arc::Arc(const std::shared_ptr<State>& initialState,
         const std::shared_ptr<FiniteStateMachine>& machine, char mark) :
    _mark(mark)
{
    if (!initialState || !machine->getInitState())
    {
        throw std::invalid_argument("State ptr is null.");
    }

    _initialState = initialState;
    _finalState = machine->getInitState();
}

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
