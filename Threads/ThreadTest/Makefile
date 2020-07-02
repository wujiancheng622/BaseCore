ARCH = X86_64;
LIB = Lib64;
ifeq ($(shell getconf LONG_BIT), 32)
    ARCH = I386
	LIB = Lib32
else
    ARCH = X86_64
	LIB = Lib64
endif


BOOST_PATH=../../../Boost/$(ARCH)



DEPEND_PATH					=../../../../Depend
	

All:$(DLLTARGET) Test

Test:./main.cpp
	g++   -g -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib -L$(DEPEND_PATH)/BaseCore/$(LIB)  -I../ -L./ ./main.cpp  -lThreadCoreBase  -lboost_chrono -lboost_date_time -lboost_thread  -l boost_system -o ./Test
	
clean:
	rm ./Test	
