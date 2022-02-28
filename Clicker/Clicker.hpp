#ifndef CLICKER_HPP
#define CLICKER_HPP

#include <vector>

#include "../Task/Task.hpp"
#include "../History/History.hpp"
class Clicker {
private:
    std::vector<Task> _tasks;
    std::vector<History> _history;

public:
    Clicker();
    ~Clicker() = default;

    void mainMenu();
    bool getMainAction(std::string action);

    void tasksListMenu();
    void displayTasks();
    bool getActionWithoutInput(char action);

    void addTaskMenu();
    bool isDigit(std::string input);

    void renameTaskMenu();
    bool validTaskIndex(int taskIndex);    

    void deleteTaskMenu();

    void runTaskMenu();

    void duplicateTaskMenu();    
   
    void historyMenu();
    void displayHistory();

    void saveTaskMenu();
    void writeTasks(std::string fileName);
    void readTasks(std::string fileName);
};

#endif // CLICKER_HPP