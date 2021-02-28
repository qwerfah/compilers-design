#pragma once

#include "state.h"

#include <memory>

/// <summary>
/// Дуга КА (переход между двумя состояниями КА).
/// </summary>
class Arc
{
public:
	Arc(const std::shared_ptr<State>& initialState, const std::shared_ptr<State>& finalState, char mark);

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
};

