#include <iostream>
#include <fstream>

#include "Click.hpp"

Click::Click(int x, int y, DWORD type, bool isHeld,  int duration) {
    this->_position[0] = x;
    this->_position[1] = y;
    this->_type = type;
    this->_isHeld = isHeld;
    this->_duration = duration;
}

Click::Click() {}

int Click::getX(){
    return this->_position[0];
}

int Click::getY(){
    return this->_position[1];
}

void Click::setPosition(int x, int y) {
    this->_position[0] = x;
    this->_position[1] = y;
}

DWORD Click::getType(){
    return this->_type;
}

void Click::setType(DWORD type) {
    this->_type = type;
}

bool Click::getIsHeld() {
    return this->_isHeld;    
}

void Click::setIsHeld(bool value) {
    this->_isHeld = value;
}

int Click::getDuration() {
    return this->_duration;
}

void Click::setDuration(int duration) {
    this->_duration = duration;
}

void Click::write(std::ofstream* file) {
    *file << _type << std::endl;
    *file << _duration << std::endl;
    *file << _position[0] << std::endl;
    *file << _position[1] << std::endl;
    *file << _isHeld << std::endl;
}

Click Click::read(std::ifstream* file) {
    Click click;

    DWORD type;
    *file >> type;
    click.setType(type);

    int value;
    *file >> value;
    click.setDuration(value);

    int value2;
    *file >> value;
    *file >> value2;
    click.setPosition(value, value2);

    bool held;
    *file >> held;
    click.setIsHeld(held);

    return click;
}