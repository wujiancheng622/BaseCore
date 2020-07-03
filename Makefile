#
# Makefile for TMS_TPX



LIB = Lib64;
ifeq ($(shell getconf LONG_BIT), 32)
	LIB = Lib32
else
	LIB = Lib64
endif


#Proto 

SUBPRJ = \
	MQClient \
	Threads \
	Network \
	Timer \
	Common \
	Election \
	#LogBaseCore \


SUBPRJ_CLEAN = $(foreach s,$(SUBPRJ),$(s)_clean)

.PHONY : all clean test test_clean $(SUBPRJ) $(SUBPRJ_CLEAN)

all : $(SUBPRJ)
	cp -rf ./$(LIB)/* ../$(LIB)

clean : $(SUBPRJ_CLEAN)

test :
	$(MAKE) -C test

test_clean :
	$(MAKE) -C test clean


$(SUBPRJ) :
	$(MAKE) -C $@ 
	

$(SUBPRJ_CLEAN) :
	$(MAKE) -C $(subst _clean,,$@) -i clean || exit "$$?"
