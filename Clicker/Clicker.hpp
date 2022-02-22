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
    void setTask(Task task);
};

#endif // CLICKER_HPP