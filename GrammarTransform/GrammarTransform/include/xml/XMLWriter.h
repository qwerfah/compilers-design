#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>

#include "../grammar/Grammar.h"
#include "tinyxml2.h"

class XMLWriter
{
public:
	XMLWriter() = default;
	XMLWriter(const std::string& filename);

	void setFilename(const std::string& filename);

	void save(const std::shared_ptr<Grammar>& grammar);

private:
	std::string _filename;
};

