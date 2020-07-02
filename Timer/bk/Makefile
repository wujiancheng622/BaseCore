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



DEPEND_PATH					=../../../Depend
	

DLLTARGET=../$(LIB)/libTimerCoreBase.so

All:$(DLLTARGET) Test


$(DLLTARGET):./Timer.cpp ./Timer.h
	g++   -g -shared -fPIC   -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib   ./Timer.cpp  -L./  -I./  -L../$(LIB) -I../Threads -lboost_system  -lboost_thread  -lThreadCoreBase  -lNetCoreBase       -lboost_chrono -lboost_date_time -lboost_thread  -lboost_system -o $(DLLTARGET)

Test:./main.cpp
	g++   -g -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib -L$(DEPEND_PATH)/BaseCore/$(LIB)   -L./ ./main.cpp -lTimerCoreBase -lThreadCoreBase  -lboost_chrono -lboost_date_time -lboost_thread  -l boost_system -o ./Test
	
clean:
	rm $(DLLTARGET)
	rm ./Test	
