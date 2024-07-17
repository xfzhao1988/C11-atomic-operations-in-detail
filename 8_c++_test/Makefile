SHELL := /bin/bash

ROOT := $(word 1,$(subst /8_c++_test,/8_c++_test ,$(shell pwd)))

include $(ROOT)/include.mk

all:
	@cd $(SRC_PATH); \
	$(MAKE)

clean:
	@cd $(SRC_PATH); \
	$(MAKE) clean

echo:
	@echo "$(ROOT)"; \
	echo "$(SRC_PATH)"; \
	echo "$(MAKE)"; \
	cd $(SRC_PATH); \
	$(MAKE) echo


.PHONY: all clean echo

