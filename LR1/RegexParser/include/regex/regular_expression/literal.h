#pragma once

#include "regular_expression.h"
#include "../../enums.h"

#include <string>

/// <summary>
/// Символьный литерал.
/// </summary>
class Literal :
    public RegularExpression
{
public:
    Literal(char c, LiteralType type);

    /// <summary>
    /// Получить символьный литерал для данного экземпляра.
    /// </summary>
    /// <returns> Символьный литерал, описываемый данным экземпляром класса. </returns>
    char getChar() const;

    /// <summary>
    /// Получить тип данного литерала.
    /// </summary>
    /// <returns> Тип литерала. </returns>
    LiteralType getType() const;

private:
    /// <summary>
    /// Символьный литерал, описываемый данным экземпляром класса.
    /// </summary>
    char _c;

    /// <summary>
    /// Тип литерала.
    /// </summary>
    LiteralType _type;
};

