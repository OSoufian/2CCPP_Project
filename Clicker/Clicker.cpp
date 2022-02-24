#include <iostream>
#include "Clicker.hpp"

Clicker::Clicker() {}

void Clicker::setTask(Task task)
{
    this->_tasks.push_back(task);
}

void Clicker::setTaskName(int taskIndex, std::string newTaskName)
{
    this->_tasks[taskIndex - 1].setName(newTaskName);
}

std::vector<Task> Clicker::getTasks()
{
    return this->_tasks;
}

Task Clicker::getTask(int taskIndex)
{
    return this->_tasks[taskIndex - 1];
}

void Clicker::deleteTask(int taskIndex)
{
    this->_tasks.erase(this->_tasks.begin() + taskIndex - 1);
}

void Clicker::displayTasks()
{
    for (int i = 0; i < this->_tasks.size(); i++)
    {
        std::cout << this->_tasks[i].getName() << ":" << std::endl;
        for (int j = 0; j < this->_tasks[i].getClicks().size(); j++){
            std::cout << "Position du clique " << (j+1) << ": (" << this->_tasks[i].getClicks()[j].getX() << ", " << this->_tasks[i].getClicks()[j].getY() << ")" << std::endl;
            if (this->_tasks[i].getClicks()[j].getIsHeld())
                std::cout << "Le temps de maintien du clique est de : " << this->_tasks[i].getClicks()[j].getDuration() << std::endl;
        }
        std::cout << "Nombres de repetions du cycle : ";
        if (this->_tasks[i].getIsInfiniteCycle())
            std::cout << "En boucle !" << std::endl;
        else 
            std::cout << this->_tasks[i].getCycleRepetitions() << std::endl;
        std::cout << "Temps d'intervalle entre 2 cycles: " << this->_tasks[i].getTimeInterval() << " secondes\n\n";
    }
}