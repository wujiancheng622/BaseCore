ARCH = X86_64;
LIB = Lib64;
ifeq ($(shell getconf LONG_BIT), 32)
    ARCH = I386
	LIB = Lib32
else
    ARCH = X86_64
	LIB = Lib64
endif

PROTOBUF_PATH=../../protobuf/$(ARCH)/

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(PROTOBUF_PATH)/lib

MQOBJS	= $(patsubst %.pb.cc,  %.pb.o, $(wildcard ./LeaderElection/*.pb.cc))


DEPEND_PATH					=../../../Depend
		
		
ALL:ALLCC ALLOBJ PROTOSO PROTOSOAR


ALLCC:
	$(PROTOBUF_PATH)/bin/protoc      -I ./LeaderElection --cpp_out=./LeaderElection ./LeaderElection/*.proto
	rm -rf ./LeaderElection/*.pb.o
	
ALLOBJ:$(MQOBJS)


PROTOSO:
	g++ -fPIC  ./LeaderElection/*.pb.o -shared -o  ./$(LIB)/libElectionCoreBase.so	
	
PROTOSOAR:
	ar crvs ./$(LIB)/libElectionCoreBaseAr.a ./LeaderElection/*.pb.o
	
	
%.pb.o:%.pb.cc
	g++ -fPIC  -I$(PROTOBUF_PATH)/include  -L$(PROTOBUF_PATH)/lib   -c $< -o $@	

clean:

	
		
		
# ALL:libElectionCoreBaseAr.a libElectionCoreBase.so
		
# HEADFILES=\
		# $(wildcard ./LeaderElection/*.h) \

# SRCFILES=\
		# $(wildcard ./LeaderElection/*.cc) \

# CFLAGS += \
	# -I./LeaderElection \
	# -I$(DEPEND_PATH)/Boost/$(ARCH)/include \
	
		
# LDFLAGS += \
	# -L$(DEPEND_PATH)/Boost/$(ARCH)/lib \
	# -lboost_thread \
	# -lboost_system \
    # -ldl \
	# -lrt \
	# -luuid  \
		
# libElectionCoreBaseAr.a:$(HEADFILES) $(SRCFILES)
	# ar crvs ./$(LIB)/libElectionCoreBaseAr.a ./LeaderElection/*.pb.o

# libElectionCoreBase.so:$(HEADFILES) $(SRCFILES)
	# g++ -fPIC  $(CFLAGS)  $(LDFLAGS) ./LeaderElection/*.pb.o  -shared -o  ./$(LIB)/libElectionCoreBase.so		
	
	



