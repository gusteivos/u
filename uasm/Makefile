
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
	$(CCALL) $(UCOMMONOBJECTS) $(UVMOBJECTS) $(OBJECTS) -o $(UASMNAME)$(EXEC)

include ./../MakefragRM

outherclean:
	$(RM) $(UASMNAME)$(EXEC)

include ./../MakefragCommon
