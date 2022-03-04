#ifndef CLICKER_HPP
#define CLICKER_HPP

#include <vector>

#include "../Task/Task.hpp"
#include "../History/History.hpp"

void runScheduledTask(Task task);

class Clicker {
private:
    std::vector<Task> _tasks;
    std::vector<History> _history;

public:
    Clicker();
    ~Clicker() = default;  

    void mainMenu();
    bool getMainAction(std::string action);
    bool getActionWithoutInput(char action);
    bool getReturnAction(std::string action);

    void tasksList();    
    void displayTasks();        

    void addTask();
    bool isDigit(std::string input);   

    void renameTask();
    bool validTaskIndex(int taskIndex);

    void deleteTask();

    void runTask();
    int keyPressed(int key);
    DWORD notHeldClickType(int key);
    DWORD heldClickType(int key);
    bool isHeld(int posx, int posy, int key);    
    Click captureClick(int key);

    void duplicateTask();

    void history();
    void displayHistory();

    void saveTask();
    void writeTasks(std::string fileName);
    bool readTasks(std::string fileName);
    bool isValidFileName(std::string nameFile);
    
    
};

#endif // CLICKER_HPP