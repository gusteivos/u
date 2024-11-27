
.PHONY: all outherclean

UASMNAME=uasm

UCOMMONPATH?=./../ucommon/
include $(UCOMMONPATH)Makefrag
INCLUDES=-I$(UCOMMONPATH)
UCOMMONOBJECTS:=$(OBJECTS)

UVMPATH?=./../uvm/
include $(UVMPATH)Makefrag
INCLUDES+=-I$(UVMPATH)
UVMOBJECTS:=$(OBJECTS)

include ./Makefrag

all: $(OBJECTS)
	$(MFCC) \
	$(MFCCFLAGS) $(FLAGS) \
	$(MFCCDEFINES) $(DEFINES) \
	$(MFCCINCLUDES) $(INCLUDES) \
	$(UCOMMONOBJECTS) $(UVMOBJECTS) $(OBJECTS) -o $(UASMNAME)$(EXEC) \
	$(MFCCLIBS) $(LIBS)

include ./../MakefragRM

outherclean:
	$(RM) $(UASMNAME)$(EXEC)

include ./../MakefragCommon
