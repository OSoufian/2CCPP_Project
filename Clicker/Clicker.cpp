#include <iostream>
#include "Clicker.hpp"

Clicker::Clicker()
{
}

void Clicker::setTask(Task task) {
    this->_tasks.push_back(task);

}

void Clicker::displayTasks()
{
    // for (int i = 0; i < ; i++)
    // {
    //     cout <<  << endl;
    // }

    this->_tasks[0].getName();
}