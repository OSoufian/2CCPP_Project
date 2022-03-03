#include <iostream>
#include <vector>

bool getMainAction(char action)
{

    std::string actions = "VvAaRrSsDdLlHhIiQq";

    int i = 0;
    int which = (actions.size() - i);
    if (action == (actions.at(i) || actions.at(i+1)))
    {
        std::cout << action << std::endl;
        return true;
    }

    // else if (action == "A" || action == "a")
    // {
    //     std::cout << action << std::endl;
    //     return true;
    // }
    // else if (action == "R" || action == "r")
    // {
    //     std::cout << action << std::endl;
    //     return true;
    // }
    // else if (action == "S" || action == "s")
    // {
    //     std::cout << action << std::endl;
    //     return true;
    // }
    // else if (action == "D" || action == "d")
    // {
    //     std::cout << action << std::endl;
    //     return true;
    // }
    // else if (action == "L" || action == "l")
    // {
    //     std::cout << action << std::endl;
    //     return true;
    // }
    // else if (action == "H" || action == "h")
    // {
    //     std::cout << action << std::endl;
    //     return true;
    // }
    // else if (action == "I" || action == "i")
    // {
    //     std::cout << action << std::endl;
    //     return true;
    // }
    // else if (action == "Q" || action == "q")
    // {
    //     exit(0);
    // }
    else
    {
        return false;
    }
}

int main()
{
    char action;
    std::cin >> action;

    getMainAction(action);
}