#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <resolv.h>
#include <string.h>
#include <errno.h>
#include <vector>
#include <netdb.h>
#include <boost/shared_ptr.hpp>


using namespace boost;
using namespace std;

class testsp{
public:
	testsp(const char * initch="test"){ memcpy(m_name, initch, strlen(initch)); m_test=strlen(m_name);};
	~testsp(){};
	
	int m_test;
	char m_name[64];
};

int Compare(const void *A, const void *B)
{
//	 int a = (*(MXRef)A)->pref;
//   int b = (*(MXRef)B)->pref;
	 int a = *((int*)A);
   int b = *((int*)B);

   if (a < b)
      return -1;
   else if (a > b)
      return  1;
   else
      return  0;
}

int main (int argc, char *argv[])
{
	boost::shared_ptr<testsp> spclass  = boost::shared_ptr<testsp>(new testsp("melong"));
	
	boost::shared_ptr<testsp> spclass_tmp = spclass;
	printf("(B)spclass_org : %s\n",spclass.get()->m_name);
	printf("(B)spclass_tmp : %s\n",spclass_tmp.get()->m_name);
	
	spclass.reset(new testsp("lalalalalala"));
	printf("(A)spclass_org : %s\n",spclass.get()->m_name);
	printf("(A)spclass_tmp : %s\n",spclass_tmp.get()->m_name);
	
	
	boost::shared_ptr<int> sp_int = boost::shared_ptr<int>(new int);
	*sp_int.get()=12345;
	
cout << "test  main" << endl;
cout << *sp_int.get() << endl;

vector<int> vectest;

vectest.push_back(5);
vectest.push_back(7);
vectest.push_back(4);
vectest.push_back(3);
vectest.push_back(6);
vectest.push_back(9);
qsort((void*)&vectest[0], vectest.size()-1, sizeof(int), Compare);

for(int i=0; i < vectest.size(); i++){
	cout << vectest[i] << endl;
}


  return 0;
}

