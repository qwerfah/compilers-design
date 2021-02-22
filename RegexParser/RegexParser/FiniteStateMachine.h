#pragma once

#include "State.h"
#include "Arc.h"
#include <set>
#include <random>

/// <summary>
/// ��������� �������� �������.
/// </summary>
class FiniteStateMachine
{
public:
	FiniteStateMachine();
	FiniteStateMachine(const std::set<State>& states,
					   const std::set<State>& finalStates,
					   const State& currentState,
					   const std::set<Arc>& arcs);

	/// <summary>
	/// �������� ����� ��������� � ��������� ���������.
	/// </summary>
	/// <param name="state"> ����� ��������� ��. </param>
	void addState(const State& state);

	/// <summary>
	/// �������� �������� ��������� ��� ������� �� 
	/// (��������� ����������� � � ��������� ��������� ��, � � ��������� �������� ��������� ��).
	/// </summary>
	/// <param name="state"> ����� �������� ��������� ��. </param>
	void addFinalState(const State& state);

	/// <summary>
	/// �������� ����� ���� � ��������� ��� ��.
	/// </summary>
	/// <param name="arc"> ����� ���� ��. </param>
	void addArc(const Arc& arc);

	/// <summary>
	/// ������� �� �������� ��������� � ��������� ���������.
	/// </summary>
	void next();


private:
	const State& _currentState;
	std::set<State> _states;
	std::set<State> _finalStates;
	std::set<Arc> _arcs;

	std::mt19937 _engine;
};

