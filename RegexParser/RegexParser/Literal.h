#pragma once

#include "RegularExpression.h"
#include "enums.h"

/// <summary>
/// ���������� �������.
/// </summary>
class Literal :
    public RegularExpression
{
public:
    Literal(char c, LiteralType type);

    /// <summary>
    /// �������� ���������� ������� ��� ������� ����������.
    /// </summary>
    /// <returns> ���������� �������, ����������� ������ ����������� ������. </returns>
    char getChar() const;

    /// <summary>
    /// �������� ��� ������� ��������.
    /// </summary>
    /// <returns> ��� ��������. </returns>
    LiteralType getType() const;

private:
    /// <summary>
    /// ���������� �������, ����������� ������ ����������� ������.
    /// </summary>
    char _c;

    /// <summary>
    /// ��� ��������.
    /// </summary>
    LiteralType _type;
};

