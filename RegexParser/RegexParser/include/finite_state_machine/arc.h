#pragma once

#include "state.h"
#include "../enums.h"

class FiniteStateMachine;

#include <memory>
#include <stdexcept>

/// <summary>
/// ���� �� (������� ����� ����� ����������� ��).
/// </summary>
class Arc
{
public:
	Arc(const std::shared_ptr<State>& initialState, 
		const std::shared_ptr<State>& finalState, 
		ArcType type = ArcType::Lambda, char mark = 'λ');
	Arc(const std::shared_ptr<FiniteStateMachine>& machine,
		const std::shared_ptr<State>& finalState, 
		ArcType type = ArcType::Lambda, char mark = 'λ');
	Arc(const std::shared_ptr<State>& initialState, 
		const std::shared_ptr<FiniteStateMachine>& machine, 
		ArcType type = ArcType::Lambda, char mark = 'λ');
	Arc(const std::shared_ptr<FiniteStateMachine>& initMachine,
		const std::shared_ptr<FiniteStateMachine>& finalMachine,
		ArcType type = ArcType::Lambda, char mark = 'λ');

	/// <summary>
	/// �������� ���������, �� �������� ������� ������ ����.
	/// </summary>
	/// <returns> ��������� ��������� ����. </returns>
	const std::shared_ptr<State>& getInitialState() const;

	/// <summary>
	/// �������� ���������, � ������� ������ ������ ����.
	/// </summary>
	/// <returns> �������� ��������� ����. </returns>
	const std::shared_ptr<State>& getFinalState() const;

	/// <summary>
	/// �������� ����� ������ ����.
	/// </summary>
	/// <returns> ����� ����. </returns>
	char getMark() const;

	/// <summary>
	/// ���������� ��� �������� ��� ������ ����.
	/// </summary>
	/// <returns> ��� ��������. </returns>
	ArcType getType() const;

	bool operator < (const Arc& arc) const;

private:
	/// <summary>
	/// ��������� ��������� ����.
	/// </summary>
	std::shared_ptr<State> _initialState;

	/// <summary>
	/// �������� ��������� ����.
	/// </summary>
	std::shared_ptr<State> _finalState;

	/// <summary>
	/// ����� ����.
	/// </summary>
	const char _mark;

	/// <summary>
	/// ��� ��������.
	/// </summary>
	ArcType _type;
};

