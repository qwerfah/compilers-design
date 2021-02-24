#pragma once
#include "RegularExpression.h"

/// <summary>
/// Парсер регулярных выражений.
/// </summary>
static class RegexParser
{
public:
	/// <summary>
	/// Строит на основе строкового представления регулярного выражения синтаксическое 
	/// дерево, которое в дальнейшем может быть использовано для построения КА.
	/// </summary>
	/// <param name="regex"> Строковое представление регулярного выражения. </param>
	/// <returns> Синтаксическое дерево. </returns>
	RegularExpression parse(const std::string& regex) const;

private:
	RegexParser();
	RegularExpression _parse(std::string& regex) const;
};
