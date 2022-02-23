#include <iostream>
#include "Click.hpp"

Click::Click(int duration, int x, int y, bool isHeld) {
    this->_duration = duration;
    this->_position[0] = x;
    this->_position[1] = y;
    this->_isHeld = isHeld;
}

int Click::getX(){
    return this->_position[0];
}

int Click::getY(){
    return this->_position[1];
}

bool Click::getIsHeld() {
    return this->_isHeld;    
}