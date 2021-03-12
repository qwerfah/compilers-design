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
	/// Добавить новое состояние в множество состояний.
	/// </summary>
	/// <param name="state"> Новое состояние КА. </param>
	void addState(const std::shared_ptr<State>& state);

	/// <summary>
	/// Добавить новое конечное состояние в множество конечных состояний 
	/// (состояние также добавляется в множество всех состояний КА).
	/// </summary>
	/// <param name="state"> Новое конечное состояние КА. </param>
	void addFinalState(const std::shared_ptr<State>& state);

	/// <summary>
	/// Добавить множество новых конечных состояний в множество конечных состояний 
	/// (состояния также добавляются в множество всех состояний КА).
	/// </summary>
	/// <param name="states"> Новое конечное состояние КА. </param>
	void addFinalState(const std::set<std::shared_ptr<State>>& states);

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

	/// <summary>
	/// Выполняет детерминизацию данного КА.
	/// </summary>
	void determine();

	/// <summary>
	/// Выполняет минимизацию данного КА.
	/// </summary>
	void minimize();

	/// <summary>
	/// Возвращает флаг, указывающий, находится ли КА в конечном состоянии.
	/// </summary>
	/// <returns></returns>
	bool isInFinalState() const;

	/// <summary>
	/// Возвращает указатель на начальное состояние данного КА.
	/// </summary>
	/// <returns> Указатель на начальное состояние КА. </returns>
	const std::shared_ptr<State>& getInitState() const;

	/// <summary>
	/// Возвращает возвращает множество конечных состояний данного КА.
	/// </summary>
	/// <returns> Указатель на конечное состояние КА. </returns>
	const std::set<std::shared_ptr<State>>& getFinalStates() const;

	/// <summary>
	/// Возвращает указатель на текущее состояние данного КА.
	/// </summary>
	/// <returns> Указатель на текущее состояние КА. </returns>
	const std::shared_ptr<State>& getCurrentState() const;

private:
	/// <summary>
	/// Указатель на начальное состояние данного КА.
	/// </summary>
	std::shared_ptr<State> _initState;

	/// <summary>
	/// Множество конечных состояний данного КА.
	/// </summary>
	std::set<std::shared_ptr<State>> _finalStates;

	/// <summary>
	/// Указатель на текущее состояние данного КА.
	/// </summary>
	std::shared_ptr<State> _currentState;

	/// <summary>
	/// Множество всех состояний данного КА.
	/// </summary>
	std::set<std::shared_ptr<State>> _states;

	/// <summary>
	/// Множество дуг данного КА.
	/// </summary>
	std::set<std::shared_ptr<Arc>> _arcs;

	/// <summary>
	/// Флаг, указывающий, находится ли данный КА в конечном состоянии.
	/// </summary>
	bool _isInFinalState;

	/// <summary>
	/// Генератор случайных чисел для выбора случайного перехода.
	/// </summary>
	std::mt19937 _engine;

	/// <summary>
	/// Удаляет все Lambda-переходы в данном КА.
	/// </summary>
	void _removeLambda();

	/// <summary>
	/// выполняет детерминизацию данного КА, в котором предварительно удалены все Lambda-переходы.
	/// </summary>
	void _determine();
};

