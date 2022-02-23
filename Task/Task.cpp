#include <iostream>
#include "Task.hpp"
#include <vector>

Task::Task(std::string name, Cycle cycle, int cycleRepetition, int delay, time_t delayedExecution) {
    this->_name = name;
    this->_cycle = cycle;
    this->_cycleRepetition = cycleRepetition;
    this->_delay = delay;
    this->_delayedExecution = delayedExecution;
}

void Task::setName(std::string name) {
    this->_name = name;
}

void Task::display() {
    std::cout << "Voici le path de notre tâche : " << std::endl;
}

void Task::run() {
}

std::string Task::getName() {
    return this->_name;
}