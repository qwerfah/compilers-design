#pragma once

#define REPEAT_STR "*"

#include "RegularExpression.h"

/// <summary>
/// ќписывает регул€рное выражение "*", предполагающее 
/// произвольное число повторений указанной конструкции.
/// </summary>
class Repeat :
    public RegularExpression
{
public:
    Repeat(const RegularExpression& expr);

    /// <summary>
    /// ѕолучить повтор€емое регул€рное выражение.
    /// </summary>
    /// <returns> ѕовтор€емое регул€рное выражение. </returns>
    const  RegularExpression& getExpr() const;

private:
    /// <summary>
    /// –егул€рное выражение, повтор€емое в данной конструкции.
    /// </summary>
    const RegularExpression& _expr;
};

