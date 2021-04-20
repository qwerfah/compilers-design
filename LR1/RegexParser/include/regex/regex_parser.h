#pragma once

#include "../../include/regex/regular_expression/regular_expression.h"
#include "../../include/regex/regular_expression/or.h"
#include "../../include/regex/regular_expression/concat.h"
#include "../../include/regex/regular_expression/repeat.h"
#include "../../include/regex/regular_expression/literal.h"

#include <memory>
#include <stdexcept>
#include <stack>
#include <vector>
#include <string>
#include <sstream>

const std::string OPEN_BRACKETS = "([{";
const std::string CLOSE_BRACKETS = ")]}";
const std::string UNARY_QUANTIFIERS = "?*+{";
const std::string BINARY_QUANTIFIERS = "|";

/// <summary>
/// Парсер регулярных выражений.
/// </summary>
class RegexParser
{
public:
	RegexParser() = default;
	RegexParser(const std::string& expression);

	/// <summary>
	/// Публичный метод для вызова _parse, который записывает результат работы в поле _tree.
	/// </summary>
	/// <param name="regex"> Строковое представление регулярного выражения. </param>
	void parse(const std::string& regex);

	const std::shared_ptr<RegularExpression>& getTree() const;

private:
	/// <summary>
	/// Синтаксическое дерево, полученное в результате парсинга регулярного выражения.
	/// </summary>
	std::shared_ptr<RegularExpression> _tree;

	/// <summary>
	/// Строит на основе строкового представления регулярного выражения синтаксическое 
	/// дерево, которое в дальнейшем может быть использовано для построения КА.
	/// </summary>
	/// <param name="regex"> Строковое представление регулярного выражения. </param>
	/// <returns> Синтаксическое дерево. </returns>
	std::shared_ptr<RegularExpression> _parse(const std::string& regex);

	/// <summary>
	/// Рекурсивно парсит регулярное выражение, строя на его основе синтаксическое дерево.
	/// </summary>
	/// <param name="regex"> Регулярное выражение. </param>
	/// <returns> Синтаксическое дерево. </returns>
	std::shared_ptr<RegularExpression> _parseRecur(const std::string& regex);

	/// <summary>
	/// Ищет оператор "|" во входной строке и в случае успеха 
	/// вызывает _parse для левого и правого подвыражения.
	/// </summary>
	/// <param name="regex"> Строковое представление регулярного выражения. </param>
	/// <param name="expr"> Указатель на новое поддерево дерева регулярного выражения, 
	/// которое создается в случае обнаружения искомого оператора. </param>
	/// <returns> true - если оператор найден, false - иначе. </returns>
	bool _tryParseOr(const std::string& regex, std::shared_ptr<RegularExpression>& expr);

	/// <summary>
	/// Ищет конкатенацию во входной строке и в случае успеха 
	/// вызывает _parse для левого и правого подвыражения.
	/// </summary>
	/// <param name="regex"> Строковое представление регулярного выражения. </param>
	/// <param name="expr"> Указатель на новое поддерево дерева регулярного выражения, 
	/// которое создается в случае обнаружения конкатенации. </param>
	/// <returns> true - если найдена конкатенация, false - иначе. </returns>
	bool _tryParseConcat(const std::string& regex, std::shared_ptr<RegularExpression>& expr);

	/// <summary>
	/// Ищет квантификаторы во входной строке и в случае успеха вызывает 
	/// _parse для подвыражения, относящегося к данному квантификатору.
	/// </summary>
	/// <param name="regex"> Строковое представление регулярного выражения. </param>
	/// <param name="expr"> Указатель на новое поддерево дерева регулярного выражения, 
	/// которое создается в случае обнаружения квантификатора. </param>
	/// <returns> true - если квантификатор найден, false - иначе. </returns>
	bool _tryParseQuantifier(const std::string& regex, std::shared_ptr<RegularExpression>& expr);

	/// <summary>
	/// Парсит диапазон вида {m,n}, задающий вырхнюю и нижнюю границы 
	/// числа вхождений подвыражения в квантификаторе повтора.
	/// </summary>
	/// <param name="str"> Строковое представление диапазона. </param>
	/// /// <param name="range"> Ссылка на числовое представление диапазона, 
	/// куда записывается результат в случае успеха. </param>
	/// <returns> true - если удалось сформировать числовой диапазон, false - иначе. </returns>
	std::pair<size_t, size_t> _parseRange(const std::string& str);

	std::vector<std::string> _split(const std::string& str, char delim);

	/// <summary>
	/// Проверяет регулярное выражение на правильность расстановки скобок.
	/// </summary>
	/// <param name="regex"> Регулярное выражение. </param>
	/// <returns> true - если скобки расставлены корректно или отсутствуют, false - иначе. </returns>
	bool _checkBrackets(const std::string& regex);

	/// <summary>
	/// Првоеряет, является ли переданный символ открывающейся скобкой.
	/// </summary>
	/// <param name="ch"> Символ строки. </param>
	/// <returns> true - если ch является открывающейся скобкой, false - иначе. </returns>
	static bool _isIn(char ch, const std::string& str);
};
