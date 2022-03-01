#include <string>
#include <iostream>
#include <thread>
#include <Windows.h>
#include "Time/Time.hpp"

using namespace std;


void run(Time time) {
    while (!time.isNow()) Sleep(1000);
    cout << "Il est l'heure !";
}

int main() {
    Time time(19, 55, 0);
    thread t1(run, time);
    t1.join();
}