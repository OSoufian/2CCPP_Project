#include <iostream>
#include <windows.h>
#include "Task.hpp"
#include <vector>

Task::Task(std::string name, int cycleRepetitions, bool isInfiniteCycle, bool isScheduled, int timeInterval) {
	this->_name = name;
	this->_cycleRepetitions = cycleRepetitions;
	this->_isInfiniteCycle = isInfiniteCycle;
	this->_isScheduled = isScheduled;
	this->_timeInterval = timeInterval;
}

Task::Task() {
}

std::string Task::getName() {
	return this->_name;
}

void Task::setName(std::string name) {
	this->_name = name;
}

std::vector<Click> Task::getClicks() {
	return this->_clicks;
}

void Task::addClick(Click click) {
	this->_clicks.push_back(click);
}

int Task::getCycleRepetitions() {
	return this->_cycleRepetitions;
}

void Task::setCycleRepetitions(int cycleRepetitions) {
	this->_cycleRepetitions = cycleRepetitions;
}

bool Task::getIsInfiniteCycle() {
	return this->_isInfiniteCycle;
}

void Task::setIsInfiniteCycle(bool isInfiniteCycle) {
	this->_isInfiniteCycle = isInfiniteCycle;
}

bool Task::getIsScheduled() {
	return this->_isScheduled;
}

void Task::setIsScheduled(bool isScheduled) {
	this->_isScheduled = isScheduled;
}

int Task::getTimeInterval() {
	return this->_timeInterval;
}

void Task::setTimeInterval(int timeInterval) {
	this->_timeInterval = timeInterval;
}

int Task::getHourTime() {
    return this->_timeExecution.getHour();
}

int Task::getMinutesTime() {
    return this->_timeExecution.getMinutes();
}

int Task::getSecondsTime() {
    return this->_timeExecution.getSeconds();
}

void Task::setTimeExecution(Time timeExecution) {
	this->_timeExecution = timeExecution;
}

void Task::run() {
	bool click = false;
	int cycles = this->_cycleRepetitions;
	std::string stopTask;
	bool isInfiniteCycle = this->_isInfiniteCycle;

	std::cout << "Press 'P' to enable and 'S' to disable autoclicker\n";

	while (cycles != 0 || isInfiniteCycle) {
		if (GetAsyncKeyState('P')) {
			click = true;
		}
		else if (GetAsyncKeyState('S')) {
			click = false;
			if (isInfiniteCycle) {
				system("cls");
				std::cout << "Voulez vous arrêter la tâche? ([O]oui/[n]non)\n";
				bool valid = false;
				do {
					std::cin >> stopTask;
					if (stopTask == "oui" || stopTask == "o" || stopTask == "O" || stopTask == "non" || stopTask == "n" || stopTask == "N") {
						if (stopTask == "oui" || stopTask == "o" || stopTask == "O") {
							isInfiniteCycle = false;
							return;
						}
						valid = true;
					}
				} while (!valid);
			}
		}
		if (click == true) {
			int x;
			int y;

			for (int i = 0; i < this->_clicks.size(); i++) {
				x = this->_clicks[i].getX();
				y = this->_clicks[i].getY();

				SetCursorPos(x, y);
				mouse_event(this->_clicks[i].getType(), x, y, 0, 0);
				if (this->_clicks[i].getIsHeld()) {
					Sleep(this->_clicks[i].getDuration() * 1000);
				}
				mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
				Sleep(1000 * this->_timeInterval);
			}
			cycles--;
		}
	}
}