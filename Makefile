# use standard libraries. if libhid is requested, use MakefileLibhid

USBACCESSFILES = USBaccessBasic.o USBaccess.o
USBACCESSHEADER = USBaccessDevTypes.h USBaccess.h USBaccessBasic.h

all: USBaccess.a lampCtrl

lampCtrl:  lampCtrl.cpp $(USBACCESSFILES) $(USBACCESSHEADER)
	gcc -g -DCLEWARELINUX -c USBaccessBasic.c $(CFLAGS) -o USBaccessBasic.o
	g++ -g -DCLEWARELINUX -c USBaccess.cpp $(CFLAGS) -o USBaccess.o
	g++ -g -DCLEWARELINUX -c lampCtrl.cpp $(CFLAGS) -o lampCtrl.o
	g++ -g $(USBACCESSFILES)  lampCtrl.o -o lampCtrl