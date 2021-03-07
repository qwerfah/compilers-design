#pragma once

#include "../../include/finite_state_machine/finite_state_machine.h"
#include "../../include/regex/regular_expression/regular_expression.h"
#include "../../include/regex/regular_expression/or.h"
#include "../../include/regex/regular_expression/repeat.h"
#include "../../include/regex/regular_expression/concat.h"
#include "../../include/regex/regular_expression/literal.h"
#include "../../include/regex/regex_parser.h"

#include <string>
#include <memory>
#include <stdexcept>

class Regex
{
public:
	Regex(const std::string& expression);

	/// <summary>
	/// ��������� ������ �� ������������ ����������� ���������, ������������ ������ �����������.
	/// </summary>
	/// <param name="chain"> ������� �������. </param>
	/// <returns> true - ���� ������ ������������ ����������� ��������� 
	/// (������� ������� ����������� �����������, �������������� ������� ��), false - �����. </returns>
	bool match(const std::string& chain);

	/// <summary>
	/// ��������� � ��������� ���, �������������� 
	/// ����������� ���������� ������������� ����������� ���������.
	/// </summary>
	/// <param name="expression"> ��������� ������������� ����������� ���������. </param>
	void buildFSM(const std::string& expression);

private:
	/// <summary>
	/// ������� ������ ��� ���������� ����������� ���������, ����������� � ������� buildFSM ��� �����������. 
	/// </summary>
	std::shared_ptr<RegexParser> _parser;

	/// <summary>
	/// ������� �� ��� ���������� ����������� ���������, ����������� � ������� buildFSM ��� �����������.
	/// </summary>
	std::shared_ptr<FiniteStateMachine> _machine;

	void _buildFSM(const std::string& expression);

	/// <summary>
	/// ��������� ���, �������������� ����������� ���������, ��������������� � ���� ��������������� ������.
	/// </summary>
	/// <param name="expr"> �������������� ������ ����������� ���������. </param>
	/// <returns> ��������� �� ����������� ��. </returns>
	std::shared_ptr<FiniteStateMachine> _buildFSMRecur(const std::shared_ptr<RegularExpression>& expr);

	/// <summary>
	/// ��������� ��� ��� ����������� "���" ����������� ���������.
	/// </summary>
	/// <param name="expr"> ���������� ���������. </param>
	/// <returns> ��������� �� ����������� ��. </returns>
	std::shared_ptr<FiniteStateMachine> _buildOr(const std::shared_ptr<Or>& expr);

	/// <summary>
	/// ��������� ��� ��� ������������ ���� ������������ ����������� ���������.
	/// </summary>
	/// <param name="expr"> ���������� ���������. </param>
	/// <returns> ��������� �� ����������� ��. </returns>
	std::shared_ptr<FiniteStateMachine> _buildConcat(const std::shared_ptr<Concat>& expr);

	/// <summary>
	/// ��������� ��� ��� ����������� "*".
	/// </summary>
	/// <param name="expr"> ���������� ���������. </param>
	/// <returns> ��������� �� ����������� ��. </returns>
	std::shared_ptr<FiniteStateMachine> _buildArbitraryRepeat(const std::shared_ptr<Repeat>& expr);

	/// <summary>
	/// ��������� ��� ��� ����������� "+".
	/// </summary>
	/// <param name="expr"> ���������� ���������. </param>
	/// <returns> ��������� �� ����������� ��. </returns>
	std::shared_ptr<FiniteStateMachine> _buildNonZeroRepeat(const std::shared_ptr<Repeat>& expr);

	/// <summary>
	/// ��������� ��� ��� ����������� "?".
	/// </summary>
	/// <param name="expr"> ���������� ���������. </param>
	/// <returns> ��������� �� ����������� ��. </returns>
	std::shared_ptr<FiniteStateMachine> _buildNonOrSingle(const std::shared_ptr<Repeat>& expr);

	/// <summary>
	/// ��������� ��� ��� ����������� "{}".
	/// </summary>
	/// <param name="expr"> ���������� ���������. </param>
	/// <returns> ��������� �� ����������� ��. </returns>
	std::shared_ptr<FiniteStateMachine> _buildRangeRepeat(const std::shared_ptr<Repeat>& expr);

	/// <summary>
	/// ��������� ��� ��� ��������� ����������� �������� ����������� ���������.
	/// </summary>
	/// <param name="expr"> ���������� ���������. </param>
	/// <returns> ��������� �� ����������� ��. </returns>
	std::shared_ptr<FiniteStateMachine> _buildSymbolLiteral(const std::shared_ptr<Literal>& expr);

	/// <summary>
	/// ��������� ��� ��� ������� ����������� �������� ����������� ���������.
	/// </summary>
	/// <param name="expr"> ���������� ���������. </param>
	/// <returns> ��������� �� ����������� ��. </returns>
	std::shared_ptr<FiniteStateMachine> _buildEmptyLiteral(const std::shared_ptr<Literal>& expr);
};