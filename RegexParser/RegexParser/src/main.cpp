#include <iostream>

#include "../include/interface.h"

int main()
{
    Interface interface;

    std::set<int> set = {1, 2, 3, 4, 5};
    std::vector<int> vector = { 2,5,6 };

    std::erase_if(set, [&](auto el) { return std::find(vector.begin(), vector.end(), el) != vector.end(); });

    for (auto i : set)
    {
        std::cout << i << " ";
    }

    //interface.loop();
}