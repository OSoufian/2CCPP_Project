#ifndef TASK_HPP
#define TASK_HPP

// #include "../Cycle/Cycle.hpp"
#include "../Click/Click.hpp"

class Task {
    private:
        std::string _name;
        // Cycle _cycle;
        std::vector<Click> _clicks;
        int _cycleRepetitions;
        int _timeInterval;
        time_t _delayedExecution;

    public:
        Task(std::string name, int cycleRepetitions, int timeInterval = 0, time_t delayedExecution = 0);
        Task();
        ~Task() = default;
        std::string getName();
        void setName(std::string name);
        // Cycle getCycle();
        std::vector<Click> getClicks();
        void setClick(Click click);
        int getCycleRepetitions();
        int getTimeInterval();
        void display();
        void run();
};

#endif // TASK_HPP