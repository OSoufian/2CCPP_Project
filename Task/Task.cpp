#include <iostream>
#include <windows.h>
#include <fstream>
#include "Task.hpp"
#include <vector>

using namespace std;

Task::Task(string name, int cycleRepetitions, bool isInfiniteCycle, bool isScheduled, int timeInterval) {
	this->_name = name;
	this->_cycleRepetitions = cycleRepetitions;
	this->_isInfiniteCycle = isInfiniteCycle;
	this->_isScheduled = isScheduled;
	this->_timeInterval = timeInterval;
}

Task::Task() {
}

string Task::getName() {
	return this->_name;
}

void Task::setName(string name) {
	this->_name = name;
}

vector<Click> Task::getClicks() {
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

Time Task::getTimeExecution() {
	return this->_timeExecution;
}

void Task::setTimeExecution(Time timeExecution) {
	this->_timeExecution = timeExecution;
}

void Task::run() {
	bool click = false;
	int cycles = this->_cycleRepetitions;
	string stopTask;
	bool isInfiniteCycle = this->_isInfiniteCycle;

	
	system("cls");
	cout << "Press 'P' to enable and 'S' to disable autoclicker\n";	
	while (cycles != 0 || isInfiniteCycle) {
		if (GetAsyncKeyState('P')) {
			click = true;
		}
		else if (GetAsyncKeyState('S')) {
			click = false;
			if (isInfiniteCycle) {
				system("cls");
				cout << "Voulez vous arrêter la tâche? ([O]oui/[n]non)\n";
				bool valid = false;
				do {
					cin >> stopTask;
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


void Task::write(ofstream *file) {
	*file << this->_name << endl;
	*file << this->_cycleRepetitions << endl;
	*file << this->_isInfiniteCycle << endl;
	*file << this->_isScheduled << endl;
	*file << this->_timeInterval << endl;

	*file << this->_timeExecution.getHour() << endl;
	*file << this->_timeExecution.getMinutes() << endl;
	*file << this->_timeExecution.getSeconds() << endl;

	int clicks = this->_clicks.size();
	*file << clicks << endl;
	for (int i = 0; i < clicks; i++) this->_clicks[i].write(file);	
}

Task Task::read(ifstream *file) {
	Task task;

	string name;
	*file >> name;
	task.setName(name);

	int value;
	*file >> value;
	task.setCycleRepetitions(value);
		
	*file >> value;
	task.setIsInfiniteCycle(value);

	*file >> value;
	task.setIsScheduled(value);

	*file >> value;
	task.setTimeInterval(value);
	
	Time time;
	*file >> value;
	time.setHour(value);
	*file >> value;
	time.setMinutes(value);
	*file >> value;
	time.setSeconds(value);
	task.setTimeExecution(time);

	*file >> value;
	for (int i = 0; i < value; i++) task.addClick(Click::read(file));

	return task;
}