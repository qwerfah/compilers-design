#pragma once

#define NON_ZERO_REPEAT_STR "+"

#include "RegularExpression.h"

/// <summary>
/// ��������� ����������� "+", ������������� ������������ 
/// ��������� ����� ���������� ���������� ����������� ���������.
/// </summary>
class NonZeroRepeat :
    public RegularExpression
{
public:
    NonZeroRepeat(const RegularExpression& expr);

    /// <summary>
    /// �������� ���������� ���������, ����������� � ������ ������ �����������.
    /// </summary>
    /// <returns> ����������� ���������� ���������. </returns>
    const RegularExpression& getExpr() const;

private:
    /// <summary>
    /// ���������� ���������, ����������� � ������ ������ �����������.
    /// </summary>
    const RegularExpression& _expr;

};

