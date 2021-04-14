#include "..\..\include\xml\xml_writer.h"

XmlWriter::XmlWriter(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument{ "File name is empty." };
	}

	_filename = filename;
}

void XmlWriter::setFilename(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument{ "File name is empty." };
	}

	_filename = filename;
}

void XmlWriter::save(const grammar_ptr& grammar)
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

	// ��������� ������� �������
	XMLDocument doc;
	XMLElement* root = doc.NewElement("grammar");
	doc.InsertFirstChild(root);
	root->SetAttribute("name", "G0");

	// ��������� ���������
	XMLElement* terminals = root->InsertNewChildElement("terminalsymbols");
	for (auto& s : grammar->terminals)
	{
		XMLElement* term = terminals->InsertNewChildElement("term");
		term->SetAttribute("name", s->getName().c_str());
		term->SetAttribute("spell", s->getSpell().c_str());
	}

	// ��������� �����������
	XMLElement* nonTerminals = root->InsertNewChildElement("nonterminalsymbols");
	for (auto& s : grammar->nonTerminals)
	{
		XMLElement* nonTerm = nonTerminals->InsertNewChildElement("nonterm");
		nonTerm->SetAttribute("name", s->getName().c_str());
	}

	// ��������� �������
	XMLElement* rules = root->InsertNewChildElement("productions");
	for (auto& rule : grammar->rules)
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

	// ��������� �������
	root->InsertNewChildElement("startsymbol")
		->SetAttribute("name", grammar->axiom->getName().c_str());

	doc.SaveFile(_filename.c_str());
}
