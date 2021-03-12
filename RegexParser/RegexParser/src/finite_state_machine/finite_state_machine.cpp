#include "../../include/finite_state_machine/finite_state_machine.h"

FiniteStateMachine::FiniteStateMachine() :
	_initState(nullptr),
	_currentState(nullptr),
	_finalStates(std::set<std::shared_ptr<State>>()),
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

void FiniteStateMachine::addState(const std::shared_ptr<State>& state)
{
	if (state == nullptr)
	{
		throw std::invalid_argument("State ptr is null.");
	}

	_states.insert(state);
}


void FiniteStateMachine::addFinalState(const std::shared_ptr<State>& state)
{
	if (state == nullptr)
	{
		throw std::invalid_argument("State ptr is null.");
	}

	_states.insert(state);
	_finalStates.insert(state);
}

void FiniteStateMachine::addFinalState(const std::set<std::shared_ptr<State>>& states)
{
	_states.insert(states.begin(), states.end());
	_finalStates.insert(states.begin(), states.end());
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
	_states.insert({ arc->getInitialState() , arc->getFinalState() });
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
	if (!_initState || _states.empty() || _finalStates.empty() || _arcs.empty())
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

	if (!_initState || _states.empty() || _finalStates.empty() || _arcs.empty())
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
		_currentState = arcs[0]->getFinalState();
		_isInFinalState = _finalStates.find(_currentState) != _finalStates.end();
		return arcs[0]->getMark() == '.' || arcs[0]->getMark() == ch;
	default:
		std::uniform_int_distribution<int> distribution(0, arcs.size());
		std::shared_ptr<Arc> arc = arcs[distribution(_engine)];
		_currentState = arc->getFinalState();
		_isInFinalState = _finalStates.find(_currentState) != _finalStates.end();
		return arc->getMark() == '.' || arc->getMark() == ch;
	}
}



void FiniteStateMachine::determine()
{
	_removeLambda();
	_determine();
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

const std::set<std::shared_ptr<State>>& FiniteStateMachine::getFinalStates() const
{
	return _finalStates;
}

const std::shared_ptr<State>& FiniteStateMachine::getCurrentState() const
{
	return _currentState;
}

void FiniteStateMachine::_removeLambda()
{
	std::vector<std::shared_ptr<State>> states;

	for (auto state : _states)
	{
		if (state != _initState)
		{
			std::set<std::shared_ptr<Arc>> inArcs;  // Входящие дуги с лямбда-переходами
			std::set<std::shared_ptr<Arc>> outArcs; // Все исходящие дуги
			bool isLambda = true;

			for (auto arc : _arcs)
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
			
			// Если текущее состояние не является конечным, заменяем лямбда-переходы
			if (_finalStates.find(state) == _finalStates.end())
			{
				for (auto inArc : inArcs)
				{
					for (auto outArc : outArcs)
					{
						_arcs.insert(std::shared_ptr<Arc>(new Arc(
							inArc->getInitialState(),
							outArc->getFinalState(),
							outArc->getType(),
							outArc->getMark())));
					}
				}
			}
			// Иначе делаем все состояния, из которых есть лямбда-переходы в текущее, конечными
			else
			{
				if (!outArcs.empty())
				{
					throw std::invalid_argument("Final state can't have outgoing arcs.");
				}

				for (auto inArc : inArcs) { _finalStates.insert(inArc->getInitialState()); }
			}

			// Удаляем все входящие лямбда-переходы
			std::erase_if(_arcs, [&](auto el) { return inArcs.find(el) != inArcs.end(); });

			// Если в текущее состояние есть только лямбда-переходы, 
			// добавляем его для удаления и удаляем все исходящие дуги
			if (isLambda)
			{
				states.push_back(state);
				std::erase_if(_arcs, [&](auto el) { return outArcs.find(el) != outArcs.end(); });
			}
		}
	}

	for (auto state : states)
	{
		_states.erase(state);
	}
}

void FiniteStateMachine::_determine()
{
}
