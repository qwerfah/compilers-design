#pragma once
#include "RegularExpression.h"

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
	RegularExpression parse(const std::string& regex) const;

private:
	RegexParser();
	RegularExpression _parse(std::string& regex) const;
};
