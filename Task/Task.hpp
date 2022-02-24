#ifndef TASK_HPP
#define TASK_HPP

// #include "../Cycle/Cycle.hpp"
#include "../Click/Click.hpp"

class Task {
    private:
        std::string _name;
        std::vector<Click> _clicks;
        int _cycleRepetitions;
        bool _isInfiniteCycle;
        int _timeInterval;
        time_t _delayedExecution;

    public:
        Task(std::string name, int cycleRepetitions = 1, bool isInfiniteCycle = false, int timeInterval = 0, time_t delayedExecution = 0);
        Task();
        ~Task() = default;
        std::string getName();
        void setName(std::string name);
        std::vector<Click> getClicks();
        void setClick(Click click);
        int getCycleRepetitions();
        bool getIsInfiniteCycle();
        void setIsInfiniteCycle(bool isInfiniteCycle);
        int getTimeInterval();
        void setCycleRepetitions(int cycleRepetitions);
        void setTimeInterval(int timeInterval);
        void display();
        void run();
};

#endif // TASK_HPP