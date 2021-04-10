#include <iostream>
#include <memory>

#include "../include/xml/xml_parser.h"
#include "../include/xml/xml_writer.h"
#include "../include/grammar_transform/grammar_transform.h"

int main()
{
    XmlParser parser{ "./resources/grammar.xml" };
    XmlWriter writer{ "./resources/new.xml" };

    try
    {
        std::shared_ptr<Grammar> grammar{ parser.parse() };
        (*grammar->algorithms["leftRecursionRemove"])();
        writer.save(grammar);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }

    system("pause");
}