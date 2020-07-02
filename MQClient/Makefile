#
# Makefile for TMS 

ARCH = X86_64;
APRPATH=include_apr;
ARRLIB=-lapr-2;
LIB = Lib64;
LOGPATH=include_log4cplus/;
ifeq ($(shell getconf LONG_BIT), 32)
    ARCH = I386
	APRPATH=include_apr
	LIB = Lib32
	ARRLIB=-lapr-1
	LOGPATH=
else
    ARCH = X86_64
	APRPATH=include_apr
	LIB = Lib64
	ARRLIB=-lapr-2
	LOGPATH=include_log4cplus/
endif

LIB_TARGET = ../$(LIB)/libMqClient.a$(FN_D)



DEPEND_PATH					=../../../Depend

##############################################################################
##############################################################################
#ActiveMQ and protobuf


MYACTIVEMQ_INCLUDE_PATH			= 	$(DEPEND_PATH)/argesActivemq/$(ARCH)/include/Activemq/
ACTIVEMQ_CPP_INCLUDE_PATH		= 	$(DEPEND_PATH)/argesActivemq/$(ARCH)/include/public/include_activemq/
APR_INCLUDE_PATH 				= 	$(DEPEND_PATH)/argesActivemq/$(ARCH)/include/public/$(APRPATH)/
HLOG_INCLUDE_PATH 				= 	$(DEPEND_PATH)/argeslog4cplus/$(ARCH)/include/$(LOGPATH)
MQ_LOG_INCLUDE_PATH				=   $(DEPEND_PATH)/argeslog4cplus/$(ARCH)/include/hlog/
PROTOBUF_INCLUDE_PATH			=   $(DEPEND_PATH)/protobuf/$(ARCH)/include/



#头文件目录
INCLUDE		= -I$(MYACTIVEMQ_INCLUDE_PATH)  -I$(ACTIVEMQ_CPP_INCLUDE_PATH)   -I$(APR_INCLUDE_PATH) -I$(HLOG_INCLUDE_PATH)  -I$(MQ_LOG_INCLUDE_PATH)  -I$(PROTOBUF_INCLUDE_PATH)

#LIB_DIR包含了所有库目录	-L:指定动态库文件路径
LIB_DIR		= -L$(DEPEND_PATH)/argesActivemq/$(ARCH)/lib  -L$(DEPEND_PATH)/argeslog4cplus/$(ARCH)/lib   -L$(DEPEND_PATH)/protobuf/$(ARCH)/lib
			
CFLAGS	= $(INCLUDE) $(LIB_DIR)  -lactivemq-cpp -lArgesActivemq $(ARRLIB) 


##-llog4cplus -lArgeslog4cplus
##############################################################################
##############################################################################




##############################################################################
##############################################################################
PROTO_LIB_PATH						= $(DEPEND_PATH)/BaseCore/Proto/$(LIB)
CFLAGS	+= -I$(DEPEND_PATH)/BaseCore/Proto/BMS  -I$(DEPEND_PATH)/BaseCore/Proto/Common    -L$(PROTO_LIB_PATH)   -lbmsproto -lcommonproto  	-lprotobuf
##############################################################################
##############################################################################




SRCS += \
		$(wildcard *.cpp) \


CFLAGS += -g -fPIC -pipe -Wall -Wno-deprecated -DLINUX

CFLAGS += \
	-I./CUHandleMdl \
	-I$(DEPEND_PATH)/Boost/$(ARCH)/include \
	-I$(DEPEND_PATH)/BaseCore/Threads \

LDFLAGS += \
	-L$(DEPEND_PATH)/BaseCore/Threads \
	-L$(DEPEND_PATH)/Boost/$(ARCH)/lib \
	-L. \
	-lThreadCoreBase \
	-lboost_thread \
	-lboost_system \
    -lssl \
    -ldl \
	-lrt \

# include template
TOP_DIR?=.
include $(TOP_DIR)/Makefile.template

