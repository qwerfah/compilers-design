#pragma once

#include "state.h"
#include "arc.h"

#include <set>
#include <random>
#include <memory>
#include <stdexcept>
#include <variant>
#include <iterator>
#include <execution>
#include <fstream>
#include <iostream>
#include <functional>

/// <summary>
/// ��������� �������� �������.
/// </summary>
class FiniteStateMachine
{
public:
	FiniteStateMachine();

	FiniteStateMachine& operator = (FiniteStateMachine&& machine);


	/// <summary>
	/// ���������� ��������� ��������� ��� ������� �� 
	/// (��������� ����������� � ��������� ��������� ��).
	/// </summary>
	/// <param name="state"> ����� ��������� ��������� ��. </param>
	void addInitState(const std::shared_ptr<State>& state);
	void addInitState(const std::set<std::shared_ptr<State>>& states);

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
	TransitionType next(char ch);

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
	const std::set<std::shared_ptr<State>>& getInitStates() const;

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
	std::set<std::shared_ptr<State>> _initStates;

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
	/// ���������������� ����� � ������, �������������� ����� ���� ��� 
	/// ������ �� ��� ������-���������, ��������� �� ���������� ���������, 
	/// � ����� ���������� ������� ��������� � ��������� �������� ���������, ���� 
	/// ��������� �������� ��������� ��������� �� ������� �� ������ �������.
	/// </summary>
	/// <param name="init"> ���������, ��� �������� �������������� �����. </param>
	/// <param name="finalStates"> ������������ � ���� ������ ��������� 
	/// �������� ��������� ������ �� ��� ������-���������. </param>
	/// <returns> ��������� �������� ���, ��������� �� ���������� 
	/// ��������� � ����� �� ��� ������-���������. </returns>
	std::set<std::shared_ptr<Arc>> _bfs(
		const std::shared_ptr<State>& init, 
		std::set<std::shared_ptr<State>>& finalStates);

	/// <summary>
	/// ��������� �������������� ������� ��, � ������� �������������� ������� ��� Lambda-��������.
	/// </summary>
	void _determine();

	/// <summary>
	/// ��������� ����������� ���������� ������������������ �� ����� ����������� ��������� ��������� �� � ���������.
	/// </summary>
	/// <param name="machine"> ����������������� ��, ���������� � �������� ���������� �� ��������� ��. </param>
	/// <param name="state"> ��������� ��������� ������ ��, � �������� ���������� ��� ����������. </param>
	void _determineRecur(FiniteStateMachine& machine, const std::shared_ptr<State>& state);

	/// <summary>
	/// ������ �� ������ ������� �� �������� ��� �� 
	/// (������������� ��� ��������, � �������� ��������� �������� � ����������).
	/// </summary>
	void _reverse();

	/// <summary>
	/// �������� ���������� ��������� ���� ��������� �� ����� ��������������.
	/// </summary>
	void _clearInnerStates();

	/// <summary>
	/// ������������ ������ �� � ���� � ���� ����� �� ����� �������� DOT.
	/// </summary>
	void _writeToFile();

	void _execDebug(const std::function<void()>& action, const std::string& message);
};

