#include <iostream>
#include "Task.hpp"
#include <vector>

Task::Task(std::string name, int cycleRepetitions, int timeInterval, time_t delayedExecution) {
    this->_name = name;
    this->_cycleRepetitions = cycleRepetitions;
    this->_timeInterval = timeInterval;
    this->_delayedExecution = delayedExecution;
}

std::string Task::getName() {
    return this->_name;
}

void Task::setName(std::string name) {
    this->_name = name;
}

// Cycle Task::getCycle() {
//     return this->_cycle;
// }

void Task::setClick(Click click) {
    this->_clicks.push_back(click);
}

std::vector<Click> Task::getClicks() {
    return this->_clicks;
}

int Task::getCycleRepetitions() {
    return this->_cycleRepetitions;
}

int Task::getTimeInterval() {
    return this->_timeInterval;
}



void Task::display() {
    std::cout << "Voici le path de notre tâche : " << std::endl;
}

void Task::run() {
}