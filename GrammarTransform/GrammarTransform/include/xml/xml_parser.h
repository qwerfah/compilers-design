#pragma once

#include <string>
#include <stdexcept>
#include <memory>

#include "../grammar/Grammar.h"
#include "tinyxml2.h"

class XmlParser
{
public:
	XmlParser() = default;
	XmlParser(const std::string& filename);

	void setFilename(const std::string& filename);

	std::shared_ptr<Grammar> parse();

private:
	std::string _filename{};
};

