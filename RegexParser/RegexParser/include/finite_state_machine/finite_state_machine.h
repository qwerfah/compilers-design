#pragma once

#include "state.h"
#include "arc.h"

#include <set>
#include <random>
#include <memory>
#include <stdexcept>
#include <variant>


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
	/// Добавить новое состояние или КА в состав данного КА.
	/// </summary>
	/// <param name="list"> Список, каждый элемент которого либо состояние, либо КА. </param>
	void addState(const std::initializer_list<std::variant<
		std::shared_ptr<State>, std::shared_ptr<FiniteStateMachine>>>& list);

	/// <summary>
	/// Добавить новую дугу в множество дуг КА.
	/// </summary>
	/// <param name="arc"> Новая дуга КА. </param>
	void addArc(const std::shared_ptr<Arc>& arc);

	/// <summary>
	/// Включить другой КА в состав данного: множества состояний и дуг 
	/// результирующего КА определяются как объединения соответствующих множеств исходных КА.
	/// </summary>
	/// <param name="machine"> Новый КА. </param>
	void addMachine(const std::shared_ptr<FiniteStateMachine>& machine);

	/// <summary>
	/// Проверить, соответсвует ли входная цепочка языку, порождаемому данным КА.
	/// </summary>
	/// <param name="expr"> Входная цепочка. </param>
	/// <returns> true - если принадлежит, false - иначе. </returns>
	bool match(const std::string& expr);

	/// <summary>
	/// Переход из текущего состояния в следующее состояние.
	/// </summary>
	/// <returns> Метка дуги, по которой был осуществлен переход. </returns>
	bool next(char ch);

	void determine();
	void minimize();

	bool isInFinalState() const;

	const std::shared_ptr<State>& getInitState() const;
	const std::shared_ptr<State>& getFinalState() const;
	const std::shared_ptr<State>& getCurrentState() const;

private:
	std::shared_ptr<State> _initState;
	std::shared_ptr<State> _finalState;
	std::shared_ptr<State> _currentState;

	std::set<std::shared_ptr<State>> _states;
	std::set<std::shared_ptr<Arc>> _arcs;
	bool _isInFinalState;

	std::mt19937 _engine;
};

