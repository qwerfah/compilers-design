#pragma once

#include "state.h"
#include "arc.h"

#include <set>
#include <random>
#include <memory>
#include <stdexcept>
#include <variant>
#include <iterator>
#include <execution>
#include <fstream>
#include <iostream>
#include <functional>

/// <summary>
/// Описывает конечный автомат.
/// </summary>
class FiniteStateMachine
{
public:
	FiniteStateMachine();

	FiniteStateMachine& operator = (FiniteStateMachine&& machine);


	/// <summary>
	/// Установить начальное состояние для данного КА 
	/// (состояние добавляется в множество состояний КА).
	/// </summary>
	/// <param name="state"> Новое начальное состояние КА. </param>
	void addInitState(const std::shared_ptr<State>& state);
	void addInitState(const std::set<std::shared_ptr<State>>& states);

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
	TransitionType next(char ch);

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
	const std::set<std::shared_ptr<State>>& getInitStates() const;

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
	std::set<std::shared_ptr<State>> _initStates;

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
	/// Модифицированный поиск в ширину, осуществляющий поиск всех дуг 
	/// нового КА без лямбда-переходов, исходящих из указанного состояния, 
	/// а также добавление данного состояния в множество конечных состояний, если 
	/// некоторое конечное состояние достижимо из данного по пустой цепочке.
	/// </summary>
	/// <param name="init"> Состояние, для которого осуществляется поиск. </param>
	/// <param name="finalStates"> Составляемое в ходе поиска множество 
	/// конечных состояний нового КА без лямбда-переходов. </param>
	/// <returns> Множество непустых дуг, исходящих из указанного 
	/// состояния в новом КА без лямбда-переходов. </returns>
	std::set<std::shared_ptr<Arc>> _bfs(
		const std::shared_ptr<State>& init, 
		std::set<std::shared_ptr<State>>& finalStates);

	/// <summary>
	/// выполняет детерминизацию данного КА, в котором предварительно удалены все Lambda-переходы.
	/// </summary>
	void _determine();

	/// <summary>
	/// Выполняет рекурсивное построение детерминированного КА путем объединения состояний исходного КА в множества.
	/// </summary>
	/// <param name="machine"> Детерминированный КА, получаемый в процессе построения из исходного КА. </param>
	/// <param name="state"> Начальное состояние нового КА, с которого начинается его построение. </param>
	void _determineRecur(FiniteStateMachine& machine, const std::shared_ptr<State>& state);

	/// <summary>
	/// Строит на основе данного КА обратный ему КА 
	/// (реверсируются все переходы, а конечные состояния меняются с начальными).
	/// </summary>
	void _reverse();

	/// <summary>
	/// Удаление внутренних состояний всех состояний КА после детерминизации.
	/// </summary>
	void _clearInnerStates();

	/// <summary>
	/// Осуществляет запись КА в файл в виде графа на языке разметки DOT.
	/// </summary>
	void _writeToFile();

	void _execDebug(const std::function<void()>& action, const std::string& message);
};

