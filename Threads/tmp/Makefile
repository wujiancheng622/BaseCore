CFLAGS=-Wall -L.
LIBCFLAGS= $(CFLAGS) -fPIC
CC=g++
OBJS=main.o
LIBOBJS=say_hello.o say_world.o
AR=ar rc
LIBRARY=libhelloworld.so

all:main

main:$(OBJS) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lhelloworld

$(LIBRARY):$(LIBOBJS)
	$(CC) -shared -o $@ $(LIBOBJS) 
	
	
main.o:main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

%.o:%.cpp
	$(CC) $(LIBCFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS) $(LIBRARY) $(LIBOBJS)  main

