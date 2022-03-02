#ifndef CLICKER_HPP
#define CLICKER_HPP

#include <vector>

#include "../Task/Task.hpp"
#include "../History/History.hpp"

void runScheduledTask(Task task);

class Clicker
{
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
    int keyPressed(int key);

    void renameTaskMenu();
    bool validTaskIndex(int taskIndex);

    void deleteTaskMenu();

    void runTaskMenu();

    void duplicateTaskMenu();

    void historyMenu();
    void displayHistory();

    void saveTaskMenu();
    void writeTasks(std::string fileName);
    bool readTasks(std::string fileName);
    bool isValidFileName(std::string nameFile);
    bool isHeld(int posx, int posy, int key);
    DWORD ClickType2(int key);
    DWORD ClickType(int key);
    Click captureClick(int key);
};

#endif // CLICKER_HPP