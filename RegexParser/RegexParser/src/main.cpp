#include <iostream>

#include "../include/regex/regex_parser.h"
#include "../include/regex/regex.h"
#include "../include/finite_state_machine/finite_state_machine.h"

void printTree(const std::shared_ptr<RegularExpression>& tree, std::string&& tabs = "")
{
    if (auto orExpr = dynamic_cast<Or*>(tree.get()))
    {
        std::cout << tabs << "Or: " << orExpr->getRawString() << std::endl;
        std::cout << tabs << "Contains of:" << std::endl;
        printTree(orExpr->getLeftExpr(), tabs + "  ");
        printTree(orExpr->getRightExpr(), tabs + "  ");
    }
    else if (auto concat = dynamic_cast<Concat*>(tree.get()))
    {
        std::cout << tabs << "Concat: " << concat->getRawString() << std::endl;
        std::cout << tabs << "Contains of:" << std::endl;
        printTree(concat->getLeftExpr(), tabs + "  ");
        printTree(concat->getRightExpr(), tabs + "  ");
    }
    else if (auto repeat = dynamic_cast<Repeat*>(tree.get()))
    {
        std::cout << tabs << "Repeat: " << static_cast<int>(repeat->getType()) 
            << " " << repeat->getRawString() << std::endl;
        std::cout << tabs << "Contains of:" << std::endl;
        printTree(repeat->getExpr(), tabs + "  ");
    }
    else if (auto literal = dynamic_cast<Literal*>(tree.get()))
    {
        std::cout << tabs << "Literal: " << static_cast<int>(literal->getType()) 
            << " " << literal->getRawString() << std::endl;
    }
}

int main()
{
    // auto tree = RegexParser::parse("(ab*c){3,8}|(dfr)*(g)+((..f)?)(ab|)");
    // printTree(tree);

    /*
    auto machine = FiniteStateMachine();

    auto state1 = std::shared_ptr<State>(new State);
    auto state2 = std::shared_ptr<State>(new State);
    auto state3 = std::shared_ptr<State>(new State);
    auto state4 = std::shared_ptr<State>(new State);

    auto arc1 = std::shared_ptr<Arc>(new Arc(state1, state2, 'a'));
    auto arc2 = std::shared_ptr<Arc>(new Arc(state2, state3, 'b'));
    auto arc3 = std::shared_ptr<Arc>(new Arc(state3, state4, 'c'));

    machine.addState(state1);
    machine.addState(state2);
    machine.addState(state3);
    machine.addState(state4);

    machine.addArc(arc1);
    machine.addArc(arc2);
    machine.addArc(arc3);

    machine.setInitState(state1);
    machine.setFinalState(state4);

    std::cout << machine.match("abc") << std::endl;
    */

    std::unique_ptr<Regex> regex = nullptr;

    while (true)
    {
        short option = 0;
        std::cout << "1 - set regex" << std::endl << "2 - match" << std::endl;
        std::cin >> option;
    }

    system("pause");
}