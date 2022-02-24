#include <iostream>
#include "Clicker.hpp"

Clicker::Clicker() {}

void Clicker::setTask(Task task) {
    this->_tasks.push_back(task);
}

std::vector<Task> Clicker::getTasks() {
    return this->_tasks;
}

Task Clicker::getTask(int taskIndex) {
    return this->_tasks[taskIndex - 1];
}

void Clicker::displayTasks() {
    for (int i = 0; i < this->_tasks.size(); i++) {
        std::cout << this->_tasks[i].getName() << ":" << std::endl;
        std::cout << "Position du clique : (" << this->_tasks[i].getClicks()[0].getX() << ", " << this->_tasks[i].getClicks()[0].getY() << ")" << std::endl;
        std::cout << "Nombres de repetions: ";
        if (!this->_tasks[i].getClicks()[0].getIsHeld()) std::cout << "en boucle\n";
        else std::cout << this->_tasks[i].getCycleRepetitions() << std::endl;
        std::cout << "Temps d'intervalle: " << this->_tasks[i].getTimeInterval() << " secondes\n\n";
    }
}