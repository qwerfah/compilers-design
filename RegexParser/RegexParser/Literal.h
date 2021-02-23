#pragma once
#include "RegularExpression.h"

/// <summary>
/// ���������� �������.
/// </summary>
class Literal :
    public RegularExpression
{
public:
    Literal(char c);

    /// <summary>
    /// �������� ���������� ������� ��� ������� ����������.
    /// </summary>
    /// <returns> ���������� �������, ����������� ������ ����������� ������. </returns>
    char getChar() const;

private:
    /// <summary>
    /// ���������� �������, ����������� ������ ����������� ������.
    /// </summary>
    const char _c;
};

