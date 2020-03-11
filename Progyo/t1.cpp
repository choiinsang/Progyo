#include <iostream>
#include <stdio.h>
#include <string.h>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{

printf("'test'\n");
return 0;
	boost::shared_ptr<string> testsp;
	string * pspstr = testsp.get();

	if(pspstr == NULL)
		printf("_NULL\n");
	else
		printf("_Not NULL\n");

for(int i=0; i<200; i++){
 printf("%d, %c\n", 90+i-'0', 90+i - '0');
}
	return 0;
}
