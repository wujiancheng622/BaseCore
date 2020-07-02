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
	-I$(DEPEND_PATH)/BaseCore/Threads \
	-I$(DEPEND_PATH)/BaseCore/Common \
	-I$(DEPEND_PATH)/BaseCore/LogBaseCore/$(ARCH)/include \
		
LDFLAGS += \
	-I$(DEPEND_PATH)/BaseCore/LogBaseCore/$(ARCH)/lib \
	-L$(DEPEND_PATH)/BaseCore/$(LIB) \
	-L/mnt/hgfs/SVN-2/TPX/Src/code/Depend/argeslog4cplus/X86_64/lib \
	-llog4cplus \
	-lLogCoreBase \
	
TARGET=test	
	
$(TARGET):./logTest.cpp
	g++ logTest.cpp  $(CFLAGS) $(LDFLAGS) -o test
	
clean:
	rm $(TARGET)
