#ifndef DATE_HPP
#define DATE_HPP


class Date {
    private:
        int _hour;
        int _minutes;
        int _seconds;
        
    public:
        Date(int hour, int minutes, int seconds);
        Date();
        ~Date() = default;
        int getHour();
        int getMinutes();
        int getSeconds();
        bool isCurrentDate();
    
};

#endif // DATE_HPP