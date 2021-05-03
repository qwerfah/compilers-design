#include <iostream>
#include <memory>

#include "../include/xml/xml_parser.h"
#include "../include/xml/antlr_writer.h"
#include "../include/grammar_transform/grammar_transform.h"

int main()
{
    std::string inputFile{};
    std::string outputFile1{};
    std::string outputFile2{};
    std::string algorithm{};

    std::string defaultInputFile{ "./resources/grammar.xml" };
    std::string defaultOutputFile1{ "./resources/recursion_deleted.g4" };
    std::string defaultOutputFile2{ "./resources/left_factorized.g4" };
    std::string defaultAlgorithm{ "fact" };

    std::cout << "Enter input file name [" << defaultInputFile << "]: ";
    std::getline(std::cin, inputFile);

    std::cout << "Enter input file name 1 [" << defaultOutputFile1 << "]: ";
    std::getline(std::cin, outputFile1);

    std::cout << "Enter input file name 2 [" << defaultOutputFile2 << "]: ";
    std::getline(std::cin, outputFile2);

    std::cout << "Enter transform algorithm [" << defaultAlgorithm << "]: ";
    std::getline(std::cin, algorithm);

    try
    {
        XmlParser parser{ inputFile.empty() ? defaultInputFile : inputFile };
        AntlrWriter writer{ outputFile1.empty() ? defaultOutputFile1 : outputFile1 };
        grammar_ptr grammar{ parser.parse() };

        //(*grammar->algorithms["epsilon"])();
        //(*grammar->algorithms[ algorithm.empty() ? defaultAlgorithm : algorithm ])();

        (*grammar->algorithms["recursion"])();
        writer.save(grammar);
        writer.setFilename(outputFile2.empty() ? defaultOutputFile2 : outputFile2);
        (*grammar->algorithms["fact"])();
        writer.save(grammar);
        
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }

    system("pause");
}