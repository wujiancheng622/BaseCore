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

CFLAGS += \
	-I../ \
	-I$(DEPEND_PATH)/BaseCore/LogBaseCore/ \
	-I$(DEPEND_PATH)/BaseCore/Common/ \
	-I$(DEPEND_PATH)/BaseCore/Threads/ \
	-I$(BOOST_PATH)/include \
	-I /home/wujiancheng/github/Depend/argeslog4cplus/X86_64/include/include_log4cplus \
		
LDFLAGS += \
	-L$(DEPEND_PATH)/BaseCore/$(LIB) \
	-L$(DEPEND_PATH)/argeslog4cplus/$(ARCH)/lib \
	-L$(BOOST_PATH)/lib \
	-llog4cplus \
	-lLogCoreBase \
	-lThreadCoreBase \
	-lboost_system \
	-lboost_thread \
	-lboost_chrono \
	
TARGET=test	
	
$(TARGET):./logTest.cpp
	g++ logTest.cpp  $(CFLAGS) $(LDFLAGS) -o test
	
clean:
	rm $(TARGET)
