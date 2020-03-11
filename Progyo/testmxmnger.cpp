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
#include <boost/unordered_map.hpp>

#include "../EmsServer/EmsMXManager.h"

using namespace boost;
using namespace std;

typedef boost::shared_ptr<CEmsMX> spEMSMX;
typedef unordered_map< string, spEMSMX> mapMXList;

//class CMXManager;

//int makeMX (const char * dname)
//{
//	//const char * dname = "gabia.com";
//	//const char * dname = "naver.com";
//	const char * dname = "gmail.com";
//	
//	CEmsMX emsmx(dname);
//	int retval = 0;
//	if((retval = emsmx.MXLookup(dname) ) < 0){
//		cout << "MXLookup Failed : " << retval <<  endl;
//		return 0;
//	}
//	vecMXList * theMXList = emsmx.getMXList();
//	
//	cout <<  "emsmx : Domain Name : " << (char*)emsmx.getDomainName().c_str() << endl;
//	
//	//typedef  std::vector<boost::shared_ptr<MXRecord> > vecMXList;
//	vecMXList::iterator itr_mxlist = theMXList->begin();
//	cout << " List Size :  "<<  theMXList->size() << endl;
//		
//	for(int i =0; itr_mxlist != theMXList->end(); itr_mxlist++, i++){
//		cout <<  "[" << i << "][pref : " << (int)(*itr_mxlist).get()->_ns_pref 
//		     << "][ NS name : " << (char*)((*itr_mxlist).get()->_ns_name.get()) 
//		     << "][ NS IP addr :" << (char*)((*itr_mxlist).get()->_ns_addr) << "]"<< endl;
//	}
//		
//	return 0;
//
//}


int main (int argc, char *argv[])
{
	theMXManager();
//	vector<string> dnslist;
//	theMXManager()->getFromDomainList(argv[1], dnslist);
//	int errCode = 0; // 0 is no error
//	
//	for(int i=0; i< dnslist.size(); i++){
//		printf( "sizeof DNS List : %s\n", dnslist[i].c_str());
//		theMXManager()->insertMXList(dnslist[i].c_str(), errCode);
//	}
//	
//	
//	mapMXList * mxList = theMXManager()->getMXList();
//	printf( "sizeof MXList : %d\n", mxList->size());
//	mapMXList::iterator itr = mxList->begin();
//	for(;itr != mxList->end(); itr++){
//		boost::shared_ptr<CEmsMX>  tmpEmsMX = itr->second;
//		vecMXList *  tmpNSMXList = tmpEmsMX.get()->getMXList();
//		vecMXList::iterator itr_ns =  tmpNSMXList->begin();
//		
//		cout <<" === Domain Name : "  <<  itr->first << endl;
//		for(; itr_ns != tmpNSMXList->end(); itr_ns++){
//			sptr_MX tmpsptrmx = *itr_ns;
//			cout <<"[ " << tmpsptrmx.get()->_ns_pref << " ][ " <<   tmpsptrmx.get()->_ns_name.c_str() <<  " / " << tmpsptrmx.get()->_ns_addr << " ]" << endl;
//		}
//	}
//	

int i=0;
while(true){
	usleep(1000000);
	if(i++ > 130)
		break;	
}
		
	return 0;

}
