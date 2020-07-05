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

TARGET =mqttclient

DEPEND_PATH					=../../../Depend
	
All:$(TARGET)


#g++ -g  ./publication.cpp -I./include -L./lib  -lpaho-mqtt3c -o publication
#g++ -g  ./subscription.cpp -I./include -L./lib  -lpaho-mqtt3c -o subscription


$(TARGET):./main.cpp
	g++ -g  -std=c++11 -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib -L$(DEPEND_PATH)/BaseCore/$(LIB)  -I$(DEPEND_PATH)/BaseCore/Threads  ./main.cpp ./MQTTModule.cpp -lThreadCoreBase  -lboost_chrono -lboost_date_time -lboost_thread  -l boost_system -lpaho-mqtt3c -o ./$(TARGET)
	
clean:
	rm ./$(TARGET)	
