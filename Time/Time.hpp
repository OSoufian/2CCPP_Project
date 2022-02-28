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
        void setHour(int hour);
        int getMinutes();
        void setMinutes(int minutes);
        int getSeconds();
        void setSeconds(int seconds);
        bool isNow();
};

#endif // TIME_HPP