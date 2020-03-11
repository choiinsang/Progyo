#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std; 
int main(int argc, char *argv[]){
	time_t oldtime, currtime;
	time(&oldtime);
	usleep(2000000);
	time(&currtime);

	double retdval1 = difftime(currtime, oldtime);	
	double retdval2 = difftime(oldtime, currtime);	
	cout << "oldtime: " << oldtime << " currtime: " <<  currtime << endl;
	cout << "difftime: " << retdval1 << endl;
	printf("%d\n", (int)retdval1);
	cout << "difftime: " << retdval2 << endl;
	cout << "difftime: " << currtime - oldtime << endl;



	return 0;
}
