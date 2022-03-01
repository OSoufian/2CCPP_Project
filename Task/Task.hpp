#ifndef TASK_HPP
#define TASK_HPP

#include "../Click/Click.hpp"
#include "../Time/Time.hpp"

class Task {
    private:
        std::string _name;
        std::vector<Click> _clicks;
        int _cycleRepetitions;
        bool _isInfiniteCycle;
        bool _isScheduled;
        int _timeInterval;
        Time _timeExecution;

    public:
        Task(std::string name, int cycleRepetitions = 1, bool isInfiniteCycle = false, bool isScheduled = false, int timeInterval = 0);
        Task();
        ~Task() = default;
        
        std::string getName();
        void setName(std::string name);
        std::vector<Click> getClicks();
        void addClick(Click click);
        int getCycleRepetitions();
        void setCycleRepetitions(int cycleRepetitions);
        bool getIsInfiniteCycle();
        void setIsInfiniteCycle(bool isInfiniteCycle);
        bool getIsScheduled();
        void setIsScheduled(bool isScheduled);        
        int getTimeInterval();
        void setTimeInterval(int timeInterval);
        int getHourTime();
        int getMinutesTime();
        int getSecondsTime();
        void setTimeExecution(Time timeExecution);
        
        void display();
        void run();
        void Task::scheduledRun();

        void write(std::ofstream *file);
        static Task read(std::ifstream *file);
};

#endif // TASK_HPP