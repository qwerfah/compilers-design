#pragma once

#include <string>
#include <memory>
#include <set>
#include <stdexcept>
#include <algorithm>

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

	/// <summary>
	/// �������� ����� ��������� �� � ��������� ��������� ������� ���������.
	/// </summary>
	/// <param name="state"> ����� ���������� ��������� ��. </param>
	void addInnerState(const std::shared_ptr<State>& state);

	/// <summary>
	/// �������� ��������� ����� ��������� �� � ��������� ���������� ��������� ������� ���������.
	/// </summary>
	/// <param name="states"> ��������� ����� ��������� ��. </param>
	void addInnerState(const std::set<std::shared_ptr<State>>& state);

	/// <summary>
	/// ���������� ��������� ���� ���������� ��������� ������� ��������� ��.
	/// </summary>
	/// <returns> ��������� ���������� ��������� ������� ���������. </returns>
	const std::set<std::shared_ptr<State>>& getInnerStates() const;

	/// <summary>
	/// �������� ��������� ���������� ��������� ������� ��������� ��.
	/// </summary>
	void clearInnerStates();

private:
	/// <summary>
	/// ������������� ���������.
	/// </summary>
	unsigned _stateId;

	/// <summary>
	/// ���������� ������������� ��������� ��� ������������ ����� ��������� ����������.
	/// </summary>
	static unsigned _globalId;

	/// <summary>
	/// ��������� ���������� ��������� ��, ������� �������� ������ ��������� (����������� ��� ��������������).
	/// </summary>
	std::set<std::shared_ptr<State>> _innerStates;
};

