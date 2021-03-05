#pragma once

#define REPEAT_STR "*"

#include "regular_expression.h"
#include "../../enums.h"

#include <memory>

/// <summary>
/// Описывает регулярное выражение, предполагающее 
/// определенное число повторений указанной конструкции.
/// </summary>
class Repeat :
    public RegularExpression
{
public:
    Repeat(std::shared_ptr<RegularExpression>& expr, RepeatType type);
    Repeat(std::shared_ptr<RegularExpression>&& expr, RepeatType type, size_t from = 0, size_t to = 0);

    /// <summary>
    /// Получить повторяемое регулярное выражение.
    /// </summary>
    /// <returns> Повторяемое регулярное выражение. </returns>
    const std::shared_ptr<RegularExpression>& getExpr() const;

    /// <summary>
    /// Получить тип конструкции повторения.
    /// </summary>
    /// <returns> Тип конструкции повторения. </returns>
    RepeatType getType() const;

    size_t getRangeFrom() const;
    size_t getRangeTo() const;

    virtual RegularExpression& operator = (const RegularExpression& other) override;

private:
    /// <summary>
    /// Регулярное выражение, повторяемое в данной конструкции.
    /// </summary>
    std::shared_ptr<RegularExpression> _expr;

    /// <summary>
    /// Тип конструкции повторения.
    /// </summary>
    RepeatType _type;

    /// <summary>
    /// Минимально допустимое число повторений выражения (если специфицировано).
    /// </summary>
    size_t _from;

    /// <summary>
    /// Максимально допустимое число повторений выражения (если специфицировано).
    /// </summary>
    size_t _to;
};

