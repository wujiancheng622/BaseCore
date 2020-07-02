ARCH = X86_64;
LIB = Lib64;
TESTDIR=Test32
ifeq ($(shell getconf LONG_BIT), 32)
    ARCH = I386
	LIB = Lib32
	TESTDIR =Test32
else
    ARCH = X86_64
	LIB = Lib64
	TESTDIR =Test64
endif


BOOST_PATH=../../Boost/$(ARCH)

HEADFILES=TcpClientModel.h \
		./TcpServerModel.h \
		./TcpCommon.h \
		./UdpCommon.h \
		./UdpServerModel.h \
		./UdpClientModel.h \
		./NetUtils.h \

SRCFILES=TcpClientModel.cpp \
		./TcpServerModel.cpp \
		./TcpCommon.cpp \
		./UdpServerModel.cpp \
		./UdpCommon.cpp \
		./UdpClientModel.cpp  \
		./NetUtils.cpp \

	
ARCH = X86_64;
ifeq ($(shell getconf LONG_BIT), 32)
    ARCH = I386
else
    ARCH = X86_64
endif


EXE_TARGET = BPX$(FN_D)



DEPEND_PATH					=../../../Depend
			
			

DLLTARGET=../$(LIB)/libNetCoreBase.so	


##############################################################################
##############################################################################
PROTOBUF_INCLUDE_PATH			=   $(DEPEND_PATH)/protobuf/$(ARCH)/include/
PROTO_LIB_PATH						= $(DEPEND_PATH)/BaseCore/Proto/$(LIB)
CFLAGS	+= -I$(DEPEND_PATH)/BaseCore/Proto/Common  -I$(DEPEND_PATH)/BaseCore/Proto/BPX  -I$(DEPEND_PATH)/BaseCore/Proto/Gate  -I$(PROTOBUF_INCLUDE_PATH)  -L$(DEPEND_PATH)/protobuf/$(ARCH)/lib  -L$(PROTO_LIB_PATH)   -lcommonproto 
##############################################################################
##############################################################################




TcpClientTest=./$(TESTDIR)/TcpClientTest	
TcpServerTest=./$(TESTDIR)/TcpServerTest
TcpClientServerTest=./$(TESTDIR)/TcpClientServerTest	
UdpServerTest=./$(TESTDIR)/UdpServerTest	
UdpClientTest=./$(TESTDIR)/UdpClientTest			
		
ALL:$(DLLTARGET) $(TcpClientTest)

#ALL:$(DLLTARGET) $(TcpClientTest) $(UdpServerTest) $(UdpClientTest) $(TcpServerTest)


#  $(TcpClientServerTest) 

$(DLLTARGET):$(HEADFILES) $(SRCFILES)
	g++ -shared -fPIC -g  -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib  -I../Threads   -L../$(LIB)  $(SRCFILES) -l ThreadCoreBase  -l boost_system -o $(DLLTARGET)
	
	
$(TcpClientTest):TcpClientTest.cpp
	g++ -g   ./TcpClientTest.cpp  $(CFLAGS) -L./  -I./  -L../$(LIB) -I../Threads  -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib  -lboost_system  -lboost_thread  -lThreadCoreBase  -lNetCoreBase -o ./$(TcpClientTest)
	
$(TcpServerTest):TcpServerTest.cpp Parser.h Parser.cpp
	g++ -g   -L../$(LIB) $(CFLAGS) -L./  -I./  -I../Threads  -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib  -lprotobuf -lboost_system  -lboost_thread   ./TcpServerTest.cpp ./Parser.cpp -lThreadCoreBase  -lNetCoreBase -o ./$(TcpServerTest)	


$(TcpClientServerTest):TcpClientServerTest.cpp
	g++ -g   ./TcpClientServerTest.cpp $(CFLAGS) -L./  -I./  -L../$(LIB) -I../Threads -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib  -lboost_system  -lboost_thread  -lThreadCoreBase  -lNetCoreBase -o ./$(TcpClientServerTest)		
	
	
$(UdpServerTest):UdpServerTest.cpp
	g++ -g   ./UdpServerTest.cpp $(CFLAGS) -L./  -I./  -L../$(LIB) -I../Threads  -I../CommonFiles -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib  -lboost_system  -lboost_thread  -lThreadCoreBase  -lNetCoreBase -o ./$(UdpServerTest)	

$(UdpClientTest):UdpClientTest.cpp
	g++ -g   ./UdpClientTest.cpp $(CFLAGS) -L./  -I./  -L../$(LIB) -I../Threads -I../CommonFiles -I$(BOOST_PATH)/include  -L$(BOOST_PATH)/lib  -lboost_system  -lboost_thread  -lThreadCoreBase  -lNetCoreBase -o ./$(UdpClientTest)	

	
clean:
	rm $(DLLTARGET) $(TcpClientTest) $(TcpServerTest) $(TcpClientServerTest) $(UdpServerTest) $(UdpClientTest)

cleanCurDir:
	rm  ./libNetCoreBase.so
	rm  ./$(TcpClientTest)
	rm 	./$(TcpServerTest)
	rm  ./$(UdpServerTest)
	rm  ./$(UdpClientTest)
	

	
