#pragma once
#include "RegularExpression.h"

/// <summary>
/// —имвольный литерал.
/// </summary>
class Literal :
    public RegularExpression
{
public:
    Literal(char c);

    /// <summary>
    /// ѕолучить символьный литерал дл€ данного экземпл€ра.
    /// </summary>
    /// <returns> —имвольный литерал, описываемый данным экземпл€ром класса. </returns>
    char getChar() const;

private:
    /// <summary>
    /// —имвольный литерал, описываемый данным экземпл€ром класса.
    /// </summary>
    const char _c;
};

