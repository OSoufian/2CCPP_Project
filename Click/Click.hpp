#ifndef CLICK_HPP
#define CLICK_HPP

#include <vector>

// enum Type {
//     RIGHTCLICK,
//     LEFTCLICK
// };

class Click {
    private:
        // Type _type;
        int _duration;
        int _position[2];
        bool _isHeld;

    public:
        Click(int duration, int x, int y, bool isHeld);
        ~Click() = default;
        int getX();
        int getY();
        bool getIsHeld();
                
};

#endif // CYCLE_HPP