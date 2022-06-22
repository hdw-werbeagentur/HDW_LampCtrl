# use standard libraries. if libhid is requested, use MakefileLibhid

USBACCESSFILES = USBaccessBasic.o USBaccess.o
USBACCESSHEADER = USBaccessDevTypes.h USBaccess.h USBaccessBasic.h

all: USBaccess.a test

test:  test.cpp $(USBACCESSFILES) $(USBACCESSHEADER)
	gcc -g -DCLEWARELINUX -c USBaccessBasic.c $(CFLAGS) -o USBaccessBasic.o
	g++ -g -DCLEWARELINUX -c USBaccess.cpp $(CFLAGS) -o USBaccess.o
	g++ -g -DCLEWARELINUX -c test.cpp $(CFLAGS) -o test.o
	g++ -g $(USBACCESSFILES)  test.o -o test