#include "../../include/finite_state_machine/arc.h"
#include "../../include/finite_state_machine/finite_state_machine.h"

Arc::Arc(const std::shared_ptr<State>& initialState, 
         const std::shared_ptr<State>& finalState,
         ArcType type, char mark) :
    _type(type),
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
         const std::shared_ptr<State>& finalState,
         ArcType type, char mark) :
    _type(type),
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
         const std::shared_ptr<FiniteStateMachine>& machine,
         ArcType type, char mark) :
    _type(type),
    _mark(mark)
{
    if (!initialState || !machine->getInitState())
    {
        throw std::invalid_argument("State ptr is null.");
    }

    _initialState = initialState;
    _finalState = machine->getInitState();
}

Arc::Arc(const std::shared_ptr<FiniteStateMachine>& initMachine,
         const std::shared_ptr<FiniteStateMachine>& finalMachine,
         ArcType type, char mark) :
    _type(type),
    _mark(mark)
{
    if (!initMachine->getFinalState() || !finalMachine->getInitState())
    {
        throw std::invalid_argument("State ptr is null.");
    }

    _initialState = initMachine->getFinalState();
    _finalState = finalMachine->getInitState();
}

const std::shared_ptr<State>& Arc::getInitialState() const
{
    return _initialState;
}

const std::shared_ptr<State>& Arc::getFinalState() const
{
    return _finalState;
}

char Arc::getMark() const
{
    return _mark;
}

ArcType Arc::getType() const
{
    return _type;
}

bool Arc::operator < (const Arc& arc) const
{
    return this->_initialState < arc._initialState;
}
