#include <iostream>

#include "../include/regex/regex_parser.h"

void printTree(const std::shared_ptr<RegularExpression>& tree, std::string&& tabs = "")
{
    if (typeid(*tree) == typeid(Or))
    {
        auto orExpr = dynamic_cast<Or*>(tree.get());
        std::cout << tabs << "Or: " << orExpr->getRawString() << std::endl;
        std::cout << tabs << "Contains of:" << std::endl;
        printTree(orExpr->getLeftExpr(), tabs + "  ");
        printTree(orExpr->getRightExpr(), tabs + "  ");
    }
    else if (typeid(*tree) == typeid(Concat))
    {
        auto concat = dynamic_cast<Concat*>(tree.get());
        std::cout << tabs << "Concat: " << concat->getRawString() << std::endl;
        std::cout << tabs << "Contains of:" << std::endl;
        printTree(concat->getLeftExpr(), tabs + "  ");
        printTree(concat->getRightExpr(), tabs + "  ");
    }
    else if (typeid(*tree) == typeid(Repeat))
    {
        auto repeat = dynamic_cast<Repeat*>(tree.get());
        std::cout << tabs << "Repeat: " << static_cast<int>(repeat->getType()) << " " << repeat->getRawString() << std::endl;
        std::cout << tabs << "Contains of:" << std::endl;
        printTree(repeat->getExpr(), tabs + "  ");
    }
    else if (typeid(*tree) == typeid(Literal))
    {
        auto literal = dynamic_cast<Literal*>(tree.get());
        std::cout << tabs << "Literal: " << static_cast<int>(literal->getType()) << " " << literal->getRawString() << std::endl;
    }
}

int main()
{
    auto tree = RegexParser::parse("abc|(dfr)*g+..f?(ab|)");

    printTree(tree);

    system("pause");
}