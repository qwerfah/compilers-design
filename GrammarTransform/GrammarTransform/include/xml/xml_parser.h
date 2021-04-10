#pragma once

#include <string>
#include <stdexcept>
#include <memory>

#include "../grammar/Grammar.h"
#include "tinyxml2.h"

/// <summary>
/// Grammar parser from XML file.
/// </summary>
class XmlParser
{
public:
	XmlParser() = default;
	XmlParser(const std::string& filename);
	
	/// <summary>
	/// Set XML file name to parse grammar.
	/// </summary>
	/// <param name="filename"> XML file name. </param>
	void setFilename(const std::string& filename);

	/// <summary>
	/// Parse grammar from XML file.
	/// </summary>
	/// <returns> Object representation for grammar from XML file. </returns>
	std::shared_ptr<Grammar> parse();

private:
	/// <summary>
	/// XML file name.
	/// </summary>
	std::string _filename{};
};

