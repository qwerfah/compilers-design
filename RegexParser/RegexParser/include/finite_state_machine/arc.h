#pragma once

#include "state.h"

#include <memory>

/// <summary>
/// ���� �� (������� ����� ����� ����������� ��).
/// </summary>
class Arc
{
public:
	Arc(const std::shared_ptr<State>& initialState, const std::shared_ptr<State>& finalState, char mark);

	/// <summary>
	/// �������� ���������, �� �������� ������� ������ ����.
	/// </summary>
	/// <returns> ��������� ��������� ����. </returns>
	const std::shared_ptr<State>& getInitialState() const;

	/// <summary>
	/// �������� ���������, � ������� ������ ������ ����.
	/// </summary>
	/// <returns> �������� ��������� ����. </returns>
	const std::shared_ptr<State>& getIFinalState() const;

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
	std::shared_ptr<State> _initialState;

	/// <summary>
	/// �������� ��������� ����.
	/// </summary>
	std::shared_ptr<State> _finalState;

	/// <summary>
	/// ����� ����.
	/// </summary>
	const char _mark;
};

