#pragma once

#define NON_ZERO_REPEAT_STR "+"

#include "RegularExpression.h"

/// <summary>
/// ќписывает конструкцию "+", декларирующую произвольное 
/// ненулевое число повторений некоторого регул€рного выражени€.
/// </summary>
class NonZeroRepeat :
    public RegularExpression
{
public:
    NonZeroRepeat(const RegularExpression& expr);

    /// <summary>
    /// ѕолучить регул€рное выражение, повтор€емое в рамках данной конструкции.
    /// </summary>
    /// <returns> ѕовтор€емое регул€рное выражение. </returns>
    const RegularExpression& getExpr() const;

private:
    /// <summary>
    /// –егул€рное выражение, повтор€емое в рамках данной конструкции.
    /// </summary>
    const RegularExpression& _expr;

};

