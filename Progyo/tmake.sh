#!/bin/sh
  
#	echo -n "make $1 "


	case "$1" in
	    "emsmx")
		g++ -o tmx -lresolv -g  testemsmx.cpp ../NetTemplate/LockObject.h ../NetTemplate/LockObject.cpp ../Common/INIFile.h ../Common/INIFile.cpp ../EmsServer/EmsConfig.h ../EmsServer/EmsConfig.cpp  ../EmsServer/EmsMX.h ../EmsServer/EmsMX.cpp
			;;
	    "mxmanager")
		g++ -o tmxmanager -lresolv -g -D__LINUX__ \
			-I./  -I/usr/local/include -I/usr/local/mysql/include -I../NetTemplate -I../Libgabia/inc -I../Common -I../EmsServer  -lpthread  -lm \
			../Common/INIFile.h           ../Common/INIFile.cpp         \
			../NetTemplate/Log.h          ../NetTemplate/Log.cpp        \
			../NetTemplate/CClientEpoll.h ../NetTemplate/CClientEpoll.cpp \
			../NetTemplate/CRequest.h                                   \
			../NetTemplate/MyClient.h     ../NetTemplate/MyClient.cpp   \
			../NetTemplate/CMyRequest.h   ../NetTemplate/CMyRequest.cpp \
			../NetTemplate/LockObject.h   ../NetTemplate/LockObject.cpp \
			../EmsServer/EmsConfig.h      ../EmsServer/EmsConfig.cpp    \
			../EmsServer/EmsDefine.h                                    \
			../EmsServer/EmsMX.h          ../EmsServer/EmsMX.cpp        \
			../EmsServer/EmsMXManager.h   ../EmsServer/EmsMXManager.cpp \
			testmxmnger.cpp 
		;;
	    "mqmanager")
		;;
	    "testrmq")
		  g++ -o emsrmq testrmq.cpp -g \
		  -I/home/frole/newEMS/neoEMS/src/EmsServer/amqpcpp-master/include \
		  -L/usr/lib64 -lrabbitmq ../EmsServer/amqpcpp-master/libamqpcpp.a  \
		  ../EmsServer/amqpcpp-master/include/AMQPcpp.h \
		  ../EmsServer/amqpcpp-master/src/AMQP.cpp \
		  ../EmsServer/amqpcpp-master/src/AMQPBase.cpp \
		  ../EmsServer/amqpcpp-master/src/AMQPException.cpp \
		  ../EmsServer/amqpcpp-master/src/AMQPMessage.cpp \
		  ../EmsServer/amqpcpp-master/src/AMQPExchange.cpp \
		  ../EmsServer/amqpcpp-master/src/AMQPQueue.cpp \
		  ../EmsServer/EmsRMQConnect.h ../EmsServer/EmsRMQConnect.cpp
		;;
	    "soa")
		  g++ -o soarun testsoa.cpp -g -L/usr/lib64 -lbind9
		;;
	    "ttest")		
		g++ -o thtest  ttest.cpp -lpthread
		;;
			*)
	        echo "$0 [emsmx|mxmanager|mqmanager|...]"
		;;
        esac
   
