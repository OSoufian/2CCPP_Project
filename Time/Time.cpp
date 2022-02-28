#include <iostream>
#include <ctime>
#include "Time.hpp"

using namespace std;

Time::Time(int hour, int minutes, int seconds) {
    this->_hour = hour;
    this->_minutes = minutes;
    this->_seconds = seconds;
}

Time::Time() {
}

int Time::getHour() {
    return this->_hour;
}

void Time::setHour(int hour) {
    this->_hour = hour;
}

int Time::getMinutes() {
    return this->_minutes;
}

void Time::setMinutes(int minutes) {
    this->_minutes = minutes;
}

int Time::getSeconds() {
    return this->_seconds;
}

void Time::setSeconds(int seconds) {
    this->_seconds = seconds;
}

bool Time::isNow() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    if (ltm->tm_hour == this->_hour &&
        ltm->tm_min == this->_minutes &&
        ltm->tm_sec == this->_seconds) return true;
    return false;
}