#ifndef HISTORY_HPP
#define HISTORY_HPP
#include <string>

class History {
private:
    std::string _name;
    time_t _timeExecution;
    //_duration; Ajouter le type duration

    
public:
    History(std::string name);
    ~History() = default;
};

#endif // HISTORY_HPP