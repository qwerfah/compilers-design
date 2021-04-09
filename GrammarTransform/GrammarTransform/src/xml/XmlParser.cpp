#include "../../include/XML/XmlParser.h"

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

std::shared_ptr<Grammar> XmlParser::parse()
{
	using namespace tinyxml2;

	if (_filename.empty())
	{
		throw std::invalid_argument("Empty file name.");
	}

	XMLDocument doc;
	std::shared_ptr<Grammar> grammar{ new Grammar{} };
	doc.LoadFile(_filename.c_str());
	XMLElement* root = doc.FirstChildElement("grammar");

	// Загружаем терминалы
	for (XMLElement* element = 
		root->FirstChildElement("terminalsymbols")->FirstChildElement("term");
		element; element = element->NextSiblingElement("term"))
	{
		
		grammar->addTerminal(std::shared_ptr<Symbol>{ 
			new Symbol{ element->FindAttribute("name")->Value(),
				element->FindAttribute("spell")->Value(), SymbolType::Terminal } });
	}

	// Загружаем нетерминалы
	for (XMLElement* element = 
		root->FirstChildElement("nonterminalsymbols")->FirstChildElement("nonterm");
		element; element = element->NextSiblingElement("nonterm"))
	{

		grammar->addNonTerminal(std::shared_ptr<Symbol>{ 
			new Symbol{ element->FindAttribute("name")->Value() } });
	}

	// Загружаем правила
	for (XMLElement* element = 
		root->FirstChildElement("productions")->FirstChildElement("production");
		element; element = element->NextSiblingElement("production"))
	{
		std::vector<std::shared_ptr<Symbol>> left{}, right{};
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

		grammar->addRule(std::shared_ptr<Rule>{ new Rule{ left, right } });
	}

	// Загружаем аксиому
	std::string name = root->FirstChildElement("startsymbol")->FindAttribute("name")->Value();
	grammar->setAxiom(grammar->getSymbol(name));

	return grammar;
}
