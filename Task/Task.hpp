#ifndef TASK_HPP
#define TASK_HPP

#include "../Cycle/Cycle.hpp"

class Task {
private:
    std::string _name;
    Cycle _path;
    int _numberCycles;
    time_t _delayedExecution;
    int _delay;

public:
    Task(std::string name, Cycle path, int numberCycles = 0, time_t delayedExecution = 0, int delay = 0);
    ~Task() = default;
    void setName(std::string name);
    void display();
    void run();
};

#endif //TASK_HPP