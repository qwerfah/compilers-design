#pragma once

#define REPEAT_STR "*"

#include "regular_expression.h"
#include "../../enums.h"

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
    Repeat(std::shared_ptr<RegularExpression>&& expr, RepeatType type, size_t from = 0, size_t to = 0);

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

    size_t getRangeFrom() const;
    size_t getRangeTo() const;

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

    /// <summary>
    /// ���������� ���������� ����� ���������� ��������� (���� ���������������).
    /// </summary>
    size_t _from;

    /// <summary>
    /// ����������� ���������� ����� ���������� ��������� (���� ���������������).
    /// </summary>
    size_t _to;
};

