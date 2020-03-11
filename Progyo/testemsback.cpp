#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <resolv.h>
#include <string.h>
#include <errno.h>

//#include <boost/unordered/unordered_map.hpp>
//#include "../EmsServer/EmsMX.h"
#include <boost/shared_ptr.hpp>


using namespace boost;
using namespace std;


bool getMXfromDNS(const char * dname){
       if(dname != NULL){
          u_char nsbuf[4096]={0,};
          char dispbuf[4096]={0,};
          ns_msg msg;
          ns_rr rr;
          int  j;
          int  l=0; // return value
	
          printf ("%s :\n", dname);
          l = res_query (dname, C_IN, T_MX, nsbuf, sizeof (nsbuf));
          cout << "Return res_query : " << l << endl;
          if (l == -1) {
             perror (dname);
          } else {
#ifdef USE_PQUERY
/* this will give lots of detailed info on the request and reply */
          res_pquery (&_res, nsbuf, l, stdout);
#else
/* just grab the MX answer info */
              const size_t size = NS_MAXDNAME;
              const u_char *data = NULL;
              HEADER *hdr = reinterpret_cast<HEADER*> (nsbuf);
              int question = ntohs (hdr->qdcount);
              int answers = ntohs (hdr->ancount);
              int nameservers = ntohs (hdr->nscount);
              int addresscords = ntohs (hdr->arcount);
              cout << "question: " << question << endl;
              cout << "answers : " << answers << endl;
              cout << "namesvr : " << nameservers << endl;
              cout << "addresscodes: " << addresscords << endl;
              
              int ll = ns_initparse (nsbuf, l, &msg);
              cout << "message Count(1) : " <<  ll << endl;
              //l = ns_msg_count (msg, ns_s_an);
                for (int i = 0; i < question; ++i) {
                  ns_rr rr;
                  //int ak = ns_parserr (&msg, ns_s_qd, i, &rr);
                  int ak = ns_parserr (&msg, ns_s_an, i, &rr);
                  if (ak == -1) {
                     std::cerr << errno << " " << strerror (errno) << "\n";
                     return 1;
                  }
                  std::cout << "question " << ns_rr_name (rr) << " "
                            << ns_rr_type (rr) << " " << ns_rr_class (rr) << endl;
       
                    cout <<  "NS_MAXDNAME : " << NS_MAXDNAME << endl;
                    unsigned char name[size];
                   data = ns_rr_rdata(rr);
                    int pref = ns_get16(data);
                    ns_name_unpack(nsbuf, nsbuf+l, data+sizeof(u_int16_t), name, size);
                    char name2[size];
                    ns_name_ntop(name, name2, size);
                    std::cout << "1)name : " << name << endl;
                    std::cout << "1)name2: " << name2  << endl;
                    data = ns_rr_rdata(rr);
                    pref = ns_get16(data);
                    ns_name_unpack(nsbuf, nsbuf+l, data+sizeof(u_int16_t), name, size);
                    ns_name_ntop(name, name2, size);
                    std::cout << "2)name : " << name << endl;
                    std::cout << "2)name2: " << name2  << endl;
                 }

              int  k = 0;
              for (j = 0; j < answers; j++) {
                k = ns_parserr (&msg, ns_s_ns, j, &rr);
                cout << "1)ns_rr_name " << ns_rr_name(rr) << endl;
                cout << "2)ns_rr_type " << ns_rr_type(rr) << endl;
                cout << "3)ns_rr_class " << ns_rr_class(rr) << endl;
                cout << "4)ns_rr_ttl " << ns_rr_ttl(rr) << endl;

                data = ns_rr_rdata(rr);
                //cout << "data : " << data << endl;
                cout <<  "NS_MAXDNAME : " << NS_MAXDNAME << endl;
                unsigned char name[size];
                int t = ns_rr_type(rr);
                cout << "t : " << t << " : " << " T_MX : "<< T_MX << " T_A : "<< T_A  << " T_NS : "<< T_NS << endl;

                if(t == T_MX){
                  cout <<  "NS_MAXDNAME : " << NS_MAXDNAME << endl;
                  int pref = ns_get16(data);
                  ns_name_unpack(nsbuf, nsbuf+l, data+sizeof(u_int16_t), name, size);
                  char name2[size];
                  ns_name_ntop(name, name2, size);
                  std::cout << "pref : " << pref << endl;
                  std::cout << "name : " << name << endl;
                  std::cout << "name2: " << name2  << endl;
                }
                else if (t == T_NS) {
                  ns_name_unpack (nsbuf, nsbuf + l, data, name, size);
                  char name2[size];
                  ns_name_ntop (name, name2, size);
                  std::cout << "T_NS : " << name2 << endl;
                }

                int nssplen = ns_sprintrr (&msg, &rr, NULL, NULL, dispbuf, sizeof (dispbuf));
                //printf("(2)message  : %s\n", rr.name);
                printf ("[%d]%s\n", nssplen, dispbuf);
            }
#endif
          }
	
	  return true;
	}
	else 
		return false;
}
	
int main (int argc, char *argv[])
{
	const char * dname = "gabia.com";
	shared_ptr<char> m_spDomainName;
	
		int    nameLen = strlen(dname);
		char * tmpDomainName = new char[nameLen+1] ;
		memset(tmpDomainName,'\0', (nameLen+1));

		strcpy(tmpDomainName, dname);
	
		if(m_spDomainName.get() != NULL){
			cout << "reset" << endl;
			m_spDomainName.reset(tmpDomainName);
		}
		else{
			cout << "push" << endl;
			m_spDomainName.reset(tmpDomainName);
		}
		const char  * tmpcname = m_spDomainName.get() ;
		cout << "Domain Name : " << tmpcname<< endl;
		
		getMXfromDNS(dname);

	return 0;
	
/*	CEmsMX tmpEms;
//	getchar();
//	for(int i=0; i< 1000000; i++){
//		tmpEms.setDomainName("testmdhkshdkfhkdhfkshfkdjhfkhdkfjhskdhfksjdhkfhdfkjsdhf");
//		usleep(10000);
//	}

	unordered_map< const char*, CEmsMX > MXList;
	MXList.insert(pair<const char*, CEmsMX >("test domain", tmpEms)); 
	cout << " insert MXList : " << MXList.size() << endl;
	
	unordered_map< const char*, CEmsMX >::iterator itr_map = MXList.begin();
	cout << " 1) " << (*itr_map).first << endl;
	cout << " 2) " << itr_map->first << endl;
	
	//boost::shared_ptr<char*> pNametest = boost::shared_ptr<char*>(new char[strlen((char*)itr_map->first)+1]);
	boost::shared_ptr<char> pNametest = boost::shared_ptr<char>(new char[strlen((char*)itr_map->first)+1]);
	strcpy( (char*)pNametest.get(), (const char*)itr_map->first);
	pNametest.get()[strlen(itr_map->first)]='\0';
	cout << pNametest.get() << endl;
  return 0;
*/
//    u_char nsbuf[4096];
//    char dispbuf[4096];
//    ns_msg msg;
//    ns_rr rr;
//    int i, j, l;
//
//    if (argc < 2) {
//        printf ("Usage: %s <domain>[...]\n", argv[0]);
//        exit (1);
//    }
//
//    for (i = 1; i < argc; i++) {
//        l = res_query (argv[i], ns_c_any, ns_t_mx, nsbuf, sizeof (nsbuf));
//        if (l < 0) {
//            perror (argv[i]);
//        } else {
//#ifdef USE_PQUERY
///* this will give lots of detailed info on the request and reply */
//            res_pquery (&_res, nsbuf, l, stdout);
//#else
///* just grab the MX answer info */
//            ns_initparse (nsbuf, l, &msg);
//            printf ("%s :\n", argv[i]);
//            l = ns_msg_count (msg, ns_s_an);
//            printf("message Count : %d\n", l);
//            for (j = 0; j < l; j++) {
//                ns_parserr (&msg, ns_s_an, j, &rr);
//            printf("(1)message  : %d\n", msg._rrnum);
//                ns_sprintrr (&msg, &rr, NULL, NULL, dispbuf, sizeof (dispbuf));
//            //printf("(2)message  : %s\n", rr.name);
//                printf ("%s\n", dispbuf);
//            }
//#endif
//        }
//    }
//
//    exit (0);
}

