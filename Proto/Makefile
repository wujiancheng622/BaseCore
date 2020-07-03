ARCH = X86_64;
LIB = Lib64;
ifeq ($(shell getconf LONG_BIT), 32)
    ARCH = I386
	LIB = Lib32
else
    ARCH = X86_64
	LIB = Lib64
endif

ALL:
	make -f ./Common/Makefile
	cp -rf ./$(LIB)/* ../$(LIB)
	
	
clean:
	rm ./$(LIB)/*
	rm ../$(LIB)/libcommonproto.so
	
cleanCurDir:
	make -f ./BMS/Makefile clean
	make -f ./Common/Makefile clean

	

