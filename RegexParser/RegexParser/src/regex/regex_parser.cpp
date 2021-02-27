#include "../../include/regex/regex_parser.h"

std::shared_ptr<RegularExpression> RegexParser::parse(const std::string& regex)
{
	if (!_checkBrackets(regex))
	{
		throw std::invalid_argument("Incorrect brackets placement.");
	}

	return _parse(regex.substr());
}

std::shared_ptr<RegularExpression> RegexParser::_parse(std::string&& regex)
{
	// Если входная строка пуста, возвращаем пустой литерал.
	if (regex.empty())
	{
		return std::shared_ptr<RegularExpression>(new Literal(0, LiteralType::Empty));
	}

	bool found = false;
	std::shared_ptr<RegularExpression> expr;

	// Парсим в порядке приоритета сначала "или", затем следование и унарные квантификаторы.
	if (_tryFindOr(regex, expr)) return expr;
	if (_tryFindConcat(regex, expr)) return expr;
	if (_tryFindQuantifier(regex, expr)) return expr;

	// Если входное выражение заключено в скобки, удаляем их.
	if (_isOpenBracket(*regex.begin()) && _isCloseBracket(*regex.rbegin()))
	{
		return _parse(regex.substr(1, regex.length() - 2));
	}

	// Если оставшееся выражение - не единственный символ, это ошибка.
	if (regex.length() != 1)
	{
		throw std::logic_error("Can't parse regular expression, unexprected string length.");
	}

	// Парсим литерал или произвольный символ.
	return regex[0] == '.' 
		? std::shared_ptr<RegularExpression>(new Literal('.', LiteralType::Any))
		: std::shared_ptr<RegularExpression>(new Literal(regex[0], LiteralType::Symbol));
}

bool RegexParser::_tryFindOr(std::string& regex, std::shared_ptr<RegularExpression>& expr)
{
	auto stack = std::stack<char>();

	for (size_t i = 0; i < regex.length(); i++)
	{
		if (_isOpenBracket(regex[i]))
		{
			stack.push(regex[i]);
		}
		else if (_isCloseBracket(regex[i]))
		{
			stack.pop();
		}
		else if (regex[i] == '|' && stack.empty())
		{
			expr = std::shared_ptr<Or>(
				new Or(_parse(regex.substr(0, i)), _parse(regex.substr(i + 1))));
			return true;
		}
	}

	return false;
}

bool RegexParser::_tryFindConcat(std::string& regex, std::shared_ptr<RegularExpression>& expr)
{
	if (regex.length() < 2) return false;

	auto stack = std::stack<char>();

	for (size_t i = 0; i < regex.length(); i++)
	{
		
		if (i > 0 && stack.empty() 
			&& !_isQuantifier(regex[i]) 
			&& !_isBinaryQuantifier(regex[i - 1]))
		{
			expr = std::shared_ptr<Concat>(
				new Concat(_parse(regex.substr(0, i)), _parse(regex.substr(i))));
			return true;
		}
		else if (_isOpenBracket(regex[i]))
		{
			stack.push(regex[i]);
		}
		else if (_isCloseBracket(regex[i]))
		{
			stack.pop();
		}
	}

	return false;
}

bool RegexParser::_tryFindQuantifier(std::string& regex, std::shared_ptr<RegularExpression>& expr)
{
	if (regex.empty())
	{
		throw std::invalid_argument("Empty regex string.");
	}

	switch (*regex.rbegin())
	{
	case '*':
		expr = std::shared_ptr<Repeat>(
			new Repeat(_parse(regex.substr(0, regex.length() - 1)), RepeatType::Arbitrary));
		return true;
	case '+':
		expr = std::shared_ptr<Repeat>(
			new Repeat(_parse(regex.substr(0, regex.length() - 1)), RepeatType::NonZero));
		return true;
	case '?':
		expr = std::shared_ptr<Repeat>(
			new Repeat(_parse(regex.substr(0, regex.length() - 1)), RepeatType::NoneOrSingle));
		return true;
	}

	return false;
}

bool RegexParser::_checkBrackets(const std::string& regex)
{
	auto stack = std::stack<char>();

	for (auto ch : regex)
	{
		if (_isOpenBracket(ch))
		{
			stack.push(ch);
		}
		else if (_isCloseBracket(ch))
		{
			if (stack.top() == ch - 1)
			{
				stack.pop();
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

bool RegexParser::_isOpenBracket(char ch)
{
	return std::string(OPEN_BRACKETS).find(ch) != std::string::npos;
}

bool RegexParser::_isCloseBracket(char ch)
{
	return std::string(CLOSE_BRACKETS).find(ch) != std::string::npos;
}

bool RegexParser::_isUnaryQuantifier(char ch)
{
	return std::string(UNARY_QUANTIFIERS).find(ch) != std::string::npos;
}

bool RegexParser::_isBinaryQuantifier(char ch)
{
	return std::string(BINARY_QUANTIFIERS).find(ch) != std::string::npos;
}

bool RegexParser::_isQuantifier(char ch)
{
	return _isUnaryQuantifier(ch) || _isBinaryQuantifier(ch);
}
