#include <iostream>
#include <windows.h>
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

void Task::run() {

    bool click = false;
	int cycles = this->_cycleRepetitions;
    std::cout << "Press 'P' to enable and 'S' to disable autoclicker\n";
	while (cycles != 0 || this->_isInfiniteCycle) {
		if (GetAsyncKeyState('P')) {
			click = true; 
		}
		else if (GetAsyncKeyState('S')) {
			click = false;
		}
		if (click == true) {
			int x;
			int y;
			
			for (int i = 0; i < this->_clicks.size(); i++) {
				x = this->_clicks[i].getX();
				y = this->_clicks[i].getY();

			
				SetCursorPos(x, y);
				mouse_event(this->_clicks[i].getType(), x, y, 0, 0);
				if (this->_clicks[i].getIsHeld()){
					Sleep(this->_clicks[i].getDuration() * 1000);
				}
				mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
				Sleep(1000/this->_timeInterval);
			}
			
		}
		cycles--;
	}
}