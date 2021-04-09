#include "..\..\include\xml\XMLWriter.h"

XMLWriter::XMLWriter(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument{ "File name is empty." };
	}

	_filename = filename;
}

void XMLWriter::setFilename(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument{ "File name is empty." };
	}

	_filename = filename;
}

void XMLWriter::save(const std::shared_ptr<Grammar>& grammar)
{
	using namespace tinyxml2;

	if (!grammar)
	{
		throw std::invalid_argument("Null pointer to grammar.");
	}

	if (_filename.empty())
	{
		throw std::invalid_argument{ "File name is empty." };
	}

	// Добавляем коревой элемент
	XMLDocument doc;
	XMLElement* root = doc.NewElement("grammar");
	doc.InsertFirstChild(root);
	root->SetAttribute("name", "G0");

	// Добавляем терминалы
	XMLElement* terminals = root->InsertNewChildElement("terminalsymbols");
	for (auto& s : grammar->getTerminals())
	{
		XMLElement* term = terminals->InsertNewChildElement("term");
		term->SetAttribute("name", s->getName().c_str());
		term->SetAttribute("spell", s->getSpell().c_str());
	}

	// Добавляем нетерминалы
	XMLElement* nonTerminals = root->InsertNewChildElement("nonterminalsymbols");
	for (auto& s : grammar->getNonTerminals())
	{
		XMLElement* nonTerm = nonTerminals->InsertNewChildElement("nonterm");
		nonTerm->SetAttribute("name", s->getName().c_str());
	}

	// Добавляем правила
	XMLElement* rules = root->InsertNewChildElement("productions");
	for (auto& rule : grammar->getRules())
	{
		XMLElement* prod = rules->InsertNewChildElement("production");
		prod->InsertNewChildElement("lhs")
			->SetAttribute("name", rule->getLeft()[0]->getName().c_str());
		XMLElement* rhs = prod->InsertNewChildElement("rhs");

		for (auto& s : rule->getRight())
		{
			XMLElement* symbol = rhs->InsertNewChildElement("symbol");
			SymbolTypeToString convertor{};
			symbol->SetAttribute("type", convertor.convert(s->getType()).c_str());
			symbol->SetAttribute("name", s->getName().c_str());
		}
	}

	// Добавляем аксиому
	root->InsertNewChildElement("startsymbol")
		->SetAttribute("name", grammar->getAxiom()->getName().c_str());

	std::cout << doc.SaveFile(_filename.c_str());
}
