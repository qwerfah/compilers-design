#pragma once

#include "state.h"
#include "arc.h"

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

	/// <summary>
	/// Установить начальное состояние для данного КА 
	/// (состояние добавляется в множество состояний КА).
	/// </summary>
	/// <param name="state"> Новое начальное состояние КА. </param>
	void setInitState(const std::shared_ptr<State>& state);

	/// <summary>
	/// Установить конечное состояние для данного КА 
	/// (состояние добавляется в множество состояний КА).
	/// </summary>
	/// <param name="state"> Новое конечное состояние КА. </param>
	void setFinalState(const std::shared_ptr<State>& state);

	/// <summary>
	/// Добавить новое состояние в множество состояний.
	/// </summary>
	/// <param name="state"> Новое состояние КА. </param>
	void addState(const std::shared_ptr<State>& state);

	/// <summary>
	/// Добавить новую дугу в множество дуг КА.
	/// </summary>
	/// <param name="arc"> Новая дуга КА. </param>
	void addArc(const std::shared_ptr<Arc>& arc);

	bool match(const std::string& expr);

	/// <summary>
	/// Переход из текущего состояния в следующее состояние.
	/// </summary>
	/// <returns> Метка дуги, по которой был осуществлен переход. </returns>
	char next();

	bool isInFinalState() const;

private:
	std::shared_ptr<State> _initState;
	std::shared_ptr<State> _finalState;
	std::shared_ptr<State> _currentState;

	std::set<std::shared_ptr<State>> _states;
	std::set<std::shared_ptr<Arc>> _arcs;
	bool _isInFinalState;

	std::mt19937 _engine;
};

