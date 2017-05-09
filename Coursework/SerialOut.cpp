#include "SerialOut.h"
Serial pc(USBTX,USBRX);
  //initialise the output string, 50 char is enough
SerialOut::SerialOut(){
	input = new char[50];
}
//this should be the only printf that is used within any threads
void SerialOut::print(){
	pc.printf("%s",input);    
}