#pragma once

#include "regular_expression.h"

#include <memory>
#include <string>

const std::string OR_STR = "|";

/// <summary>
/// ��������� ����������� "|" � ���������� ���������.
/// </summary>
class Or :
    public RegularExpression
{
public:
    Or(std::shared_ptr<RegularExpression>& expr1, std::shared_ptr<RegularExpression>& expr2);
    Or(std::shared_ptr<RegularExpression>&& expr1, std::shared_ptr<RegularExpression>&& expr2);

    /// <summary>
    /// �������� ����� ������� ����������� "|".
    /// </summary>
    /// <returns> ����� �������, �������������� ����� ���������� ���������. </returns>
    const std::shared_ptr<RegularExpression>& getLeftExpr() const;

    /// <summary>
    /// �������� ������ ������� ����������� "|".
    /// </summary>
    /// <returns> ������ �������, �������������� ����� ���������� ���������. </returns>
    const std::shared_ptr<RegularExpression>& getRightExpr() const;

    virtual RegularExpression& operator = (const RegularExpression& other) override;


private:
    /// <summary>
    /// ����� ������� ����������� "|".
    /// </summary>
    std::shared_ptr<RegularExpression> _leftExpr;

    /// <summary>
    /// ������ ������� ����������� "|".
    /// </summary>
    std::shared_ptr<RegularExpression> _rightExpr;
};

