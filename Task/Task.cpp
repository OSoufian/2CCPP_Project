#include <iostream>
#include "Task.hpp"
#include <vector>

Task::Task(std::string name, Cycle cycle, int cycleRepetition = 0, int delay = 0, time_t delayedExecution = 0)
{
    this->_name = name;
    this->_cycle = cycle;
    this->_cycleRepetition = cycleRepetition;
    this->_delay = delay;
    this->_delayedExecution = delayedExecution;
}

void Task::setName(std::string name)
{
    this->_name = name;
}

void Task::display()
{
    std::cout << "Voici le path de notre tâche : " << std::endl;
}

void Task::run()
{
}