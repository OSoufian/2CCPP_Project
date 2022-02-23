#include <iostream>
#include "Clicker.hpp"

Clicker::Clicker() {}

void Clicker::setTask(Task task) {
    this->_tasks.push_back(task);
}

void Clicker::displayTasks() {
    std::cout << this->_tasks[0].getName();
}