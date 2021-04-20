#pragma once

#include "regular_expression.h"

#include <memory>

class Concat :
    public RegularExpression
{
public:
    Concat(std::shared_ptr<RegularExpression>& expr1, std::shared_ptr<RegularExpression>& expr2);
    Concat(std::shared_ptr<RegularExpression>&& expr1, std::shared_ptr<RegularExpression>&& expr2);

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

