#pragma once

#include <string>
#include <memory>
#include <set>
#include <stdexcept>
#include <algorithm>

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
	State& operator = (const State& state);

	/// <summary>
	/// Добавить новое состояние КА в множество состояний данного состояния.
	/// </summary>
	/// <param name="state"> Новое внутреннее состояние КА. </param>
	void addInnerState(const std::shared_ptr<State>& state);

	/// <summary>
	/// Добавить множество новых состояний КА в множество внутренних состояний данного состояния.
	/// </summary>
	/// <param name="states"> Множество новых состояний КА. </param>
	void addInnerState(const std::set<std::shared_ptr<State>>& state);

	/// <summary>
	/// Возвращает множество всех внутренних состояний данного состояния КА.
	/// </summary>
	/// <returns> Множество внутренних состояний данного состояния. </returns>
	const std::set<std::shared_ptr<State>>& getInnerStates() const;

	/// <summary>
	/// Очистить множество внутренних состояний данного состояния КА.
	/// </summary>
	void clearInnerStates();

private:
	/// <summary>
	/// Идентификатор состояния.
	/// </summary>
	unsigned _stateId;

	/// <summary>
	/// Глобальный идентификатор состояния для присваивания вновь созданным состояниям.
	/// </summary>
	static unsigned _globalId;

	/// <summary>
	/// Множество внутренних состояний КА, которым является данное состояние (применяется при детерминизации).
	/// </summary>
	std::set<std::shared_ptr<State>> _innerStates;
};

