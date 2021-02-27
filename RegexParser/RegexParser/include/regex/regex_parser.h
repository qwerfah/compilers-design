#pragma once

#define OPEN_BRACKETS "([{"
#define CLOSE_BRACKETS ")]}"
#define UNARY_QUANTIFIERS "?*+"
#define BINARY_QUANTIFIERS "|"

#include "../../include/regex/regular_expression/regular_expression.h"
#include "../../include/regex/regular_expression/or.h"
#include "../../include/regex/regular_expression/concat.h"
#include "../../include/regex/regular_expression/repeat.h"
#include "../../include/regex/regular_expression/literal.h"

#include <memory>
#include <stdexcept>
#include <stack>

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
	static std::shared_ptr<RegularExpression> parse(const std::string& regex);

private:
	RegexParser();

	/// <summary>
	/// Рекурсивно парсит регулярное выражение, строя на его основе синтаксическое дерево.
	/// </summary>
	/// <param name="regex"> Регулярное выражение. </param>
	/// <returns> Синтаксическое дерево. </returns>
	static std::shared_ptr<RegularExpression> _parse(std::string&& regex);

	static bool _tryFindOr(std::string& regex, std::shared_ptr<RegularExpression>& expr);

	static bool _tryFindConcat(std::string& regex, std::shared_ptr<RegularExpression>& expr);

	static bool _tryFindQuantifier(std::string& regex, std::shared_ptr<RegularExpression>& expr);

	/// <summary>
	/// Проверяет регулярное выражение на правильность расстановки скобок.
	/// </summary>
	/// <param name="regex"> Регулярное выражение. </param>
	/// <returns> true - если скобки расставлены корректно или отсутствуют, false - иначе. </returns>
	static bool _checkBrackets(const std::string& regex);

	/// <summary>
	/// Првоеряет, является ли переданный символ открывающейся скобкой.
	/// </summary>
	/// <param name="ch"> Символ строки. </param>
	/// <returns> true - если ch является открывающейся скобкой, false - иначе. </returns>
	static bool _isOpenBracket(char ch);

	/// <summary>
	/// Првоеряет, является ли переданный символ закрывающейся скобкой.
	/// </summary>
	/// <param name="ch"> Символ строки. </param>
	/// <returns> true - если ch является закрывающейся скобкой, false - иначе. </returns>
	static bool _isCloseBracket(char ch);

	/// <summary>
	/// Првоеряет, является ли переданный символ унарным квантификатором.
	/// </summary>
	/// <param name="ch"> Символ строки. </param>
	/// <returns> true - если ch является унарным квантификатором, false - иначе. </returns>
	static bool _isUnaryQuantifier(char ch);

	/// <summary>
	/// Првоеряет, является ли переданный символ бинарным квантификатором.
	/// </summary>
	/// <param name="ch"> Символ строки. </param>
	/// <returns> true - если ch является бинарным квантификатором, false - иначе. </returns>
	static bool _isBinaryQuantifier(char ch);

	/// <summary>
	/// Првоеряет, является ли переданный символ квантификатором.
	/// </summary>
	/// <param name="ch"> Символ строки. </param>
	/// <returns> true - если ch является квантификатором, false - иначе. </returns>
	static bool _isQuantifier(char ch);
};
