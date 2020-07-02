ARCH = X86_64;
APRPATH=include_apr;
LIB = Lib64;
ARRLIB=-lapr-2;
ifeq ($(shell getconf LONG_BIT), 32)
    ARCH = I386
	APRPATH=include_apr
	LIB = Lib32
	ARRLIB=-lapr-1
else
    ARCH = X86_64
	APRPATH=include_apr
	LIB = Lib64
	ARRLIB=-lapr-2
endif


DEPEND_PATH					=../../../Depend
	

##############################################################################
##############################################################################
#ActiveMQ and protobuf


MYACTIVEMQ_INCLUDE_PATH			= 	$(DEPEND_PATH)/argesActivemq/$(ARCH)/include/Activemq/
ACTIVEMQ_CPP_INCLUDE_PATH		= 	$(DEPEND_PATH)/argesActivemq/$(ARCH)/include/public/include_activemq/
APR_INCLUDE_PATH 				= 	$(DEPEND_PATH)/argesActivemq/$(ARCH)/include/public/$(APRPATH)/
HLOG_INCLUDE_PATH 				= 	$(DEPEND_PATH)/argeslog4cplus/$(ARCH)/include/include_log4cplus/
MQ_LOG_INCLUDE_PATH				=   $(DEPEND_PATH)/argeslog4cplus/$(ARCH)/include/hlog/
PROTOBUF_INCLUDE_PATH			=   $(DEPEND_PATH)/protobuf/$(ARCH)/include/



#头文件目录
INCLUDE		= -I$(MYACTIVEMQ_INCLUDE_PATH)  -I$(ACTIVEMQ_CPP_INCLUDE_PATH)   -I$(APR_INCLUDE_PATH) -I$(HLOG_INCLUDE_PATH)  -I$(MQ_LOG_INCLUDE_PATH)  -I$(PROTOBUF_INCLUDE_PATH)

#LIB_DIR包含了所有库目录	-L:指定动态库文件路径
LIB_DIR		= -L$(DEPEND_PATH)/argesActivemq/$(ARCH)/lib  -L$(DEPEND_PATH)/argeslog4cplus/$(ARCH)/lib   -L$(DEPEND_PATH)/protobuf/$(ARCH)/lib
			
CFLAGS	= $(INCLUDE) $(LIB_DIR)  -lactivemq-cpp -lArgesActivemq $(ARRLIB) -llog4cplus -lArgeslog4cplus



##############################################################################
##############################################################################

	
	
TARGET=../$(LIB)/libElection.so
	
ALL:$(TARGET)
		
HEADFILES=\
		$(wildcard ./*.h) \

SRCFILES=\
		$(wildcard ./*.cpp) \

		

##############################################################################
##############################################################################
PROTOBUF_INCLUDE_PATH			=   $(DEPEND_PATH)/protobuf/$(ARCH)/include/
PROTO_LIB_PATH						= $(DEPEND_PATH)/BaseCore/Proto/$(LIB)
CFLAGS	+= -I$(DEPEND_PATH)/BaseCore/Proto/LeaderElection  -I$(PROTOBUF_INCLUDE_PATH)  -L$(DEPEND_PATH)/protobuf/$(ARCH)/lib  -L$(PROTO_LIB_PATH)  -lprotobuf
##############################################################################
##############################################################################
		
		
CFLAGS += \
	-I./ \
	-I$(DEPEND_PATH)/Boost/$(ARCH)/include \
	-I$(DEPEND_PATH)/BaseCore/Timer \
	-I$(DEPEND_PATH)/BaseCore/Threads \
	-I$(DEPEND_PATH)/BaseCore/MQClient \
		
LDFLAGS += \
	-L$(DEPEND_PATH)/Boost/$(ARCH)/lib \
	-L$(DEPEND_PATH)/BaseCore/$(LIB) \
	-lTimerCoreBase \
	-lThreadCoreBase \
	-lMqClient \
	-lboost_thread \
	-lboost_system \
	-ldl \
	-lrt \
	-luuid  \
		
$(TARGET):$(HEADFILES) $(SRCFILES)
	g++ -fPIC $(SRCFILES)  $(CFLAGS)  $(LDFLAGS)   -shared -Wall  -o  ./$(TARGET)		
	

	
	

clean:
	rm $(TARGET)

