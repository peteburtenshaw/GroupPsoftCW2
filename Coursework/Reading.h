#ifndef Reading_H
#define Reading_H
#include "Clock.h"
#include "mbed.h"//is this needed?

class Reading{
    
	//variables - this is a public class
	public:
	Clock clock;
	float temp;
	float humidity;
	float pressure;

	//constructor
	Reading(Clock c, float t, float p, float h);
	Reading();
	void printReading();
};
#endif