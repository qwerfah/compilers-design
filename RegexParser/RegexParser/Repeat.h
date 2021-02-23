#pragma once

#define REPEAT_STR "*"

#include "RegularExpression.h"

/// <summary>
/// ��������� ���������� ��������� "*", �������������� 
/// ������������ ����� ���������� ��������� �����������.
/// </summary>
class Repeat :
    public RegularExpression
{
public:
    Repeat(const RegularExpression& expr);

    /// <summary>
    /// �������� ����������� ���������� ���������.
    /// </summary>
    /// <returns> ����������� ���������� ���������. </returns>
    const  RegularExpression& getExpr() const;

private:
    /// <summary>
    /// ���������� ���������, ����������� � ������ �����������.
    /// </summary>
    const RegularExpression& _expr;
};

