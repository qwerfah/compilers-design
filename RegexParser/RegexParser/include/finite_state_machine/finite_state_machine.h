#pragma once

#include "state.h"
#include "arc.h"

#include <set>
#include <random>
#include <memory>
#include <stdexcept>
#include <variant>


/// <summary>
/// ��������� �������� �������.
/// </summary>
class FiniteStateMachine
{
public:
	FiniteStateMachine();

	/// <summary>
	/// ���������� ��������� ��������� ��� ������� �� 
	/// (��������� ����������� � ��������� ��������� ��).
	/// </summary>
	/// <param name="state"> ����� ��������� ��������� ��. </param>
	void setInitState(const std::shared_ptr<State>& state);

	/// <summary>
	/// �������� ����� ��������� � ��������� ���������.
	/// </summary>
	/// <param name="state"> ����� ��������� ��. </param>
	void addState(const std::shared_ptr<State>& state);

	/// <summary>
	/// �������� ����� �������� ��������� � ��������� �������� ��������� 
	/// (��������� ����� ����������� � ��������� ���� ��������� ��).
	/// </summary>
	/// <param name="state"> ����� �������� ��������� ��. </param>
	void addFinalState(const std::shared_ptr<State>& state);

	/// <summary>
	/// �������� ��������� ����� �������� ��������� � ��������� �������� ��������� 
	/// (��������� ����� ����������� � ��������� ���� ��������� ��).
	/// </summary>
	/// <param name="states"> ����� �������� ��������� ��. </param>
	void addFinalState(const std::set<std::shared_ptr<State>>& states);

	/// <summary>
	/// �������� ����� ��������� ��� �� � ������ ������� ��.
	/// </summary>
	/// <param name="list"> ������, ������ ������� �������� ���� ���������, ���� ��. </param>
	void addState(const std::initializer_list<std::variant<
		std::shared_ptr<State>, std::shared_ptr<FiniteStateMachine>>>& list);

	/// <summary>
	/// �������� ����� ���� � ��������� ��� ��.
	/// </summary>
	/// <param name="arc"> ����� ���� ��. </param>
	void addArc(const std::shared_ptr<Arc>& arc);

	/// <summary>
	/// �������� ������ �� � ������ �������: ��������� ��������� � ��� 
	/// ��������������� �� ������������ ��� ����������� ��������������� �������� �������� ��.
	/// </summary>
	/// <param name="machine"> ����� ��. </param>
	void addMachine(const std::shared_ptr<FiniteStateMachine>& machine);

	/// <summary>
	/// ���������, ������������ �� ������� ������� �����, ������������ ������ ��.
	/// </summary>
	/// <param name="expr"> ������� �������. </param>
	/// <returns> true - ���� �����������, false - �����. </returns>
	bool match(const std::string& expr);

	/// <summary>
	/// ������� �� �������� ��������� � ��������� ���������.
	/// </summary>
	/// <returns> ����� ����, �� ������� ��� ����������� �������. </returns>
	bool next(char ch);

	/// <summary>
	/// ��������� �������������� ������� ��.
	/// </summary>
	void determine();

	/// <summary>
	/// ��������� ����������� ������� ��.
	/// </summary>
	void minimize();

	/// <summary>
	/// ���������� ����, �����������, ��������� �� �� � �������� ���������.
	/// </summary>
	/// <returns></returns>
	bool isInFinalState() const;

	/// <summary>
	/// ���������� ��������� �� ��������� ��������� ������� ��.
	/// </summary>
	/// <returns> ��������� �� ��������� ��������� ��. </returns>
	const std::shared_ptr<State>& getInitState() const;

	/// <summary>
	/// ���������� ���������� ��������� �������� ��������� ������� ��.
	/// </summary>
	/// <returns> ��������� �� �������� ��������� ��. </returns>
	const std::set<std::shared_ptr<State>>& getFinalStates() const;

	/// <summary>
	/// ���������� ��������� �� ������� ��������� ������� ��.
	/// </summary>
	/// <returns> ��������� �� ������� ��������� ��. </returns>
	const std::shared_ptr<State>& getCurrentState() const;

private:
	/// <summary>
	/// ��������� �� ��������� ��������� ������� ��.
	/// </summary>
	std::shared_ptr<State> _initState;

	/// <summary>
	/// ��������� �������� ��������� ������� ��.
	/// </summary>
	std::set<std::shared_ptr<State>> _finalStates;

	/// <summary>
	/// ��������� �� ������� ��������� ������� ��.
	/// </summary>
	std::shared_ptr<State> _currentState;

	/// <summary>
	/// ��������� ���� ��������� ������� ��.
	/// </summary>
	std::set<std::shared_ptr<State>> _states;

	/// <summary>
	/// ��������� ��� ������� ��.
	/// </summary>
	std::set<std::shared_ptr<Arc>> _arcs;

	/// <summary>
	/// ����, �����������, ��������� �� ������ �� � �������� ���������.
	/// </summary>
	bool _isInFinalState;

	/// <summary>
	/// ��������� ��������� ����� ��� ������ ���������� ��������.
	/// </summary>
	std::mt19937 _engine;

	/// <summary>
	/// ������� ��� Lambda-�������� � ������ ��.
	/// </summary>
	void _removeLambda();

	/// <summary>
	/// ��������� �������������� ������� ��, � ������� �������������� ������� ��� Lambda-��������.
	/// </summary>
	void _determine();
};

