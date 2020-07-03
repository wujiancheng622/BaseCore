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

MQOBJS	= $(patsubst %.pb.cc,  %.pb.o, $(wildcard ./BPX/*.pb.cc))


ALL:ALLCC ALLOBJ PROTOSO


ALLCC:
	$(PROTOBUF_PATH)/bin/protoc      -I ./BPX --cpp_out=./BPX ./BPX/*.proto
	rm -rf ./BPX/*.pb.o
	
ALLOBJ:$(MQOBJS)


PROTOSO:
	g++ -fPIC  ./BPX/*.pb.o -shared -o  ./$(LIB)/libbpxproto.so	
	
	
%.pb.o:%.pb.cc
	g++ -fPIC  -I$(PROTOBUF_PATH)/include  -L$(PROTOBUF_PATH)/lib   -c $< -o $@	

clean:
	rm ./BPX/*.o 
	rm ./$(LIB)/libbpxproto.so 
