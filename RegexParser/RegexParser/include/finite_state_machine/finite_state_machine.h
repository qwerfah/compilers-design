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
	/// ���������� �������� ��������� ��� ������� �� 
	/// (��������� ����������� � ��������� ��������� ��).
	/// </summary>
	/// <param name="state"> ����� �������� ��������� ��. </param>
	void setFinalState(const std::shared_ptr<State>& state);

	/// <summary>
	/// �������� ����� ��������� � ��������� ���������.
	/// </summary>
	/// <param name="state"> ����� ��������� ��. </param>
	void addState(const std::shared_ptr<State>& state);

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

	void determine();
	void minimize();

	bool isInFinalState() const;

	const std::shared_ptr<State>& getInitState() const;
	const std::shared_ptr<State>& getFinalState() const;
	const std::shared_ptr<State>& getCurrentState() const;

private:
	std::shared_ptr<State> _initState;
	std::shared_ptr<State> _finalState;
	std::shared_ptr<State> _currentState;

	std::set<std::shared_ptr<State>> _states;
	std::set<std::shared_ptr<Arc>> _arcs;
	bool _isInFinalState;

	std::mt19937 _engine;
};

