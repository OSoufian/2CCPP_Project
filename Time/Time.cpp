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

int Time::getMinutes() {
    return this->_minutes;
}

int Time::getSeconds() {
    return this->_seconds;
}

bool Time::isCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    if (ltm->tm_hour == this->_hour &&
        ltm->tm_min == this->_minutes &&
        ltm->tm_sec == this->_seconds) return true;
    return false;
}