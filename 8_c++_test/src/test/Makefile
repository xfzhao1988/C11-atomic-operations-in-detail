SHELL := /bin/bash

ROOT = $(word 1,$(subst /8_c++_test,/8_c++_test ,$(shell pwd)))

include $(ROOT)/include.mk

CC = g++
sources = $(wildcard *.cpp)
headers = $(wildcard *.h)
objects = $(sources:.cpp=.o)
depens = $(objects:.o=.d)

target = testc++

$(target): $(objects)
	$(CC) -o $@ $^ $(LIBFLAGS) $(CCFLAGS) -ldbg -lpthread; \
	cp $(target) $(BIN_PATH); \
	cp $(headers) $(HEADER_PATH); \
	$(RM) *.o; \
	$(RM) *.d; \
	$(RM) $(target)

%.o:%.cpp
	$(CC) -g -o $@ -c  $< $(CCFLAGS)

include $(depens)

define gen_depens
set -e; \
$(RM) $($@); \
$(CC) -MM $(CCFLAGS) $< > $@.$$$$; \
sed 's,\($*\)\.o[ :]*,\1.o $@: ,g' < $@.$$$$ > $@; \
$(RM) $@.$$$$
endef

%.d:%.cpp
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
	$(RM) $(target) $(objects) $(depens) $(depens)* \
	$(RM) *.o; \
	$(RM) *.d; \
	cd $(BIN_PATH) && $(RM) $(target); \
	cd $(HEADER_PATH) && $(RM) $(headers)
