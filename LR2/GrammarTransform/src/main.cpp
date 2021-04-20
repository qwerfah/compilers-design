#include <iostream>
#include <memory>

#include "../include/xml/xml_parser.h"
#include "../include/xml/xml_writer.h"
#include "../include/grammar_transform/grammar_transform.h"

int main()
{
    std::string inputFile{};
    std::string outputFile{};
    std::string algorithm{};

    std::cout << "Enter input file name [./resources/grammar.xml]: ";
    std::getline(std::cin, inputFile);

    std::cout << "Enter input file name [./resources/new.xml]: ";
    std::getline(std::cin, outputFile);

    std::cout << "Enter transform algorithm [recursion]: ";
    std::getline(std::cin, algorithm);

    try
    {
        XmlParser parser{ inputFile.empty() ? "./resources/grammar.xml" : inputFile };
        XmlWriter writer{ outputFile.empty() ? "./resources/new.xml" : outputFile };

        grammar_ptr grammar{ parser.parse() };
        //(*grammar->algorithms["epsilon"])();
        (*grammar->algorithms[ algorithm.empty() ? "recursion" : algorithm ])();
        writer.save(grammar);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }

    system("pause");
}