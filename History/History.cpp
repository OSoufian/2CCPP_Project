#include <iostream>
#include "History.hpp"

History::History(std::string name, time_t timeExecution, std::chrono::duration<double> duration) {
    this->_name = name;
    this->_timeExecution = timeExecution;
    this->_duration = duration;    
}

std::string History::getName() {
    return this->_name;
}

time_t History::getTimeExecution() {
    return this->_timeExecution;
}

std::chrono::duration<double> History::getDuration() {
    return this->_duration;
}