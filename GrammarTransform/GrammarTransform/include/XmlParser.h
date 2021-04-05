#pragma once

#include <string>
#include <stdexcept>
#include <xmllite.h>

#include "grammar/Grammar.h"

class XmlParser
{
public:
	XmlParser() = default;
	XmlParser(const std::string& filename);

	void setFilename(const std::string& filename);

	Grammar&& parse();

private:
	std::string _filename{};
};

