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

    public:
        Click(int duration, int x, int y);
        ~Click() = default;
                
};

#endif // CYCLE_HPP