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
        Click(int x, int y, bool isHeld = false, int duration = 0);
        ~Click() = default;
        int getX();
        int getY();
        bool getIsHeld();
        int getDuration();
        
                
};

#endif // CYCLE_HPP