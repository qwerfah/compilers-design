#pragma once

#include <string>

/// <summary>
///  Описывает состояние КА.
/// </summary>
class State
{
public:
	State();

	/// <summary>
	/// Получить идентификатор состояния.
	/// </summary>
	/// <returns> Идентификатор данного состояния. </returns>
	unsigned getId() const;

	bool operator == (const State& state) const;
	bool operator < (const State& state) const;

private:
	/// <summary>
	/// Идентификатор состояния.
	/// </summary>
	const unsigned _stateId;

	/// <summary>
	/// Глобальный идентификатор состояния для присваивания вновь созданным состояниям.
	/// </summary>
	static unsigned _globalId;
};

