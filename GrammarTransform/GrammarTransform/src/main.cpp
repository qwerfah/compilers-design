#include <iostream>
#include <memory>

#include "../include/xml/XmlParser.h"
#include "../include/xml/XMLWriter.h"

int main()
{
    XmlParser parser{ "./resources/grammar.xml" };
    XMLWriter writer{ "./resources/new.xml" };

    try
    {
        std::shared_ptr<Grammar> grammar{ parser.parse() };
        grammar->removeRecursion();
        writer.save(grammar);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }

    system("pause");
}