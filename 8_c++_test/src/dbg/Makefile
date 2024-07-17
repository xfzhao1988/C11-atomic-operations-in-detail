SHELL := /bin/bash

ROOT = $(word 1,$(subst /8_c++_test,/8_c++_test ,$(shell pwd)))

include $(ROOT)/include.mk

CC = gcc
sources = $(wildcard *.c)
headers = $(wildcard *.h)
objects = $(sources:.c=.o)
depens = $(objects:.o=.d)

target = libdbg.a

$(target): $(objects)
	$(AR) rv $@ $^; \
	cp $(target) $(LIB_PATH); \
	cp $(headers) $(HEADER_PATH); \
	$(RM) *.o; \
	$(RM) *.d; \
	$(RM) $(target)

%.o:%.c
	$(CC) -g -o $@ -c  $<

include $(depens)

define gen_depens
set -e; \
$(RM) $(depens); \
$(CC) -MM $< > $@.$$$$; \
sed 's,\($*\)\.o[ :]*,\1.o $@: ,g' < $@.$$$$ > $@; \
$(RM) $@.$$$$
endef

%.d:%.c
	$(gen_depens)


.PHONY: clean echo

echo:
	@echo "$(sources)"
	@echo "$(objects)"
	@echo "$(depens)"
	@echo "$(AR)"
	@echo "$(CP)"
	@echo "$(LIB_PATH)"
	@echo "$(HEADER_PATH)"

clean:
	$(RM) $(target) $(objects) $(depens); \
	$(RM) *.o; \
	$(RM) *.d; \
	cd $(LIB_PATH) && $(RM) $(target); \
	cd $(HEADER_PATH) && $(RM) $(headers)
