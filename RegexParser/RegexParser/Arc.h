#pragma once

#include "State.h"

/// <summary>
/// ���� �� (������� ����� ����� ����������� ��).
/// </summary>
class Arc
{
public:
	Arc(const State& initialState, const State& finalState, char mark);

	/// <summary>
	/// �������� ���������, �� �������� ������� ������ ����.
	/// </summary>
	/// <returns> ��������� ��������� ����. </returns>
	const State& getInitialState() const;

	/// <summary>
	/// �������� ���������, � ������� ������ ������ ����.
	/// </summary>
	/// <returns> �������� ��������� ����. </returns>
	const State& getIFinalState() const;

	/// <summary>
	/// �������� ����� ������ ����.
	/// </summary>
	/// <returns> ����� ����. </returns>
	char getMark() const;

	bool operator < (const Arc& arc) const;

private:
	/// <summary>
	/// ��������� ��������� ����.
	/// </summary>
	const State& _initialState;

	/// <summary>
	/// �������� ��������� ����.
	/// </summary>
	const State& _finalState;

	/// <summary>
	/// ����� ����.
	/// </summary>
	const char _mark;
};

