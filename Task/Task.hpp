#ifndef TASK_HPP
#define TASK_HPP

#include "../Cycle/Cycle.hpp"

class Task {
    private:
        std::string _name;
        Cycle _cycle;
        int _cycleRepetition;
        int _delay;
        time_t _delayedExecution;

    public:
        Task(std::string name, Cycle cycle, int cycleRepetition = 0, int delay = 0, time_t delayedExecution = 0);
        ~Task() = default;
        void setName(std::string name);
        void display();
        void run();
        std::string getName();
};

#endif // TASK_HPP