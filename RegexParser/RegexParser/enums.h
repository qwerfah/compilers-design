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
	NoneOrSingle
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