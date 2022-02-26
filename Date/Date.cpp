#include <iostream>
#include <ctime>
#include "Date.hpp"

using namespace std;

Date::Date(int hour, int minutes, int seconds) {
    this->_hour = hour;
    this->_minutes = minutes;
    this->_seconds = seconds;
}

Date::Date() {
}

int Date::getHour() {
    return this->_hour;
}

int Date::getMinutes() {
    return this->_minutes;
}

int Date::getSeconds() {
    return this->_seconds;
}

bool Date::isCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    if (ltm->tm_hour == this->_hour &&
        ltm->tm_min == this->_minutes &&
        ltm->tm_sec == this->_seconds) return true;
    return false;
}