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
        void setClick(Click click);
        std::vector<Click> getClicks();
};

#endif // CYCLE_HPP