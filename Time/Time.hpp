#ifndef TIME_HPP
#define TIME_HPP


class Time {
    private:
        int _hour;
        int _minutes;
        int _seconds;
        
    public:
        Time(int hour, int minutes, int seconds);
        Time();
        ~Time() = default;
        int getHour();
        int getMinutes();
        int getSeconds();
        bool isCurrentTime();
    
};

#endif // TIME_HPP