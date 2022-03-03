#ifndef CLICK_HPP
#define CLICK_HPP

#include <windows.h>
#include <vector>

class Click {
    private:
        int _position[2];
        DWORD _type;
        bool _isHeld;
        int _duration;
        

    public:
        Click(int x, int y, DWORD type, bool isHeld = false, int duration = 0);
        Click();
        ~Click() = default;        

        int getX();
        int getY();
        void setPosition(int x, int y);
        bool getIsHeld();
        void setIsHeld(bool isHeld);
        int getDuration();
        void setDuration(int duration);
        DWORD getType();
        void setType(DWORD type);

        void write(std::ofstream* file);
        static Click read(std::ifstream* file);
};

#endif // CLICK_HPP