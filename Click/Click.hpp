#ifndef CLICK_HPP
#define CLICK_HPP

#include <windows.h>
#include <vector>

class Click {
    private:
        DWORD _type;
        int _duration;
        int _position[2];
        bool _isHeld;

    public:
        Click(int x, int y, DWORD type, bool isHeld = false, int duration = 0);
        ~Click() = default;
        int getX();
        int getY();
        bool getIsHeld();
        int getDuration();
        DWORD getType();
        
                
};

#endif // CYCLE_HPP