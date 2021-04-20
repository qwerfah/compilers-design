#include "../../include/XML/xml_parser.h"

XmlParser::XmlParser(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument{ "Empty file name." };
	}

	_filename = filename;
}

void XmlParser::setFilename(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument{ "Empty file name." };
	}

	_filename = filename;
}

grammar_ptr XmlParser::parse()
{
	using namespace tinyxml2;

	if (_filename.empty())
	{
		throw std::invalid_argument("Empty file name.");
	}

	XMLDocument doc;
	grammar_ptr grammar{ new Grammar{} };
	doc.LoadFile(_filename.c_str());
	XMLElement* root{ doc.FirstChildElement("grammar") };

	// Загружаем терминалы
	for (XMLElement* element =
		root->FirstChildElement("terminalsymbols")->FirstChildElement("term");
		element; element = element->NextSiblingElement("term"))
	{
		
		grammar->terminals.push_back(symbol_ptr{ 
			new Symbol{ element->FindAttribute("name")->Value(),
				element->FindAttribute("spell")->Value(), SymbolType::Terminal } });
	}

	// Загружаем нетерминалы
	for (XMLElement* element = 
		root->FirstChildElement("nonterminalsymbols")->FirstChildElement("nonterm");
		element; element = element->NextSiblingElement("nonterm"))
	{

		grammar->nonTerminals.push_back(symbol_ptr{ 
			new Symbol{ element->FindAttribute("name")->Value() } });
	}

	// Загружаем правила
	for (XMLElement* element = 
		root->FirstChildElement("productions")->FirstChildElement("production");
		element; element = element->NextSiblingElement("production"))
	{
		symbol_vector left{}, right{};
		XMLElement* lhs = element->FirstChildElement("lhs");
		// Левая часть правила
		left.push_back(grammar->getSymbol(lhs->FindAttribute("name")->Value()));
		// Правая часть правила
		for (XMLElement* rhs = 
			element->FirstChildElement("rhs")->FirstChildElement("symbol"); 
			rhs; rhs = rhs->NextSiblingElement("symbol"))
		{
			right.push_back(grammar->getSymbol(rhs->FindAttribute("name")->Value()));
		}

		grammar->rules.push_back(rule_ptr{ new Rule{ left, right } });
	}

	// Загружаем аксиому
	std::string name = root->FirstChildElement("startsymbol")->FindAttribute("name")->Value();
	grammar->axiom = grammar->getSymbol(name);

	return grammar;
}
