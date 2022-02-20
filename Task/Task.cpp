#include <iostream>
#include "Task.hpp"
#include <vector>


Task::Task(std::string name, Cycle path, int numberCycles = 0, time_t delayedExecution = 0, int delay = 0) {
    this->_name = name;
    this->_path = path;
    this->_numberCycles = numberCycles;
    this->_delayedExecution = delayedExecution;
    this->_delay = delay;
}

void Task::setName(std::string name) {
    this->_name = name;
}

void Task::display() {
    std::cout << "Voici le path de notre tâche : " << std::endl;
}

void Task::run() {

}