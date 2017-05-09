#include "Clock.h"

Clock::Clock(int y, int mo, int d, int h,int mi,int s){
    year = y;
    month = mo;
    day = d;
    hour = h;
    minute = mi;
    second = s;
}
Clock::Clock(){
    year = 2017;
    month = 01;
    day = 01;
    hour = 12;
    minute = 0;
    second = 0;
}
    
void Clock::TickTock(){
    //Adds a second every second
    second = second +1;
    if (second == 60){
        second = 0;
        minute = minute +1;
        if (minute == 60){
            minute = 0;
            hour = hour +1;
            if (hour == 24){
                hour = 0;
                day = day +1;
                    //check for month length - leap years to be added
                    if (month == 1||month == 3||month == 5||month == 7||month == 8||month == 10||month == 12){
                        if (day == 31){
                            day = 1;
                            month = month +1;
                            if (month == 12){
                                month = 1;
                                year = year +1;
                            }
                        }
                    }
                    else if (month == 4||month == 6||month == 9||month == 11){
                        if (day == 30) {
                        day = 1;
                        month = month +1;
                            if (month == 12){
                                month = 1;
                                year = year +1;
                            }
                        }
                    }       
                    else if (month == 2){//FEB LEAP YEAR TO ADD!
                        if (day == 28){
                        day = 1;
                        month = month +1;
                            if (month == 12){
                                month = 1;
                                year = year +1;
                            }
                        }       
                    } 
                }
            }
    }
}
  
void Clock::setClock(Clock *dt){
    year = dt->year;
    month = dt->month;
    day = dt->day;
    hour = dt->hour;
    minute = dt->minute;
    second = dt->second;
}
void Clock::readClock(){
	printf("%i /%i /%i  %i :%i :%i",day,month,year,hour,minute,second);
}