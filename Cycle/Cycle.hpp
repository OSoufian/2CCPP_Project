#ifndef CYCLE_HPP
#define CYCLE_HPP

class Cycle {
private:
    int _delay;
    int _numberClicks;
    int _duration;

public:
    Cycle();
    ~Cycle() = default;
    void listener();
};

#endif // CYCLE_HPP