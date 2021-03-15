#pragma once

#include "regular_expression.h"

#include <memory>
#include <string>

const std::string OR_STR = "|";

/// <summary>
/// Описывает конструкцию "|" в регулярном выражении.
/// </summary>
class Or :
    public RegularExpression
{
public:
    Or(std::shared_ptr<RegularExpression>& expr1, std::shared_ptr<RegularExpression>& expr2);
    Or(std::shared_ptr<RegularExpression>&& expr1, std::shared_ptr<RegularExpression>&& expr2);

    /// <summary>
    /// Получить левый операнд конструкции "|".
    /// </summary>
    /// <returns> Левый операнд, представляющий собой регулярное выражение. </returns>
    const std::shared_ptr<RegularExpression>& getLeftExpr() const;

    /// <summary>
    /// Получить правый операнд конструкции "|".
    /// </summary>
    /// <returns> Правый операнд, представляющий собой регулярное выражение. </returns>
    const std::shared_ptr<RegularExpression>& getRightExpr() const;

    virtual RegularExpression& operator = (const RegularExpression& other) override;


private:
    /// <summary>
    /// Левый операнд конструкции "|".
    /// </summary>
    std::shared_ptr<RegularExpression> _leftExpr;

    /// <summary>
    /// Правый операнд конструкции "|".
    /// </summary>
    std::shared_ptr<RegularExpression> _rightExpr;
};

