
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

ifeq ($(OS),Windows_NT)
	LIBS+=-lkernel32
else
	LIBS+=-lpthread
endif

all: $(OBJECTS)
	$(MFCC) \
	$(MFCCFLAGS) $(FLAGS) \
	$(MFCCDEFINES) $(DEFINES) \
	$(MFCCINCLUDES) $(INCLUDES) \
	$(UCOMMONOBJECTS) $(UVMOBJECTS) $(OBJECTS) -o $(URUNTIMENAME)$(EXEC) \
	$(MFCCLIBS) $(LIBS)

include ./../MakefragRM

outherclean:
	$(RM) $(URUNTIMENAME)$(EXEC)

include ./../MakefragCommon
