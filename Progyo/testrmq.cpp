#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "../EmsServer/EmsRMQConnect.h"

int main(int argc, char *argv[])
{
	CEmsRMQConnect emsrmqconn;
	emsrmqconn.setEmsRMQConnInfo("127.0.0.1", 5672, "fmco", "fmco1234", "/ems");
	emsrmqconn.startThread();
	
	while(true){
		static int i = 0;
		if(i++ < 30)
			usleep(THREAD_SLEEPTIME_1SEC);
		else
			break;
	}
	printf("END Main Process\n");

	return 0;
}

