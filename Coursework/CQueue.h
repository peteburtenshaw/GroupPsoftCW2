#ifndef CQueue_H
#define CQueue_H
#include "Reading.h"
 
class CQueue{
       //variables 
       public: 
       int maxSize;
       int front;
       int back;
       int count;
       bool loopBack;
       Reading *storage;
			 int counter;
       
       
       //realisticly what we need::
       //read values taking argument n
       //read values taking no argument 
       //take value and put it in the right place
       //delete with argument
       //delete without argument
       
       CQueue();
       void push(Reading r);
       void read(int nR); // where nR is the number to read, if REAL ALL is typed then the method will be called by something like queue.read(queue.count).
       void deleteRecords(int nD); //as above but nD is number to delete
			 void readAll();
			 void deleteAll(); //delete all records
			 
           
};
#endif