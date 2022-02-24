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
    std::vector<Task> getTasks();
    Task getTask(int taskIndex);
    void setTask(Task task);
    void deleteTask(int taskIndex);
    void setTaskName(int taskIndex, std::string newTaskName);
};

#endif // CLICKER_HPP