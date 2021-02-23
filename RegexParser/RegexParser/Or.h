#pragma once

#define OR_STR "|"

#include "RegularExpression.h"

/// <summary>
/// Описывает конструкцию "|" в регулярном выражении.
/// </summary>
class Or :
    public RegularExpression
{
public:
    Or(const RegularExpression& expr1, const RegularExpression& expr2);

    /// <summary>
    /// Получить левый операнд конструкции "|".
    /// </summary>
    /// <returns> Левый операнд, представляющий собой регулярное выражение. </returns>
    const RegularExpression& getLeftExpr() const;

    /// <summary>
    /// Получить правый операнд конструкции "|".
    /// </summary>
    /// <returns> Правый операнд, представляющий собой регулярное выражение. </returns>
    const RegularExpression& getRightExpr() const;

private:
    /// <summary>
    /// Левый операнд конструкции "|".
    /// </summary>
    const RegularExpression& _leftExpr;

    /// <summary>
    /// Правый операнд конструкции "|".
    /// </summary>
    const RegularExpression& _rightExpr;
};

