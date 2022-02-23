#ifndef TASK_HPP
#define TASK_HPP

#include "../Cycle/Cycle.hpp"

class Task {
    private:
        std::string _name;
        Cycle _cycle;
        int _cycleRepetitions;
        int _timeInterval;
        time_t _delayedExecution;

    public:
        Task(std::string name, Cycle cycle, int cycleRepetitions, int timeInterval = 0, time_t delayedExecution = 0);
        ~Task() = default;
        std::string getName();
        void setName(std::string name);
        Cycle getCycle();
        int getCycleRepetitions();
        int getTimeInterval();
        void display();
        void run();
};

#endif // TASK_HPP