#pragma once

#define REPEAT_STR "*"

#include "RegularExpression.h"
#include "enums.h"

#include <memory>

/// <summary>
/// ��������� ���������� ���������, �������������� 
/// ������������ ����� ���������� ��������� �����������.
/// </summary>
class Repeat :
    public RegularExpression
{
public:
    Repeat(std::shared_ptr<RegularExpression>& expr, RepeatType type);
    Repeat(std::shared_ptr<RegularExpression>&& expr, RepeatType type);

    /// <summary>
    /// �������� ����������� ���������� ���������.
    /// </summary>
    /// <returns> ����������� ���������� ���������. </returns>
    const std::shared_ptr<RegularExpression>& getExpr() const;

    /// <summary>
    /// �������� ��� ����������� ����������.
    /// </summary>
    /// <returns> ��� ����������� ����������. </returns>
    RepeatType getType() const;

    virtual RegularExpression& operator = (const RegularExpression& other) override;

private:
    /// <summary>
    /// ���������� ���������, ����������� � ������ �����������.
    /// </summary>
    std::shared_ptr<RegularExpression> _expr;

    /// <summary>
    /// ��� ����������� ����������.
    /// </summary>
    RepeatType _type;
};

