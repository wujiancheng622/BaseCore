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

MQOBJS	= $(patsubst %.pb.cc,  %.pb.o, $(wildcard ./Common/*.pb.cc))


ALL:ALLCC ALLOBJ PROTOSO PROTOSOAR


ALLCC:
	$(PROTOBUF_PATH)/bin/protoc      -I ./Common --cpp_out=./Common ./Common/*.proto
	rm -rf ./Common/*.pb.o
	
	
ALLOBJ:$(MQOBJS)


PROTOSO:
	g++ -fPIC  ./Common/*.pb.o -L$(PROTOBUF_PATH)/lib -lprotobuf  -shared -o  ./$(LIB)/libcommonproto.so	
	
		
PROTOSOAR:
	ar crvs ./$(LIB)/libcommonproto.a ./Common/*.pb.o
	
	
	
%.pb.o:%.pb.cc
	g++ -fPIC  -I$(PROTOBUF_PATH)/include  -L$(PROTOBUF_PATH)/lib -lprotobuf  -c $< -o $@	

clean:
	rm ./Common/*.o 
