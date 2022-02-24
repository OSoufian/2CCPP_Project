#include <iostream>
#include "Task.hpp"
#include <vector>

Task::Task(std::string name, int cycleRepetitions, bool isInfiniteCycle, int timeInterval, time_t delayedExecution)
{
    this->_name = name;
    this->_cycleRepetitions = cycleRepetitions;
    this->_isInfiniteCycle = isInfiniteCycle;
    this->_timeInterval = timeInterval;
    this->_delayedExecution = delayedExecution;
}

Task::Task()
{
}

std::string Task::getName()
{
    return this->_name;
}

void Task::setName(std::string name)
{
    this->_name = name;
}

// Cycle Task::getCycle() {
//     return this->_cycle;
// }

void Task::setClick(Click click)
{
    this->_clicks.push_back(click);
}

std::vector<Click> Task::getClicks()
{
    return this->_clicks;
}

int Task::getCycleRepetitions()
{
    return this->_cycleRepetitions;
}

bool Task::getIsInfiniteCycle() {
    return this->_isInfiniteCycle;    
}

void Task::setIsInfiniteCycle(bool isInfiniteCycle) {
    this->_isInfiniteCycle = isInfiniteCycle;
}

int Task::getTimeInterval()
{
    return this->_timeInterval;
}

void Task::setCycleRepetitions(int cycleRepetitions)
{
    this->_cycleRepetitions = cycleRepetitions;
}

void Task::setTimeInterval(int timeInterval)
{
    this->_timeInterval = timeInterval;
}

void Task::run()
{
}