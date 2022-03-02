#include <string>
#include <iostream>
#include <thread>
#include <Windows.h>
#include "Time/Time.hpp"
#include "Task/Task.hpp"

using namespace std;


void run() {
    // while (!time.isNow()) Sleep(1000);
    cout << "Il est l'heure !";
}

int main() {
    Time time(19, 55, 0);
    thread t1(run);
    t1.join();
}