ARCH = X86_64;
LIB = Lib64;
ifeq ($(shell getconf LONG_BIT), 32)
    ARCH = I386
	LIB = Lib32
else
    ARCH = X86_64
	LIB = Lib64
endif


BOOST_PATH=../../Boost/$(ARCH)
	

DLLTARGET=../$(LIB)/libLogCoreBase.so

All:$(DLLTARGET)  Test


$(DLLTARGET):./LogBaseCore.cpp ./LogBaseCore.h
	g++   -g -shared -fPIC  -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib  -L../$(LIB)  -I$(ARCH)/include -L$(ARCH)/lib -I../Common -I../Threads  ./LogBaseCore.cpp -lboost_system  -lboost_thread  -lThreadCoreBase -o $(DLLTARGET)
	
Test:main.cpp
	g++   -g -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib  -L../$(LIB)  -I$(ARCH)/include -L$(ARCH)/lib ./main.cpp -llog4cplus  -o ./Test

	

clean:
	rm $(DLLTARGET)
