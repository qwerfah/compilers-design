#pragma once
#include <string>

/// <summary>
/// Абстрактный класс для произвольной окнструкции регулярного выражения.
/// </summary>
class RegularExpression
{
public:
	RegularExpression(const std::string& rawString);

	/// <summary>
	/// Получить строковое представление регулярного выражения.
	/// </summary>
	/// <returns> Строковое представление. </returns>
	const std::string& getRawString() const;

protected:
	/// <summary>
	/// Строковое представление конструкции регулярного выражения.
	/// </summary>
	const std::string _rawString;
};

