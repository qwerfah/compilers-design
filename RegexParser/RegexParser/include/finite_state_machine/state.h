#pragma once

#include <string>

/// <summary>
///  ��������� ��������� ��.
/// </summary>
class State
{
public:
	State();

	/// <summary>
	/// �������� ������������� ���������.
	/// </summary>
	/// <returns> ������������� ������� ���������. </returns>
	unsigned getId() const;

	bool operator == (const State& state) const;
	bool operator < (const State& state) const;
	State& operator = (const State& state);

private:
	/// <summary>
	/// ������������� ���������.
	/// </summary>
	unsigned _stateId;

	/// <summary>
	/// ���������� ������������� ��������� ��� ������������ ����� ��������� ����������.
	/// </summary>
	static unsigned _globalId;
};

