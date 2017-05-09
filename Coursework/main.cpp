//SOFT253 Coursework - See Readme for details 27020@cent-4-009.uopnet.plymouth.ac.uk
#include "mbed.h"
#include "rtos.h" // Device header
#include <hts221.h>
#include <LPS25H.h>
#include <iostream>
#include "Clock.h"// used for date and time
//Reading class is for each reading, date and time (Clock), temperature, pressure and humidity 
#include "Reading.h"//used to store each sensor reading
#include "CQueue.h" //used to store readings
#include "SerialOut.h" //used to print to the terminal in a seperate thread
#include <String>

DigitalOut myled(LED1);
I2C i2c2(I2C_SDA, I2C_SCL);
//variables to store measuring info in - possibly redundant
float tempCelsius = 25.50;
float humi = 55;
int humiMax = 100; 
char cmd=0;
//Ticker declarations and Clock
Ticker timer;
Ticker clockDTTicker;
Clock *clockDT = new Clock();//DT stands for Date Time, this stores the 'current' time of the system. operated by ticker. Note: install ticker
SerialOut *interface = new SerialOut();
Serial pcSerial(USBTX,USBRX);

LPS25H barometer(i2c2, LPS25H_V_CHIP_ADDR);

Thread *t1;
Thread *t2;
Thread *t3;
Thread *t4;
//Mail array for meaurement data buffer
Mail<Reading,16> measureMail;
CQueue *q = new CQueue();
bool logging;
char *globalLog;

//pings the measure thread from the ticker
void pingMeasure(){
    t2->signal_set(33);
    } 
//pings the serial interface to log data if logging is on
void pingLogger(){	
	if(logging==true){
	interface->input=globalLog;
	interface->print();
	}
}
//pings the serial interface output
void pingSerialOut(){
	t4->signal_set(34);
	interface->input=globalLog;
	interface->print();
}
void callTickTock(){
	clockDT->TickTock();
}	
void measure() {

	//Thread waits for the ping from pingMeasure
	Thread::signal_wait(8);

	Reading *reading = measureMail.alloc();
	if (reading == NULL) {
		printf("reading=null");
		
		return;
	}

	reading->clock.setClock(clockDT);
	HTS221_ReadTempHumi(&tempCelsius, &humi);
	reading->temp = tempCelsius;
	reading->humidity = humi;
	barometer.get();
	reading->pressure = barometer.pressure();
	//loggerCheck("Sending reading to queue..");
	//printf("winner winner chicken dinner");

	measureMail.put(reading);

	
}
void commands(){
	bool sampling;
	float f1 =0;
	int i1 =0;
	int i2 =0;
	int i3 =0;
	char s1 [50];
	char s2 [10];
	char s3 [10];
	char s4 [10];
	char tempC;
  char userLine [30];
  int commandCounter= 0;
	//inside each successful 'search', clear 'line'. or make a counter for the langth of it and then only check
		//the number of chars inside it
	
    while(1){
        
        while(1){
            if(pcSerial.readable()){
                tempC=pcSerial.getc();
                userLine[commandCounter] = tempC;
                commandCounter = commandCounter+1;
                pcSerial.putc(tempC);
                if(tempC == 13){//try with \r
                    //strcpy(globalLog,"\n\r");
                    printf("I think you pressed enter there \n\r");
                    commandCounter=0;
                    //pingSerialOut();
                    break;
                }
            }
        }
        if(userLine[0]=='R'){
            printf("R was pressed perhaps \n\r");
            }
		//loop here
		//sscanf(line,"%s %s %s ",s1,s2,s3);
		//printf("%s %s %s\n\r",s1,s2,s3);
		/*
		--BELOW ARE STRING COMMANDS
		//USE STRNCMP INSTEAD : (strncmp (str[n],"R2xx",2) == 0) WHERE str[n] and "R2xx" are strings to compare and 2 is an int of characters to check
		if(strncmp (s1,"?",1)){
			printf("SOFT253 simple Temperature Humidity and Pressure Sensor Monitor\n\r");
			printf("Using the X-NUCLEO-IKS01A1 shield and MBED Libraries\n\r");
			}
		if(strncmp (s1,"A",1)){//Gives a reading on command
			printf("A was entered");

		}
		//readers
		if(strncmp (s1,"READ",4)){//reads all records Sends a comma separated list of all measurements. Each record shall be separated with a \n newline. Each record shall be comma separated as follows: date, time, temperature, pressure, humidity
			if (strncmp (s2,"ALL",3)){
				q->readAll();
			}
			else if (i1>0){
				q->read(i1);
			}
			else{
			printf("Are you trying to read something? try READ ALL or READ <n>");
			}
		}
		//deleters
		else if(strncmp (s1,"DELETE",6)){//deletes all records  The F401 will return a string �DELETED <N> RECORDS� N = no. deleted obviously
			if (strncmp (s2,"ALL",3)){
			//delete all
			}
			else if (i1>0){
			//delete <n> //Delete the oldest <n> records.return �DELETED <m> RECORDS� m is how many were deleted obviously
				if(i1<=q->maxSize){
					
					q->deleteRecords(q->maxSize-1);
				}
				else if(i1<1){
					printf("Please enter a positive integer");
				}
				else{
					q->deleteRecords(i1);
				}
			}
			else{
			printf("Are you trying to delete something? Try DELETE ALL or DELETE <n>");
			}
		}



		if(strncmp (s1,"SETDATE",7)){//  no points for guessing what this one does. return a string �DATE UPDATED TO <dd> <dd> <yyyy>�
			
		}
		if(strncmp (s1,"SETTIME",7)){//  nil point. return �TIME UPDATED TO <hh> <mm> <ss>�

		}
		if(strncmp (s1,"SETT",4)){// SETT <t> set sampling rate to 0.1=T=60.0  return a string �T UPDATED TO <T>� otherwise return an �OUT OF RANGE� error.
		//f1 =  std::stof( s2 );

		}
		if(strncmp (s1,"STATE",5)){//STATE <x> set sampling ON or OFF
			if(strncmp (s2,"ON",2)){
				if (sampling == false){
				timer.attach(&measure,15);
				sampling = true;
				}
			}
			else if(strncmp (s2,"OFF",3)){
				if (sampling == false){
					timer.detach();
					sampling = false;
				}
			}
		}
		if(strncmp (s1,"LOGGING",7)){// turns on/off diagnostic logging to the serial interface. The F401 will return a string �LOGGING <x>�
			if(strncmp (s2,"ON",2)){
				logging = true;
			}
			else if(strncmp (s2,"OFF",3)){
				logging = false; 
			}
		}
		*/
	}
}
	
void thread1()
	{
	Reading *pReading = new Reading();
	while (true) {
		osEvent evt = measureMail.get();
		//Check status
		if (evt.status == osEventMessage) {
			pReading = (Reading*)evt.value.p;  //This is the pointer (address)
			//Make a copy
			Reading msg(pReading->clock ,pReading->temp, pReading->humidity, pReading->pressure);//CHECKVARIABLE NAMES
			q->push(msg);
			measureMail.free(pReading);
			strcpy(globalLog,"Reading writted to queue");
			pingLogger();
		}
	}
}
void serialOut()	{
	while (true) {
		Thread::signal_wait(34);
		printf("%s \n\r",globalLog);
			/*this is the format for the logger: 
				strcpy(globalLog,"Reading writted to queue");
				pingLogger();
		
		this is the format for any printf:
		strcpy(globalLog,"Reading writted to queue");
			pingSerialOut();
		
		set input then ping it
			*/
	}
}

// main() runs in its own thread in the OS
int main() {
	
	hts221_init();
	HTS221_Calib();
	printf("START SOFT253 simple Temperature Humidity and Pressure Sensor Monitor\n\r");
	printf("Using the X-NUCLEO-IKS01A1 shield and MBED Libraries\n\r");
	globalLog = new char[50];
	logging = true;
	timer.attach( &pingMeasure, 15);
	clockDTTicker.attach(&callTickTock,1);
	printf("well something should be happening right about now\n\r");
	//Threads:
	t1 = new Thread();
	t1->start(thread1);
	t2 = new Thread();
	t2->start(measure);
	t3 = new Thread();
	t3->start(commands);
	t4 = new Thread();
	t4->start(serialOut);

	printf("Enter commands:\n\r");

	while (true){
		
	Thread::wait(5000);
	}
}