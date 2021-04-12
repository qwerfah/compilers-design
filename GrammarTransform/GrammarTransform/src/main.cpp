#include <iostream>
#include <memory>

#include "../include/xml/xml_parser.h"
#include "../include/xml/xml_writer.h"
#include "../include/grammar_transform/grammar_transform.h"


template<typename TArg1, typename TArg2>
bool func(TArg1 arg1, TArg2 arg2)
{
    return arg1 > arg2;
}

using temp = std::vector<int>;

int main()
{
    XmlParser parser{ "./resources/grammar.xml" };
    XmlWriter writer{ "./resources/new.xml" };

    temp vec{1, 2, 3};

    try
    {
        grammar_ptr grammar{ parser.parse() };
        //(*grammar->algorithms["epsilonRuleRemove"])();
        (*grammar->algorithms["leftRecursionRemove"])();
        writer.save(grammar);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }

    system("pause");
}