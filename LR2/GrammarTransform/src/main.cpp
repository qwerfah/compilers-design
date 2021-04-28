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

    std::string defaultInputFile{ "./resources/grammar.xml" };
    std::string defaultOutputFile{ "./resources/new.xml" };
    std::string defaultAlgorithm{ "fact" };

    std::cout << "Enter input file name [" << defaultInputFile << "]: ";
    std::getline(std::cin, inputFile);

    std::cout << "Enter input file name [" << defaultOutputFile << "]: ";
    std::getline(std::cin, outputFile);

    std::cout << "Enter transform algorithm [" << defaultAlgorithm << "]: ";
    std::getline(std::cin, algorithm);

    try
    {
        XmlParser parser{ inputFile.empty() ? defaultInputFile : inputFile };
        XmlWriter writer{ outputFile.empty() ? defaultOutputFile : outputFile };

        grammar_ptr grammar{ parser.parse() };
        //(*grammar->algorithms["epsilon"])();
        (*grammar->algorithms[ algorithm.empty() ? defaultAlgorithm : algorithm ])();
        writer.save(grammar);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }

    system("pause");
}