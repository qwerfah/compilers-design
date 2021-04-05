#include "../include/XmlParser.h"

XmlParser::XmlParser(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument("Empty file name.");
	}

	_filename = filename;
}

void XmlParser::setFilename(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument("Empty file name.");
	}

	_filename = filename;
}

Grammar&& XmlParser::parse()
{
	return Grammar && ();
}
