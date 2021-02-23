#pragma once
#include <string>

/// <summary>
/// ����������� ����� ��� ������������ ����������� ����������� ���������.
/// </summary>
class RegularExpression
{
public:
	RegularExpression(const std::string& rawString);

	/// <summary>
	/// �������� ��������� ������������� ����������� ���������.
	/// </summary>
	/// <returns> ��������� �������������. </returns>
	const std::string& getRawString() const;

protected:
	/// <summary>
	/// ��������� ������������� ����������� ����������� ���������.
	/// </summary>
	const std::string _rawString;
};

