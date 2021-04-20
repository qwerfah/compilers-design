#pragma once

#include <iostream>

#include "../grammar/Grammar.h"
#include "tinyxml2.h"

/// <summary>
/// Grammar writer to XML file in specified format.
/// </summary>
class XmlWriter
{
public:
	XmlWriter() = default;
	XmlWriter(const std::string& filename);

	/// <summary>
	/// Set XML file name to save grammar.
	/// </summary>
	/// <param name="filename"></param>
	void setFilename(const std::string& filename);

	/// <summary>
	/// Serialize grammar to XML and save to XML file.
	/// </summary>
	/// <param name="grammar"> Grammar to serialize. </param>
	void save(const grammar_ptr& grammar);

private:
	/// <summary>
	/// XML file name.
	/// </summary>
	std::string _filename;
};

