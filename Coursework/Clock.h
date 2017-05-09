#ifndef Clock_H
#define Clock_H
 
#include "mbed.h"

class Clock{
    //variables  //public so that Reading can read it
    public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    
    Clock(int y, int mo, int d, int h,int mi,int s);
    Clock();
    
    void TickTock();
    void setClock(Clock *dt);
		void readClock();
    
    };
#endif