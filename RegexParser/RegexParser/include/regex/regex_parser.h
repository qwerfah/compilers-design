#pragma once

#include "../../include/regex/regular_expression/regular_expression.h"
#include "../../include/regex/regular_expression/or.h"
#include "../../include/regex/regular_expression/concat.h"
#include "../../include/regex/regular_expression/repeat.h"
#include "../../include/regex/regular_expression/literal.h"

#include <memory>
#include <stdexcept>
#include <stack>
#include <vector>
#include <string>
#include <sstream>

const std::string OPEN_BRACKETS = "([{";
const std::string CLOSE_BRACKETS = ")]}";
const std::string UNARY_QUANTIFIERS = "?*+{";
const std::string BINARY_QUANTIFIERS = "|";

/// <summary>
/// ������ ���������� ���������.
/// </summary>
class RegexParser
{
public:
	RegexParser() = default;
	RegexParser(const std::string& expression);

	/// <summary>
	/// ��������� ����� ��� ������ _parse, ������� ���������� ��������� ������ � ���� _tree.
	/// </summary>
	/// <param name="regex"> ��������� ������������� ����������� ���������. </param>
	void parse(const std::string& regex);

	const std::shared_ptr<RegularExpression>& getTree() const;

private:
	/// <summary>
	/// �������������� ������, ���������� � ���������� �������� ����������� ���������.
	/// </summary>
	std::shared_ptr<RegularExpression> _tree;

	/// <summary>
	/// ������ �� ������ ���������� ������������� ����������� ��������� �������������� 
	/// ������, ������� � ���������� ����� ���� ������������ ��� ���������� ��.
	/// </summary>
	/// <param name="regex"> ��������� ������������� ����������� ���������. </param>
	/// <returns> �������������� ������. </returns>
	std::shared_ptr<RegularExpression> _parse(const std::string& regex);

	/// <summary>
	/// ���������� ������ ���������� ���������, ����� �� ��� ������ �������������� ������.
	/// </summary>
	/// <param name="regex"> ���������� ���������. </param>
	/// <returns> �������������� ������. </returns>
	std::shared_ptr<RegularExpression> _parseRecur(const std::string& regex);

	/// <summary>
	/// ���� �������� "|" �� ������� ������ � � ������ ������ 
	/// �������� _parse ��� ������ � ������� ������������.
	/// </summary>
	/// <param name="regex"> ��������� ������������� ����������� ���������. </param>
	/// <param name="expr"> ��������� �� ����� ��������� ������ ����������� ���������, 
	/// ������� ��������� � ������ ����������� �������� ���������. </param>
	/// <returns> true - ���� �������� ������, false - �����. </returns>
	bool _tryParseOr(const std::string& regex, std::shared_ptr<RegularExpression>& expr);

	/// <summary>
	/// ���� ������������ �� ������� ������ � � ������ ������ 
	/// �������� _parse ��� ������ � ������� ������������.
	/// </summary>
	/// <param name="regex"> ��������� ������������� ����������� ���������. </param>
	/// <param name="expr"> ��������� �� ����� ��������� ������ ����������� ���������, 
	/// ������� ��������� � ������ ����������� ������������. </param>
	/// <returns> true - ���� ������� ������������, false - �����. </returns>
	bool _tryParseConcat(const std::string& regex, std::shared_ptr<RegularExpression>& expr);

	/// <summary>
	/// ���� �������������� �� ������� ������ � � ������ ������ �������� 
	/// _parse ��� ������������, ������������ � ������� ��������������.
	/// </summary>
	/// <param name="regex"> ��������� ������������� ����������� ���������. </param>
	/// <param name="expr"> ��������� �� ����� ��������� ������ ����������� ���������, 
	/// ������� ��������� � ������ ����������� ��������������. </param>
	/// <returns> true - ���� ������������� ������, false - �����. </returns>
	bool _tryParseQuantifier(const std::string& regex, std::shared_ptr<RegularExpression>& expr);

	/// <summary>
	/// ������ �������� ���� {m,n}, �������� ������� � ������ ������� 
	/// ����� ��������� ������������ � �������������� �������.
	/// </summary>
	/// <param name="str"> ��������� ������������� ���������. </param>
	/// /// <param name="range"> ������ �� �������� ������������� ���������, 
	/// ���� ������������ ��������� � ������ ������. </param>
	/// <returns> true - ���� ������� ������������ �������� ��������, false - �����. </returns>
	std::pair<size_t, size_t> _parseRange(const std::string& str);

	std::vector<std::string> _split(const std::string& str, char delim);

	/// <summary>
	/// ��������� ���������� ��������� �� ������������ ����������� ������.
	/// </summary>
	/// <param name="regex"> ���������� ���������. </param>
	/// <returns> true - ���� ������ ����������� ��������� ��� �����������, false - �����. </returns>
	bool _checkBrackets(const std::string& regex);

	/// <summary>
	/// ���������, �������� �� ���������� ������ ������������� �������.
	/// </summary>
	/// <param name="ch"> ������ ������. </param>
	/// <returns> true - ���� ch �������� ������������� �������, false - �����. </returns>
	static bool _isIn(char ch, const std::string& str);
};
