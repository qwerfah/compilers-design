#pragma once

#include <iostream>

#include "../grammar/Grammar.h"

/// <summary>
/// Grammar writer to file in ANTLR G4 format.
/// </summary>
class AntlrWriter
{
public:
	AntlrWriter() = default;
	AntlrWriter(const std::string & filename);

	/// <summary>
	/// Set G4 file name to save grammar.
	/// </summary>
	/// <param name="filename"></param>
	void setFilename(const std::string& filename);

	/// <summary>
	/// Serialize grammar to G4 and save to file.
	/// </summary>
	/// <param name="grammar"> Grammar to serialize. </param>
	void save(const grammar_ptr& grammar);

private:
	/// <summary>
	/// G4 file name.
	/// </summary>
	std::string _filename;
};

