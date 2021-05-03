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

	std::ofstream file{};

	file.open(_filename);

	if (file.is_open())
	{
		file << "grammar G1";

		for (auto& symbol : grammar->nonTerminals)
		{
			rule_vector rules{};

			std::copy_if(grammar->rules.begin(), grammar->rules.end(), 
				std::back_inserter(rules), [&](auto& rule)
				{
					return *rule->getLeft().begin() == symbol;
				});

			file << symbol->getName() << " : " << std::endl;

			for (size_t i = 0; i < rules.size(); i++)
			{
				if (i)
				{
					file << "| " << std::endl;
				}

				file << "  ";

				for (auto& s : rules[i]->getRight())
				{
					file << s->getName() << " ";
				}
			}

			file << ";" << std::endl << std::endl;
		}
	}

	file.close();
}
