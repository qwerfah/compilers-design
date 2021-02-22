#pragma once

#include "State.h"
#include "Arc.h"

#include <set>
#include <random>
#include <memory>

/// <summary>
/// Описывает конечный автомат.
/// </summary>
class FiniteStateMachine
{
public:
	FiniteStateMachine();
	FiniteStateMachine(const std::set<State>& states,
					   const std::set<State>& finalStates,
					   const State& currentState,
					   const std::set<Arc>& arcs);

	/// <summary>
	/// Добавить новое состояние в множество состояний.
	/// </summary>
	/// <param name="state"> Новое состояние КА. </param>
	void addState(const State& state);

	/// <summary>
	/// Добавить конечное состояние для данного КА 
	/// (состояние добавляется и в множество состояний КА, и в множество конечных состояний КА).
	/// </summary>
	/// <param name="state"> Новое конечное состояние КА. </param>
	void addFinalState(const State& state);

	/// <summary>
	/// Добавить новую дугу в множество дуг КА.
	/// </summary>
	/// <param name="arc"> Новая дуга КА. </param>
	void addArc(const Arc& arc);

	/// <summary>
	/// Переход из текущего состояния в следующее состояние.
	/// </summary>
	void next();

	bool isInFinalState() const;

private:
	std::unique_ptr<const State> _currentState;
	std::set<State> _states;
	std::set<State> _finalStates;
	std::set<Arc> _arcs;
	bool _isInFinalState;

	std::mt19937 _engine;
};

