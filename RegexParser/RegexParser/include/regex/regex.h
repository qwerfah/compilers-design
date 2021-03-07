#pragma once

#include "../../include/finite_state_machine/finite_state_machine.h"
#include "../../include/regex/regular_expression/regular_expression.h"
#include "../../include/regex/regular_expression/or.h"
#include "../../include/regex/regular_expression/repeat.h"
#include "../../include/regex/regular_expression/concat.h"
#include "../../include/regex/regular_expression/literal.h"
#include "../../include/regex/regex_parser.h"

#include <string>
#include <memory>
#include <stdexcept>

class Regex
{
public:
	Regex(const std::string& expression);

	/// <summary>
	/// Проверить строку на соответствие регулярному выражению, реализуемому данным экземпляром.
	/// </summary>
	/// <param name="chain"> Входная цепочка. </param>
	/// <returns> true - если строка соответсвует регулярному выражению 
	/// (входная цепочка порождается грамматикой, соответсвующей данному КА), false - иначе. </returns>
	bool match(const std::string& chain);

	/// <summary>
	/// Построить и сохранить НКА, соответсвующий 
	/// переданному строковому представлению регулярного выражения.
	/// </summary>
	/// <param name="expression"> Строковое представление регулярного выражения. </param>
	void buildFSM(const std::string& expression);

private:
	/// <summary>
	/// Текущий парсер для последнего регулярного выражения, переданного в функцию buildFSM или конструктор. 
	/// </summary>
	std::shared_ptr<RegexParser> _parser;

	/// <summary>
	/// Текущий КА для последнего регулярного выражения, переданного в функцию buildFSM или конструктор.
	/// </summary>
	std::shared_ptr<FiniteStateMachine> _machine;

	void _buildFSM(const std::string& expression);

	/// <summary>
	/// Построить НКА, соответсвующий регулярному выражению, представленному в виде синтаксического дерева.
	/// </summary>
	/// <param name="expr"> Синтаксическое дерево регулярного выражения. </param>
	/// <returns> Указатель на построенный КА. </returns>
	std::shared_ptr<FiniteStateMachine> _buildFSMRecur(const std::shared_ptr<RegularExpression>& expr);

	/// <summary>
	/// Построить НКА для конструкции "или" регулярного выражения.
	/// </summary>
	/// <param name="expr"> Регулярное выражение. </param>
	/// <returns> Указатель на построенный КА. </returns>
	std::shared_ptr<FiniteStateMachine> _buildOr(const std::shared_ptr<Or>& expr);

	/// <summary>
	/// Построить НКА для конкатенации двух подвыражений регулярного выражения.
	/// </summary>
	/// <param name="expr"> Регулярное выражение. </param>
	/// <returns> Указатель на построенный КА. </returns>
	std::shared_ptr<FiniteStateMachine> _buildConcat(const std::shared_ptr<Concat>& expr);

	/// <summary>
	/// Построить НКА для конструкции "*".
	/// </summary>
	/// <param name="expr"> Регулярное выражение. </param>
	/// <returns> Указатель на построенный КА. </returns>
	std::shared_ptr<FiniteStateMachine> _buildArbitraryRepeat(const std::shared_ptr<Repeat>& expr);

	/// <summary>
	/// Построить НКА для конструкции "+".
	/// </summary>
	/// <param name="expr"> Регулярное выражение. </param>
	/// <returns> Указатель на построенный КА. </returns>
	std::shared_ptr<FiniteStateMachine> _buildNonZeroRepeat(const std::shared_ptr<Repeat>& expr);

	/// <summary>
	/// Построить НКА для конструкции "?".
	/// </summary>
	/// <param name="expr"> Регулярное выражение. </param>
	/// <returns> Указатель на построенный КА. </returns>
	std::shared_ptr<FiniteStateMachine> _buildNonOrSingle(const std::shared_ptr<Repeat>& expr);

	/// <summary>
	/// Построить НКА для конструкции "{}".
	/// </summary>
	/// <param name="expr"> Регулярное выражение. </param>
	/// <returns> Указатель на построенный КА. </returns>
	std::shared_ptr<FiniteStateMachine> _buildRangeRepeat(const std::shared_ptr<Repeat>& expr);

	/// <summary>
	/// Построить НКА для заданного символьного литерала регулярного выражения.
	/// </summary>
	/// <param name="expr"> Регулярное выражение. </param>
	/// <returns> Указатель на построенный КА. </returns>
	std::shared_ptr<FiniteStateMachine> _buildSymbolLiteral(const std::shared_ptr<Literal>& expr);

	/// <summary>
	/// Построить НКА для пустого символьного литерала регулярного выражения.
	/// </summary>
	/// <param name="expr"> Регулярное выражение. </param>
	/// <returns> Указатель на построенный КА. </returns>
	std::shared_ptr<FiniteStateMachine> _buildEmptyLiteral(const std::shared_ptr<Literal>& expr);
};