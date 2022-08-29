# use standard libraries. if libhid is requested, use MakefileLibhid

USBACCESSFILES = USBaccessBasic.o USBaccess.o
USBACCESSHEADER = USBaccessDevTypes.h USBaccess.h USBaccessBasic.h

all: USBaccess.a CLampCtrl

CLampCtrl:  CLampCtrl.cpp $(USBACCESSFILES) $(USBACCESSHEADER)
	gcc -g -DCLEWARELINUX -c USBaccessBasic.c $(CFLAGS) -o USBaccessBasic.o
	g++ -g -DCLEWARELINUX -c USBaccess.cpp $(CFLAGS) -o USBaccess.o
	g++ -g -DCLEWARELINUX -c CLampCtrl.cpp $(CFLAGS) -o CLampCtrl.o
	g++ -g $(USBACCESSFILES)  CLampCtrl.o -o CLampCtrl