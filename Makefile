
.PHONY: all uasm uruntime uvm ucommon clean-ucommon clean-uvm clean-uruntime clean-uasm

MAKE?=make

all: ucommon uvm uruntime uasm

uasm: ucommon uvm
	$(MAKE) -C $@

uruntime: ucommon uvm
	$(MAKE) -C $@

uvm: ucommon
	$(MAKE) -C $@

ucommon:
	$(MAKE) -C $@

clean: clean-ucommon clean-uvm clean-uruntime clean-uasm

clean-ucommon:
	$(MAKE) -C ucommon clean

clean-uvm:
	$(MAKE) -C uvm clean

clean-uruntime:
	$(MAKE) -C uruntime clean

clean-uasm:
	$(MAKE) -C uasm clean
