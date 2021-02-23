#pragma once

#include "State.h"

/// <summary>
/// Дуга КА (переход между двумя состояниями КА).
/// </summary>
class Arc
{
public:
	Arc(const State& initialState = State(), const State& finalState = State(), char mark = 0);

	/// <summary>
	/// Получить состояние, из которого исходит данная дуга.
	/// </summary>
	/// <returns> Начальное состояние дуги. </returns>
	const State& getInitialState() const;

	/// <summary>
	/// Получить состояние, в которое входит данная дуга.
	/// </summary>
	/// <returns> Конечное состояние дуги. </returns>
	const State& getIFinalState() const;

	/// <summary>
	/// Получить метку данной дуги.
	/// </summary>
	/// <returns> Метка дуги. </returns>
	char getMark() const;

	bool operator < (const Arc& arc) const;

private:
	/// <summary>
	/// Начальное состояние дуги.
	/// </summary>
	const State& _initialState;

	/// <summary>
	/// Конечное состояние дуги.
	/// </summary>
	const State& _finalState;

	/// <summary>
	/// Метка дуги.
	/// </summary>
	const char _mark;
};

