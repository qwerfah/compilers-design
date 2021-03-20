#pragma once

#include "regex/regular_expression/regular_expression.h"
#include "regex/regex.h"

#include <memory>
#include <exception>
#include <iostream>

class Interface
{
public:
	Interface() = default;

	void loop();
	
	const std::shared_ptr<Regex>& getRegex() const;

	void printTree(const std::shared_ptr<RegularExpression>& tree, std::string&& tabs = "");

	static bool isDebugOn();

private:
	std::shared_ptr<Regex> _regex;
	static bool _isDebugOn;

	void _printMenu() const;

	void _setRegularExpression();

	void _matchRegularExpression();
};