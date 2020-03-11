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

#include "../EmsServer/EmsMX.h"

const char * trim(char * chbuf){
	if(chbuf ==  NULL){
		printf("Check the Pointer is NULL\n");
		return (const char *)NULL;
	}
	else
	{
		size_t chbuflen = strlen(chbuf);
		size_t chpos = 0;
		int i=0;
		
		for(; i<chbuflen; i++){
			if( (chbuf[i] == ' ') || (chbuf[i] == '\t') ||(chbuf[i] == ',') ||(chbuf[i] == ';')||(chbuf[i] == '\n')){
				//do nothing
			}
			else{
				chbuf[chpos++] = chbuf[i];
			}
		}
		memset(&chbuf[chpos], '\0', i-chpos);
		printf("domain name : %s\n", chbuf);
		return chbuf;
	}
		
};

int getDomainList(const char * dname, std::vector<string> &vecDomainList)
{
	char tmpFileBuf[NS_MAXDNAME];
	FILE *  fp = fopen(dname, "r");
	
	if(fp == NULL){
		printf("File Open failed![%s]\n", dname);
		return -1;
	}
	
	while(!feof(fp)){
	    memset((void *)&tmpFileBuf, 0, NS_MAXDNAME);
	    fgets(tmpFileBuf, NS_MAXDNAME, fp);
	    if(strlen(tmpFileBuf) == 0){
	      //printf("=====> END\n");
	      break;
	    }
	    printf("Read : %s", tmpFileBuf);
	    
	    vecDomainList.push_back(trim(tmpFileBuf));
	}
	fclose(fp);	
	
	vector<string>::iterator itr_str = vecDomainList.begin();
	for(int i=1;itr_str != vecDomainList.end(); i++, itr_str++){
		printf("[%03d]%s\n", i, itr_str->c_str());
	}
	
	return 0;
};

int main (int argc, char *argv[])
{
	const char * dnames ="nslist.txt";
	std::vector<string> vecDomainList;
	getDomainList(dnames, vecDomainList);
	printf("=================\n");
//	return 0;
	//const char * dname = "gabia.com";
	//const char * dname = "naver.com";
	if (argc < 2 ) {
		cout << "Input Domain Server Name! " << endl;
		return 0;
	}
	
	const char * dname = argv[1];
	
	CEmsMX emsmx(dname);
	int retval = 0;
	if((retval = emsmx.MXLookup(dname) ) < 0){
		cout << "MXLookup Failed : " << retval <<  endl;
		return 0;
	}
	vecMXList * theMXList = emsmx.getMXList();
	
	cout <<  "emsmx : Domain Name : " << (const char*)emsmx.getDomainName().c_str() << endl;
	
	//typedef  std::vector<boost::shared_ptr<MXRecord> > vecMXList;
	vecMXList::iterator itr_mxlist = theMXList->begin();
	cout << " List Size :  "<<  theMXList->size() << endl;
		
	for(int i =0; itr_mxlist != theMXList->end(); itr_mxlist++, i++){
		cout <<  "[" << i << "][pref : " << (int)(*itr_mxlist).get()->_ns_pref 
		     << "][ NS name : " << (const char*)((*itr_mxlist).get()->_ns_name.c_str()) 
		     << "][ NS IP addr :" << (char*)((*itr_mxlist).get()->_ns_addr) << "]"<< endl;
	}
		
	return 0;

}

