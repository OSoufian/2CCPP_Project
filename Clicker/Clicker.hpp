#ifndef CLICKER_HPP
#define CLICKER_HPP

#include <vector>

#include "../Task/Task.hpp"
#include "../History/History.hpp"
class Clicker
{
private:
    std::vector<Task> _tasks;
    std::vector<History> _histories;

public:
    Clicker();
    ~Clicker() = default;
    void displayTasks();

    bool isDigit(std::string input);

    void mainMenu();
    bool getMainAction(std::string action);

    void tasksListMenu();
    bool getTasksListAction(char action);

    void addTaskMenu();

    bool validTaskIndex(int taskIndex);
    void renameTaskMenu();

    void deleteTaskMenu();

    void duplicateTaskMenu();

    void runTaskMenu();
};

#endif // CLICKER_HPP