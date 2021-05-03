#include "../../include/xml/antlr_writer.h"

AntlrWriter::AntlrWriter(const std::string& filename) : AntlrWriter()
{
	if (filename.empty())
	{
		throw std::invalid_argument{ "Invalid filename." };
	}

	_filename = filename;
}

void AntlrWriter::setFilename(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument{ "Invalid filename." };
	}

	_filename = filename;
}

void AntlrWriter::save(const grammar_ptr& grammar)
{
	if (!grammar)
	{
		throw std::invalid_argument("Null pointer to grammar.");
	}

	if (_filename.empty())
	{
		throw std::invalid_argument{ "File name is empty." };
	}


}
