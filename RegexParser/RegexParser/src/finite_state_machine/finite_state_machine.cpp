#include "../../include/finite_state_machine/finite_state_machine.h"

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

void FiniteStateMachine::addState(const std::initializer_list<
	std::variant<std::shared_ptr<State>, std::shared_ptr<FiniteStateMachine>>>& list)
{
	for (auto elem : list)
	{
		try
		{
			auto state = std::get<std::shared_ptr<State>>(elem);

			if (!state)
			{
				throw std::invalid_argument("Null pointer to state of FSM.");
			}

			_states.insert(state);
		}
		catch (std::exception _)
		{
			auto machine = std::get<std::shared_ptr<FiniteStateMachine>>(elem);

			if (!machine)
			{
				throw std::invalid_argument("Null pointer to state of FSM.");
			}

			_states.insert(machine->_states.begin(), machine->_states.end());
			_arcs.insert(machine->_arcs.begin(), machine->_arcs.end());
		}
	}
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

void FiniteStateMachine::addMachine(const std::shared_ptr<FiniteStateMachine>& machine)
{
	if (machine == nullptr)
	{
		throw std::invalid_argument("Finite-state machine ptr is null.");
	}

	_states.insert(machine->_states.begin(), machine->_states.end());
	_arcs.insert(machine->_arcs.begin(), machine->_arcs.end());
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
		if (copy.empty()) return false;

		if (next(copy[0]))
		{
			copy = copy.substr(1);
		}
	}

	return copy.empty();
}

bool FiniteStateMachine::next(char ch)
{
	if (_isInFinalState) return false;

	if (!_finalState || !_initState || _states.empty() || _arcs.empty())
	{
		throw std::invalid_argument("Invalid finite-state machine configuration.");
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
		return false;
	case 1:
		_currentState = arcs[0]->getIFinalState();
		_isInFinalState = _currentState == _finalState;
		return arcs[0]->getMark() == '.' || arcs[0]->getMark() == ch;
	default:
		std::uniform_int_distribution<int> distribution(0, arcs.size());
		std::shared_ptr<Arc> arc = arcs[distribution(_engine)];
		_currentState = arc->getIFinalState();
		_isInFinalState = _currentState == _finalState;
		return arc->getMark() == '.' || arc->getMark() == ch;
	}
}

void FiniteStateMachine::determine()
{
	std::vector<std::shared_ptr<State>> states;

	for (auto state: _states)
	{
		if (state != _initState && state != _finalState)
		{
			std::vector<std::shared_ptr<Arc>> inArcs;
			std::vector<std::shared_ptr<Arc>> outArcs;
			bool isLambda = true;

			for (auto arc: arcs)
			{
				if (arc->getFinalState() == state)
				{
					inArcs.insert(arc);
					isLambda = arc->getType() == ArcType::Lambda ? isLambda : false;
					
					if (arc->getType() == ArcType::Lambda)
					{
						inArcs.insert(arc);
					}
				}
				else if (arc->getInitialState() == state)
				{
					outArcs.insert(arc);
				}
			}
			
			for (auto inArc: inArcs)
			{
				for (auto outArc: outArcs)
				{
					_arcs.insert(std::shared_ptr<Arc>(new Arc(
						inArc->getInitState(), 
						outArc->getFinalState(), 
						outArc->getType(), 
						outArc->getMark()));
				}
			}

			_arcs.erase(inArcs.begin(), isArcs.end());

			if (isLambda)
			{
				states.insert(state);
				_arcs.erase(outArcs.begin(), outArcs.end());
			}
		}
	}

	for (auto state: states)
	{
		_states.erase(state);	
	}
}

void FiniteStateMachine::minimize()
{
}

bool FiniteStateMachine::isInFinalState() const
{
	return _isInFinalState;
}

const std::shared_ptr<State>& FiniteStateMachine::getInitState() const
{
	return _initState;
}

const std::shared_ptr<State>& FiniteStateMachine::getFinalState() const
{
	return _finalState;
}

const std::shared_ptr<State>& FiniteStateMachine::getCurrentState() const
{
	return _currentState;
}
