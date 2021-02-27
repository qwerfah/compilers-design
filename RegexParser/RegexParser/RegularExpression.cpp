#include "RegularExpression.h"
#include <stdexcept>

RegularExpression::RegularExpression() : _rawString("")
{ }

RegularExpression::RegularExpression(const std::string& rawString) : _rawString(rawString)
{ }

const std::string& RegularExpression::getRawString() const
{
    return _rawString;
}

RegularExpression& RegularExpression::operator=(const RegularExpression& other)
{
    if (this != &other)
    {
        _rawString = other._rawString;
    }

    return *this;
}
