#include "Reading.h"

Reading::Reading(Clock c, float t, float p, float h){
	clock = c;
	temp = t;
	pressure = p;
	humidity = h;
	}
Reading::Reading(){ 
	temp = 25.50;
	pressure = 1000;
	humidity = 55;
	}
void Reading::printReading(){
	clock.readClock();
	printf(" %3.1f °C %f mB %4.2f \n\r",temp,pressure,humidity);//temp pre hum
	}