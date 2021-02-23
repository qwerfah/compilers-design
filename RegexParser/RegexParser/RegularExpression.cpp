#include "RegularExpression.h"
#include <stdexcept>

RegularExpression::RegularExpression(const std::string& rawString) : _rawString(rawString)
{ }

const std::string& RegularExpression::getRawString() const
{
    return _rawString;
}
