#ifndef CYCLE_HPP
#define CYCLE_HPP

class Cycle {
private:

public:
    Cycle();
    ~Cycle() = default;
    void listener();
    void instructions(int _delay, int _numberClicks, int _duration);
};

#endif // CYCLE_HPP