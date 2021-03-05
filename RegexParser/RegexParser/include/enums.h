#pragma once

/// <summary>
/// ��� ����������� ������� ����������� ���������.
/// </summary>
enum class RepeatType
{
	/// <summary>
	/// ������������ ����� ����������.
	/// </summary>
	Arbitrary,
	/// <summary>
	/// ��������� ����� ����������.
	/// </summary>
	NonZero,
	/// <summary>
	/// ���� ��� ������������ ���������.
	/// </summary>
	NoneOrSingle,
	/// <summary>
	/// �������� �������� ����� ���������.
	/// </summary>
	Range
};

/// <summary>
/// ��� �������� ����������� ���������.
/// </summary>
enum class LiteralType
{
	/// <summary>
	/// ������� ������.
	/// </summary>
	Symbol,
	/// <summary>
	/// ������������ ������.
	/// </summary>
	Any,
	/// <summary>
	/// ������ ������������������.
	/// </summary>
	Empty
};

/// <summary>
/// ��� �������� � ��.
/// </summary>
enum class ArcType
{
	/// <summary>
	/// ���������� �������.
	/// </summary>
	Symbol,
	/// <summary>
	/// ������-�������.
	/// </summary>
	Lambda
};