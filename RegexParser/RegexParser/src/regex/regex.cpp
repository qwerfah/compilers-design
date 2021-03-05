#include "../../include/regex/regex.h"

Regex::Regex(const std::string& expression)
{
	_machine = std::shared_ptr<FiniteStateMachine>(new FiniteStateMachine);
	_machine->determine();
	_machine->minimize();
}

bool Regex::match(const std::string& chain)
{
	if (!_machine)
	{
		throw std::invalid_argument("Finite-state machine is not determined.");
	}

	return _machine->match(chain);
}

void Regex::buildFSM(const std::string& expression)
{
	std::shared_ptr<RegularExpression> expr = RegexParser::parse(expression);

	if (!expr)
	{
		throw std::logic_error("Can't build tree for string expression.");
	}

	_machine = _buildFSM(expr);

	if (!_machine)
	{
		throw std::logic_error("Can't build FSM for expression tree.");
	}
}

std::shared_ptr<FiniteStateMachine> Regex::_buildFSM(const std::shared_ptr<RegularExpression>& expr)
{
	if (auto orExpr = std::dynamic_pointer_cast<Or>(expr))
	{
		return _buildOr(orExpr);
	}
	else if (auto concat = std::dynamic_pointer_cast<Concat>(expr))
	{
		return _buildConcat(concat);
	}
	else if (auto repeat = std::dynamic_pointer_cast<Repeat>(expr))
	{
		switch (repeat->getType())
		{
		case RepeatType::Arbitrary: return _buildArbitraryRepeat(repeat);
		case RepeatType::NonZero: return _buildNonZeroRepeat(repeat);
		case RepeatType::NoneOrSingle: return _buildNonOrSingle(repeat);
		case RepeatType::Range: return _buildRangeRepeat(repeat);
		}
	}
	else if (auto literal = std::dynamic_pointer_cast<Literal>(expr))
	{
		switch (literal->getType())
		{
		case LiteralType::Symbol: case LiteralType::Any: return _buildSymbolLiteral(literal);
		case LiteralType::Empty: return _buildEmptyLiteral(literal);
		}
	}
	else
	{
		throw std::runtime_error("Unexpected type of tree node.");
	}
}

std::shared_ptr<FiniteStateMachine> Regex::_buildOr(const std::shared_ptr<Or>& expr)
{
	auto machine = std::shared_ptr<FiniteStateMachine>(new FiniteStateMachine);

	auto in = std::shared_ptr<State>(new State());
	auto out = std::shared_ptr<State>(new State());

	std::shared_ptr<FiniteStateMachine> leftFSM = _buildFSM(expr->getLeftExpr());
	std::shared_ptr<FiniteStateMachine> rightFSM = _buildFSM(expr->getRightExpr());

	machine->addState({ in, out, leftFSM, rightFSM });

	machine->addArc(std::shared_ptr<Arc>(new Arc(in, leftFSM)));
	machine->addArc(std::shared_ptr<Arc>(new Arc(in, rightFSM)));
	machine->addArc(std::shared_ptr<Arc>(new Arc(leftFSM, out)));
	machine->addArc(std::shared_ptr<Arc>(new Arc(rightFSM, out)));

	machine->setInitState(in);
	machine->setFinalState(out);

	return machine;
}

std::shared_ptr<FiniteStateMachine> Regex::_buildConcat(const std::shared_ptr<Concat>& expr)
{
	auto machine = std::shared_ptr<FiniteStateMachine>(new FiniteStateMachine);

	std::shared_ptr<FiniteStateMachine> leftFSM = _buildFSM(expr->getLeftExpr());
	std::shared_ptr<FiniteStateMachine> rightFSM = _buildFSM(expr->getRightExpr());

	machine->addState({ leftFSM, rightFSM });

	machine->addArc(std::shared_ptr<Arc>(new Arc(leftFSM, rightFSM)));

	machine->setInitState(leftFSM->getInitState());
	machine->setFinalState(rightFSM->getFinalState());

	return machine;
}

std::shared_ptr<FiniteStateMachine> Regex::_buildArbitraryRepeat(const std::shared_ptr<Repeat>& expr)
{
	auto machine = std::shared_ptr<FiniteStateMachine>(new FiniteStateMachine);

	auto in = std::shared_ptr<State>(new State());
	auto out = std::shared_ptr<State>(new State());

	std::shared_ptr<FiniteStateMachine> inner = _buildFSM(expr->getExpr());

	machine->addState({ in, out, inner });

	machine->addArc(std::shared_ptr<Arc>(new Arc(in, inner)));
	machine->addArc(std::shared_ptr<Arc>(new Arc(inner, in)));
	machine->addArc(std::shared_ptr<Arc>(new Arc(in, out)));

	machine->setInitState(in);
	machine->setFinalState(out);

	return machine;
}

std::shared_ptr<FiniteStateMachine> Regex::_buildNonZeroRepeat(const std::shared_ptr<Repeat>& expr)
{
	auto machine = std::shared_ptr<FiniteStateMachine>(new FiniteStateMachine);

	auto in = std::shared_ptr<State>(new State());
	auto inner = _buildFSM(expr->getExpr());

	machine->addState({ in, inner });

	machine->addArc(std::shared_ptr<Arc>(new Arc(in, inner)));
	machine->addArc(std::shared_ptr<Arc>(new Arc(inner, in)));

	machine->setInitState(in);
	machine->setFinalState(inner->getFinalState());

	return machine;
}

std::shared_ptr<FiniteStateMachine> Regex::_buildNonOrSingle(const std::shared_ptr<Repeat>& expr)
{
	auto machine = std::shared_ptr<FiniteStateMachine>(new FiniteStateMachine);

	auto in = std::shared_ptr<State>(new State());
	auto out = std::shared_ptr<State>(new State());
	auto inner = _buildFSM(expr->getExpr());

	machine->addState({ in, out, inner });

	machine->addArc(std::shared_ptr<Arc>(new Arc(in, inner)));
	machine->addArc(std::shared_ptr<Arc>(new Arc(inner, out)));
	machine->addArc(std::shared_ptr<Arc>(new Arc(in, out)));

	machine->setInitState(in);
	machine->setFinalState(out);

	return machine;
}

std::shared_ptr<FiniteStateMachine> Regex::_buildRangeRepeat(const std::shared_ptr<Repeat>& expr)
{
	return std::shared_ptr<FiniteStateMachine>();
}

std::shared_ptr<FiniteStateMachine> Regex::_buildSymbolLiteral(const std::shared_ptr<Literal>& expr)
{
	auto machine = std::shared_ptr<FiniteStateMachine>(new FiniteStateMachine);

	auto in = std::shared_ptr<State>(new State());
	auto out = std::shared_ptr<State>(new State());

	machine->addState({ in, out });

	machine->addArc(std::shared_ptr<Arc>(new Arc(in, out, ArcType::Symbol, expr->getChar())));

	machine->setInitState(in);
	machine->setFinalState(out);

	return machine;
}

std::shared_ptr<FiniteStateMachine> Regex::_buildEmptyLiteral(const std::shared_ptr<Literal>& expr)
{
	auto machine = std::shared_ptr<FiniteStateMachine>(new FiniteStateMachine);

	auto in = std::shared_ptr<State>(new State());

	machine->addState({ in });

	machine->setInitState(in);
	machine->setFinalState(in);

	return machine;
}
