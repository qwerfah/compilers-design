#include "../include/interface.h"

bool Interface::_isDebugOn = false;

void Interface::loop()
{
    unsigned short option = 0;
    std::string garbage = "";

    while (true)
    {
        _printMenu();
        std::cin.clear();
        fflush(stdin);
        std::cin >> option;

        system("cls");

        switch (option)
        {
        case 1:
            _setRegularExpression();
            break;
        case 2:
            _matchRegularExpression();
            break;
        case 3:
            _isDebugOn = !_isDebugOn;
            break;
        case 4:
            return;
        default:
            std::cout << std::endl << "Bad option, try again" << std::endl;
            system("pause");
        }
    }
}

const std::shared_ptr<Regex>& Interface::getRegex() const
{
    return _regex;
}

void Interface::printTree(const std::shared_ptr<RegularExpression>& tree, std::string&& tabs)
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

bool Interface::isDebugOn()
{
    return _isDebugOn;
}

void Interface::_printMenu() const
{
    system("cls");

    std::cout << std::endl;
    std::cout << "Debug mode: " << (_isDebugOn ? "On" : "Off") << std::endl;
    std::cout << "Current expression: "
        << (_regex ? _regex->getExpression() : "none") << std::endl;
    std::cout << "*********** Menu ***********" << std::endl;
    std::cout << "1 --- Set regular expression" << std::endl;
    std::cout << "2 ---- Match regex to string" << std::endl;
    std::cout << "3 -------------- Change mode" << std::endl;
    std::cout << "4 --------------------- Exit" << std::endl;
    std::cout << "****************************" << std::endl;
    std::cout << "Enter option: ";
}

void Interface::_setRegularExpression()
{
    std::string expression;

    std::cout << std::endl << "Enter regular expression: ";
    std::cin >> expression;

    if (!_regex)
    {
        _regex = std::shared_ptr<Regex>(new Regex(expression));
    }
    else
    {
        try
        {
            _regex->buildFSM(expression);
        }
        catch (std::exception e)
        {
            std::cout << std::endl << e.what() << std::endl;
            system("pause");
        }
    }
}

void Interface::_matchRegularExpression()
{
    if (!_regex)
    {
        std::cout << std::endl << "First enter regular expression to match with" << std::endl;
        system("pause");
        return;
    }

    std::string input;

    std::cout << std::endl << "Enter string to match: ";
    std::cin >> input;
    try
    {
        std::cout << std::endl << (_regex->match(input) ? "Match" : "Not match") << std::endl;
        system("pause");
    }
    catch (std::exception e)
    {
        std::cout << std::endl << e.what() << std::endl;
        system("pause");
    }
}
