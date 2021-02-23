#pragma once

#define OR_STR "|"

#include "RegularExpression.h"

/// <summary>
/// ��������� ����������� "|" � ���������� ���������.
/// </summary>
class Or :
    public RegularExpression
{
public:
    Or(const RegularExpression& expr1, const RegularExpression& expr2);

    /// <summary>
    /// �������� ����� ������� ����������� "|".
    /// </summary>
    /// <returns> ����� �������, �������������� ����� ���������� ���������. </returns>
    const RegularExpression& getLeftExpr() const;

    /// <summary>
    /// �������� ������ ������� ����������� "|".
    /// </summary>
    /// <returns> ������ �������, �������������� ����� ���������� ���������. </returns>
    const RegularExpression& getRightExpr() const;

private:
    /// <summary>
    /// ����� ������� ����������� "|".
    /// </summary>
    const RegularExpression& _leftExpr;

    /// <summary>
    /// ������ ������� ����������� "|".
    /// </summary>
    const RegularExpression& _rightExpr;
};

