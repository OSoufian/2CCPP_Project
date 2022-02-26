#include <iostream>
#include "Click.hpp"

Click::Click(int x, int y, DWORD type, bool isHeld,  int duration) {
    this->_position[0] = x;
    this->_position[1] = y;
    this->_type = type;
    this->_isHeld = isHeld;
    this->_duration = duration;
}

int Click::getX(){
    return this->_position[0];
}

int Click::getY(){
    return this->_position[1];
}

DWORD Click::getType(){
    return this->_type;
}

bool Click::getIsHeld() {
    return this->_isHeld;    
}

int Click::getDuration() {
    return this->_duration;
}