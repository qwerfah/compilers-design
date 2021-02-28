#include "../../include/regex/regex_parser.h"

std::shared_ptr<RegularExpression> RegexParser::parse(const std::string& regex)
{
	if (!_checkBrackets(regex))
	{
		throw std::invalid_argument("Incorrect brackets placement.");
	}

	return _parse(regex);
}

std::shared_ptr<RegularExpression> RegexParser::_parse(const std::string& regex)
{
	// Если входная строка пуста, возвращаем пустой литерал.
	if (regex.empty())
	{
		return std::shared_ptr<RegularExpression>(new Literal(0, LiteralType::Empty));
	}

	bool found = false;
	std::shared_ptr<RegularExpression> expr;

	// Парсим в порядке приоритета сначала "или", затем следование и унарные квантификаторы.
	if (_tryParseOr(regex, expr)) return expr;
	if (_tryParseConcat(regex, expr)) return expr;
	if (_tryParseQuantifier(regex, expr)) return expr;

	// Если входное выражение заключено в скобки, удаляем их.
	if (_isIn(*regex.begin(), OPEN_BRACKETS) && _isIn(*regex.rbegin(), CLOSE_BRACKETS))
	{
		return _parse(regex.substr(1, regex.length() - 2));
	}

	// Если оставшееся выражение - не единственный символ, это ошибка.
	if (regex.length() != 1)
	{
		throw std::logic_error("Can't parse regular expression, unexpected string length.");
	}

	// Парсим литерал или произвольный символ.
	return regex[0] == '.' 
		? std::shared_ptr<RegularExpression>(new Literal('.', LiteralType::Any))
		: std::shared_ptr<RegularExpression>(new Literal(regex[0], LiteralType::Symbol));
}

bool RegexParser::_tryParseOr(const std::string& regex, std::shared_ptr<RegularExpression>& expr)
{
	auto stack = std::stack<char>();

	for (size_t i = 0; i < regex.length(); i++)
	{
		if (_isIn(regex[i], OPEN_BRACKETS))
		{
			stack.push(regex[i]);
		}
		else if (_isIn(regex[i], CLOSE_BRACKETS))
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

bool RegexParser::_tryParseConcat(const std::string& regex, std::shared_ptr<RegularExpression>& expr)
{
	if (regex.length() < 2) return false;

	auto stack = std::stack<char>();

	for (size_t i = 0; i < regex.length(); i++)
	{
		
		if (i > 0 && stack.empty() 
			&& !_isIn(regex[i], UNARY_QUANTIFIERS + BINARY_QUANTIFIERS)
			&& !_isIn(regex[i - 1], BINARY_QUANTIFIERS))
		{
			expr = std::shared_ptr<Concat>(
				new Concat(_parse(regex.substr(0, i)), _parse(regex.substr(i))));
			return true;
		}
		else if (_isIn(regex[i], OPEN_BRACKETS))
		{
			stack.push(regex[i]);
		}
		else if (_isIn(regex[i], CLOSE_BRACKETS))
		{
			stack.pop();
		}
	}

	return false;
}

bool RegexParser::_tryParseQuantifier(const std::string& regex, std::shared_ptr<RegularExpression>& expr)
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
	case '}':
		std::pair<size_t, size_t> range = _parseRange(regex.substr(regex.find('{')));
		expr = std::shared_ptr<Repeat>(
			new Repeat(_parse(regex.substr(0, regex.find('{'))),
				RepeatType::Range, range.first, range.second));
		return true;
	}

	return false;
}

std::pair<size_t, size_t> RegexParser::_parseRange(const std::string& str)
{
	if (!_isIn(*str.begin(), OPEN_BRACKETS) || !_isIn(*str.rbegin(), CLOSE_BRACKETS))
	{
		throw std::invalid_argument("Invalid repeat range representation.");
	}

	std::vector<std::string> strings = _split(str.substr(1, str.length() - 2), ',');

	if (strings.size() != 2)
	{
		throw std::invalid_argument("Invalid repeat range representation.");
	}

	std::pair<size_t, size_t> range;

	try
	{
		range.first = std::stoi(strings[0]);
		range.second = std::stoi(strings[1]);
	}
	catch (std::exception e)
	{
		throw std::invalid_argument("Invalid repeat range representation.");
	}

	return range;
}

std::vector<std::string> RegexParser::_split(const std::string& str, char delim)
{
	std::stringstream strStream(str);
	std::string item;
	std::vector<std::string> elems;

	while (std::getline(strStream, item, delim)) 
	{
		elems.push_back(item);
	}

	return elems;
}

bool RegexParser::_checkBrackets(const std::string& regex)
{
	auto stack = std::stack<char>();

	for (auto ch : regex)
	{
		if (_isIn(ch, OPEN_BRACKETS))
		{
			stack.push(ch);
		}
		else if (_isIn(ch, CLOSE_BRACKETS))
		{
			if (OPEN_BRACKETS.find(stack.top()) == CLOSE_BRACKETS.find(ch))
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

bool RegexParser::_isIn(char ch, const std::string& str)
{
	return str.find(ch) != std::string::npos;
}