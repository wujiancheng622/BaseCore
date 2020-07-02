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


DLLTARGET=../$(LIB)/libCommonCoreBase.so

ALL: $(DLLTARGET) test

$(DLLTARGET):Singleton.cpp Coroutine.cpp Coroutine.h  OSUtil.h OSUtil.cpp
	g++ -g  -shared -fPIC   -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib   ./Singleton.cpp  ./Coroutine.cpp ./OSUtil.cpp -L../$(LIB) -I../Threads  -lboost_system  -lboost_thread  -lThreadCoreBase   -o $(DLLTARGET)
	
	
test:	main.cpp Coroutine.cpp Coroutine.h
	g++ -g -I./  -L../$(LIB)/  ./main.cpp ./Coroutine.cpp  -lCommonCoreBase  -o test
	

clean:
	rm $(DLLTARGET)

cleanCurDir:
	rm *.a  *.so *.o
