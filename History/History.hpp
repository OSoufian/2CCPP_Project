#ifndef HISTORY_HPP
#define HISTORY_HPP
#include <string>
#include <chrono>

class History {
private:
    std::string _name;
    time_t _timeExecution;
    std::chrono::duration<double> _duration;

    
public:
    History(std::string name, time_t timeExecution, std::chrono::duration<double> duration);
    ~History() = default;
    std::string getName();
    time_t getTimeExecution();
    std::chrono::duration<double> getDuration();
};

#endif // HISTORY_HPP