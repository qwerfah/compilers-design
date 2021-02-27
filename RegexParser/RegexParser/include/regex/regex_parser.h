#pragma once

#define OPEN_BRACKETS "([{"
#define CLOSE_BRACKETS ")]}"
#define UNARY_QUANTIFIERS "?*+"
#define BINARY_QUANTIFIERS "|"

#include "../../include/regex/regular_expression/regular_expression.h"
#include "../../include/regex/regular_expression/or.h"
#include "../../include/regex/regular_expression/concat.h"
#include "../../include/regex/regular_expression/repeat.h"
#include "../../include/regex/regular_expression/literal.h"

#include <memory>
#include <stdexcept>
#include <stack>

/// <summary>
/// ������ ���������� ���������.
/// </summary>
static class RegexParser
{
public:
	/// <summary>
	/// ������ �� ������ ���������� ������������� ����������� ��������� �������������� 
	/// ������, ������� � ���������� ����� ���� ������������ ��� ���������� ��.
	/// </summary>
	/// <param name="regex"> ��������� ������������� ����������� ���������. </param>
	/// <returns> �������������� ������. </returns>
	static std::shared_ptr<RegularExpression> parse(const std::string& regex);

private:
	RegexParser();

	/// <summary>
	/// ���������� ������ ���������� ���������, ����� �� ��� ������ �������������� ������.
	/// </summary>
	/// <param name="regex"> ���������� ���������. </param>
	/// <returns> �������������� ������. </returns>
	static std::shared_ptr<RegularExpression> _parse(std::string&& regex);

	static bool _tryFindOr(std::string& regex, std::shared_ptr<RegularExpression>& expr);

	static bool _tryFindConcat(std::string& regex, std::shared_ptr<RegularExpression>& expr);

	static bool _tryFindQuantifier(std::string& regex, std::shared_ptr<RegularExpression>& expr);

	/// <summary>
	/// ��������� ���������� ��������� �� ������������ ����������� ������.
	/// </summary>
	/// <param name="regex"> ���������� ���������. </param>
	/// <returns> true - ���� ������ ����������� ��������� ��� �����������, false - �����. </returns>
	static bool _checkBrackets(const std::string& regex);

	/// <summary>
	/// ���������, �������� �� ���������� ������ ������������� �������.
	/// </summary>
	/// <param name="ch"> ������ ������. </param>
	/// <returns> true - ���� ch �������� ������������� �������, false - �����. </returns>
	static bool _isOpenBracket(char ch);

	/// <summary>
	/// ���������, �������� �� ���������� ������ ������������� �������.
	/// </summary>
	/// <param name="ch"> ������ ������. </param>
	/// <returns> true - ���� ch �������� ������������� �������, false - �����. </returns>
	static bool _isCloseBracket(char ch);

	/// <summary>
	/// ���������, �������� �� ���������� ������ ������� ���������������.
	/// </summary>
	/// <param name="ch"> ������ ������. </param>
	/// <returns> true - ���� ch �������� ������� ���������������, false - �����. </returns>
	static bool _isUnaryQuantifier(char ch);

	/// <summary>
	/// ���������, �������� �� ���������� ������ �������� ���������������.
	/// </summary>
	/// <param name="ch"> ������ ������. </param>
	/// <returns> true - ���� ch �������� �������� ���������������, false - �����. </returns>
	static bool _isBinaryQuantifier(char ch);

	/// <summary>
	/// ���������, �������� �� ���������� ������ ���������������.
	/// </summary>
	/// <param name="ch"> ������ ������. </param>
	/// <returns> true - ���� ch �������� ���������������, false - �����. </returns>
	static bool _isQuantifier(char ch);
};
