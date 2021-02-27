#pragma once

#define REPEAT_STR "*"

#include "RegularExpression.h"
#include "enums.h"

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
    Repeat(std::shared_ptr<RegularExpression>&& expr, RepeatType type);

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
};

