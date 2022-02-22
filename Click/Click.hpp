#ifndef CLICK_HPP
#define CLICK_HPP

#include <vector>

enum Type {
    RIGHTCLICK,
    LEFTCLICK
};

class Click {
    private:
        Type _type;
        int duration;
        int x;
        int y;

    public:
        Click();
        ~Click() = default;
                
};

#endif // CYCLE_HPP