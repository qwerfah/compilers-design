#pragma once

#include "state.h"
#include "arc.h"

#include <set>
#include <random>
#include <memory>

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
	/// �������� ����� ���� � ��������� ��� ��.
	/// </summary>
	/// <param name="arc"> ����� ���� ��. </param>
	void addArc(const std::shared_ptr<Arc>& arc);

	bool match(const std::string& expr);

	/// <summary>
	/// ������� �� �������� ��������� � ��������� ���������.
	/// </summary>
	/// <returns> ����� ����, �� ������� ��� ����������� �������. </returns>
	char next();

	bool isInFinalState() const;

private:
	std::shared_ptr<State> _initState;
	std::shared_ptr<State> _finalState;
	std::shared_ptr<State> _currentState;

	std::set<std::shared_ptr<State>> _states;
	std::set<std::shared_ptr<Arc>> _arcs;
	bool _isInFinalState;

	std::mt19937 _engine;
};

