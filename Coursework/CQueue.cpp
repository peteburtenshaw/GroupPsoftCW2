#include "CQueue.h"

    
CQueue::CQueue(){
    front = 0;
    back = 0;
    maxSize = 130;
	  loopBack = false;
    storage = new Reading[maxSize];
	  counter =0;
}
   
void CQueue::push(Reading r){
    //if it is full then the front must move. if front is max then it must become 0
 	back = back +1;
	if(back == maxSize){
		back = 0;
	}	
	storage[back]=r;
	//if the queue is full then front = back
	if(front == back){
		front = front +1;
		if(front ==maxSize){
			front = 0;
		}
	}
}

void CQueue::read(int nR){// where nR is the number to read, if REAL ALL is typed then the method will be called by something like queue.read(Queue.count).

          for( int a = front; a < back; a = a + 1 ) {
						if (a==maxSize){
							loopBack = true;
							break;
						}
						counter = counter + 1;
						storage[a].printReading();
						if(counter == nR){
							break;
						}
          }
					if(loopBack == true){
						for( int a = 0; a <back; a = a + 1 ) {
							counter = counter + 1;
							storage[a].printReading();
							if(counter == nR){
								break;
							}
						
							}
					}
				printf("%i records were read.\n\r",counter);
				//set it up for next time
        loopBack = false;
				counter = 0;
    
}
void CQueue::deleteRecords(int nD){ //as above but nD is number to delete
    if(front >back){
			if(front+nD < maxSize){//if it needs to loopp to the begining
				front = front + nD; //change front pointer to nD more
			}
			else{
				nD = nD-(maxSize - front);//find the remaining to 'delete'
				front = nD;//set pointer as the remaining
			}
		}
		else{
			if((back-front)>nD){
				front = front+nD;
			}
			else{
				counter = back-front;
				front =0;
				back=0;
			}
		}
    
}   
void CQueue::readAll(){
	for( int a = front; a < back; a = a + 1 ) {
						if (a==maxSize){
							loopBack = true;
							break;
						}
						counter = counter + 1;
						storage[a].printReading();
          }
	if(loopBack == true){
		for( int a = 0; a <back; a = a + 1 ) {
				counter = counter + 1;
				storage[a].printReading();
						
				}
	}
		printf("%i records were read.\n\r",counter);
		//set it up for next time
		loopBack = false;
		counter = 0;
}
void CQueue::deleteAll(){
	
	front = 0;
	back = 0;
}