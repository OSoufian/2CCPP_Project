#include <iostream>
#include "Task/Task.hpp"

int main() {
    std::string name;
    std::cout << "Comment tu veux appeler ta tâche? \n Le nom : " << std::endl;
    std::cin >> name;
    std::cout << "On t'écoute vas y" << std::endl;
    Cycle cycle;
    Task task(name, cycle);
    return 0;
}
