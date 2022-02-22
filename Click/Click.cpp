#include <iostream>
#include "Click.hpp"

Click::Click(int duration, int x, int y)
{
    this->_duration = duration;
    this->_position[0] = x;
    this->_position[1] = y;
}