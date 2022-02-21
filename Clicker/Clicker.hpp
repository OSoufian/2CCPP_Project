#ifndef CLICKER_HPP
#define CLICKER_HPP

#include <vector>

#include "../Task/Task.hpp"
class Clicker {
private:
    std::vector<Task> _tasks;
    
    
public:
    Clicker();
    ~Clicker() = default;
};

#endif //CLICKER_HPP