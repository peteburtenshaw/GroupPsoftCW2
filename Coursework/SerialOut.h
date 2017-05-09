#ifndef SerialOut_H
#define SerialOut_H
#include "Clock.h"
#include "mbed.h"//is this needed?

class SerialOut{
	public:
	char *input;
	//constructor
	SerialOut();
	void print();
};
#endif