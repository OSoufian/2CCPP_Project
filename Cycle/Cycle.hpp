#ifndef CYCLE_HPP
#define CYCLE_HPP

#include <vector>

#include "../Click/Click.hpp"

class Cycle {
    private:
        std::vector<Click> _clicks;

    public:
        Cycle();
        ~Cycle() = default;
        void listener();
        void instructions(int _delay, int _numberClicks, int _duration);
        void setClick(Click click);
};

#endif // CYCLE_HPP