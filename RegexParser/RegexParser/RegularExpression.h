#pragma once
#include <string>

/// <summary>
/// ����������� ����� ��� ������������ ����������� ����������� ���������.
/// </summary>
class RegularExpression
{
public:
	RegularExpression();
	RegularExpression(const std::string& rawString);

	/// <summary>
	/// �������� ��������� ������������� ����������� ���������.
	/// </summary>
	/// <returns> ��������� �������������. </returns>
	const std::string& getRawString() const;

	virtual RegularExpression& operator = (const RegularExpression& other);

protected:
	/// <summary>
	/// ��������� ������������� ����������� ����������� ���������.
	/// </summary>
	std::string _rawString;
};

