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

FiniteStateMachine& FiniteStateMachine::operator = (FiniteStateMachine&& machine)  
{
	_initState = std::move(machine._initState);
	_finalStates = std::move(machine._finalStates);
	_states = std::move(machine._states);
	_arcs = std::move(machine._arcs);
	_currentState = std::move(machine._currentState);
	_isInFinalState = machine._isInFinalState;

	return *this;
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
	if (std::any_of(states.begin(), states.end(), [&](auto v) { return !v; }))
	{
		throw std::invalid_argument("One of inner states is null pointer.");
	}

	_states.insert(states.begin(), states.end());
	_finalStates.insert(states.begin(), states.end());
}

void FiniteStateMachine::addState(const std::initializer_list<
	std::variant<std::shared_ptr<State>, std::shared_ptr<FiniteStateMachine>>>& list)
{
	for (auto& elem : list)
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

	for ( ; ; )
	{
		TransitionType transition = next(copy[0]);

		switch (transition)
		{
		case TransitionType::Successful: copy = copy.substr(1); break;
		case TransitionType::Impossible: return false;
		default: continue;
		}

		if (copy.empty() && _isInFinalState)
		{
			return true;
		}
	}
}

TransitionType FiniteStateMachine::next(char ch)
{
	if (_isInFinalState) return TransitionType::Impossible;

	if (!_initState || _states.empty() || _finalStates.empty() || _arcs.empty())
	{
		throw std::invalid_argument("Invalid finite-state machine configuration.");
	}

	std::vector<std::shared_ptr<Arc>> arcs;
	std::vector<std::shared_ptr<Arc>> lambdaArcs;
	std::shared_ptr<Arc> arc = nullptr;

	std::copy_if(_arcs.begin(), _arcs.end(), std::back_inserter(arcs), [&](auto arc) { 
		return arc->getInitialState() == _currentState;
	});

	switch (arcs.size())
	{
	case 0:
		throw std::logic_error("FSM is in state without outgoing arcs, but it's not a final state.");
	case 1:
		arc = arcs[0];
		break;
	default:
		auto it = std::find_if(arcs.begin(), arcs.end(), [&](auto v) { return v->getMark() == ch; });
		if (it != arcs.end())
		{
			arc = *it;
		}
		else
		{
			std::copy_if(arcs.begin(), arcs.end(), std::back_inserter(lambdaArcs), [&](auto v) {
				return v->getType() == ArcType::Lambda;
			});
			std::uniform_int_distribution<int> distribution(0, lambdaArcs.size());
			arc = lambdaArcs.empty() ? nullptr : arcs[distribution(_engine)];
		}
	}

	if (arc && (arc->getType() == ArcType::Lambda || arc->getMark() == '.' || arc->getMark() == ch))
	{
		_currentState = arc->getFinalState();
		_isInFinalState = _finalStates.find(_currentState) != _finalStates.end();
		return arc->getType() == ArcType::Lambda 
			? TransitionType::Lambda 
			: TransitionType::Successful;
	}
	
	return TransitionType::Impossible;
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
	auto it = std::find_if(_arcs.begin(), _arcs.end(), [&](auto arc) {
		return arc->getType() == ArcType::Lambda;
	});

	_writeToFile();

	// ”дал€ем все л€мбда-переходы и определ€ем новые конечные состо€ни€
	while  (it != _arcs.end())
	{
		std::set<std::shared_ptr<Arc>> outArcs;

		std::copy_if(_arcs.begin(), _arcs.end(), std::inserter(outArcs, outArcs.end()), [&](auto arc) {
			return arc != *it && arc->getInitialState() == (*it)->getFinalState();
		});

		if (_finalStates.find((*it)->getFinalState()) != _finalStates.end())
		{
			_finalStates.insert((*it)->getInitialState());
		}

		for (auto& arc : outArcs)
		{
			_arcs.insert(std::shared_ptr<Arc>(new Arc(
				(*it)->getInitialState(),
				arc->getFinalState(),
				arc->getType(),
				arc->getMark())));

			if (arc->getType() == ArcType::Lambda)
			{
				_arcs.erase(arc);
			}
		}

		_arcs.erase(it);

		it = std::find_if(_arcs.begin(), _arcs.end(), [&](auto arc) {
			return arc->getType() == ArcType::Lambda;
		});

		_writeToFile();
	}

	std::set<std::shared_ptr<State>> states;

	// Ќаходим все состо€ни€ кроме начального, в которые не входит ни одна дуга.
	std::copy_if(_states.begin(), _states.end(), std::inserter(states, states.end()), [&](auto state) { 
		return state != _initState && std::none_of(_arcs.begin(), _arcs.end(), [&](auto arc) {
			return arc->getFinalState() == state;
		});
	});

	// ”дал€ем все найденные состо€ни€ и исход€щие из них дуги.
	std::erase_if(_arcs, [&](auto arc) {
		return states.find(arc->getInitialState()) != states.end();
	});

	std::erase_if(_states, [&](auto state) {
		return states.find(state) != states.end();
	});

	_writeToFile();
}

void FiniteStateMachine::_determine()
{
	FiniteStateMachine machine;

	_initState->addInnerState(_initState);
	machine._initState = _initState;
	_determineRecur(machine, _initState);

	std::copy_if(machine._states.begin(), machine._states.end(), 
		std::inserter(machine._finalStates, machine._finalStates.end()), [&](auto v) {
			return std::any_of(v->getInnerStates().begin(), v->getInnerStates().end(), [&](auto s) {
				return _finalStates.find(s) != _finalStates.end();
			});
		});

	machine._clearInnerStates();

	*this = std::move(machine);
}

void FiniteStateMachine::_determineRecur(FiniteStateMachine& machine, const std::shared_ptr<State>& state)
{
	if (!state)
	{
		throw std::invalid_argument("Null state pointer.");
	}

	std::set<std::shared_ptr<Arc>> arcs;

	machine._states.insert(state);

	// Ќаходим все дуги, исход€щие из данного множества состо€ний
	for (auto& innerState : state->getInnerStates())
	{
		std::copy_if(_arcs.begin(), _arcs.end(), std::inserter(arcs, arcs.end()), [&](auto v) { 
			return v->getInitialState() == innerState; 
		});
	}

	for (auto& arc : arcs)
	{
		std::set<std::shared_ptr<Arc>> oneMarkArcs;
		std::set<std::shared_ptr<State>> states;

		// ќпредел€ем множество дуг с одинаковыми метками
		std::copy_if(arcs.begin(), arcs.end(), std::inserter(oneMarkArcs, oneMarkArcs.end()), [&](auto v) {
			return v->getMark() == arc->getMark();
		});

		// ќпредел€ем множество состо€ний, в которые есть переход по данной метке
		for (auto& arc : oneMarkArcs) { states.insert(arc->getFinalState()); }

		// »щем состо€ние, €вл€ющеес€ таким же множеством состо€ний в новом  ј
		auto it = std::find_if(machine._states.begin(), machine._states.end(), [&](auto v) {
			return v->getInnerStates() == states;
		});

		// ≈сли оно уже есть, добавл€ем дугу из нового состо€ни€ в данное
		if (it != machine._states.end())
		{
			machine._arcs.insert(std::shared_ptr<Arc>(new Arc(state, *it)));
		}
		// »наче добавл€ем состо€ние с данным множеством состо€ний и 
		// дугу в него, а также ищем все состо€ни€, св€занные с новым
		else
		{
			auto newState = std::shared_ptr<State>(new State);

			newState->addInnerState(states);

			machine._states.insert(newState);
			machine._arcs.insert(std::shared_ptr<Arc>(new Arc(state, newState)));

			_determineRecur(machine, newState);
		}
	}
}

void FiniteStateMachine::_clearInnerStates()
{
	for (auto& state : _states) 
	{ 
		state->clearInnerStates();
	}
}

void FiniteStateMachine::_writeToFile()
{
	std::ofstream out;

	out.open("graph.dot");

	if (out.is_open())
	{
		out << "digraph FSM {\n";

		for (auto& state : _states)
		{
			out << state->getId() << std::endl;
		}

		for (auto& arc : _arcs)
		{
			out << arc->getInitialState()->getId()
				<< " -> "
				<< arc->getFinalState()->getId()
				<< " [label="
				<< (arc->getType() == ArcType::Lambda ? "lambda" : std::string({ arc->getMark() }))
				<< "]" << std::endl;
		}

		out << "}";
	}

	out.close();
}



