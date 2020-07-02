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


DLLATRGET=../$(LIB)/libThreadCoreBase.so


ALL: $(DLLATRGET)

$(DLLATRGET):ThreadCoreBase.cpp ThreadCoreBase.h ./Mutex.cpp ./Mutex.h ./CommandBase.cpp  ./MsgTarget.cpp ./CommandBase.h  ./MsgTarget.h   ./Condition.h  ./Condition.cpp ./ThreadPool.h  ./ThreadPool.cpp
	g++ -g -shared -fPIC  -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib  -I../Common ./CommandBase.cpp  ./MsgTarget.cpp ./Mutex.cpp  ./ThreadCoreBase.cpp  ./ThreadPool.cpp ./Condition.cpp -lboost_thread  -lboost_system  -lboost_chrono  -lboost_date_time  -o $(DLLATRGET)
		
clean:
	rm $(DLLATRGET)

cleanCurDir:
	rm *.a  *.so *.o
