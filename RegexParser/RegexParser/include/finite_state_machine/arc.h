#pragma once

#include "state.h"
#include "../enums.h"

class FiniteStateMachine;

#include <memory>
#include <stdexcept>

/// <summary>
/// Дуга КА (переход между двумя состояниями КА).
/// </summary>
class Arc
{
public:
	Arc(const std::shared_ptr<State>& initialState, 
		const std::shared_ptr<State>& finalState, 
		ArcType type = ArcType::Lambda, char mark = 0);
	Arc(const std::shared_ptr<FiniteStateMachine>& machine,
		const std::shared_ptr<State>& finalState, 
		ArcType type = ArcType::Lambda, char mark = 0);
	Arc(const std::shared_ptr<State>& initialState, 
		const std::shared_ptr<FiniteStateMachine>& machine, 
		ArcType type = ArcType::Lambda, char mark = 0);
	Arc(const std::shared_ptr<FiniteStateMachine>& initMachine,
		const std::shared_ptr<FiniteStateMachine>& finalMachine,
		ArcType type = ArcType::Lambda, char mark = 0);

	/// <summary>
	/// Получить состояние, из которого исходит данная дуга.
	/// </summary>
	/// <returns> Начальное состояние дуги. </returns>
	const std::shared_ptr<State>& getInitialState() const;

	/// <summary>
	/// Получить состояние, в которое входит данная дуга.
	/// </summary>
	/// <returns> Конечное состояние дуги. </returns>
	const std::shared_ptr<State>& getIFinalState() const;

	/// <summary>
	/// Получить метку данной дуги.
	/// </summary>
	/// <returns> Метка дуги. </returns>
	char getMark() const;

	/// <summary>
	/// Возвращает тип перехода для данной дуги.
	/// </summary>
	/// <returns> Тип перехода. </returns>
	ArcType getType() const;

	bool operator < (const Arc& arc) const;

private:
	/// <summary>
	/// Начальное состояние дуги.
	/// </summary>
	std::shared_ptr<State> _initialState;

	/// <summary>
	/// Конечное состояние дуги.
	/// </summary>
	std::shared_ptr<State> _finalState;

	/// <summary>
	/// Метка дуги.
	/// </summary>
	const char _mark;

	/// <summary>
	/// Тип перехода.
	/// </summary>
	ArcType _type;
};

