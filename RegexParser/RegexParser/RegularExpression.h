#pragma once
#include <string>

/// <summary>
/// Абстрактный класс для произвольной окнструкции регулярного выражения.
/// </summary>
class RegularExpression
{
public:
	RegularExpression();
	RegularExpression(const std::string& rawString);

	/// <summary>
	/// Получить строковое представление регулярного выражения.
	/// </summary>
	/// <returns> Строковое представление. </returns>
	const std::string& getRawString() const;

	virtual RegularExpression& operator = (const RegularExpression& other);

protected:
	/// <summary>
	/// Строковое представление конструкции регулярного выражения.
	/// </summary>
	std::string _rawString;
};

