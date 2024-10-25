
.PHONY: all outherclean

URUNTIMENAME=uruntime

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
	$(CCALL) $(UCOMMONOBJECTS) $(UVMOBJECTS) $(OBJECTS) -o $(URUNTIMENAME)$(EXEC)

include ./../MakefragRM

outherclean:
	$(RM) $(URUNTIMENAME)$(EXEC)

include ./../MakefragCommon
