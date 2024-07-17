CC = g++
RM = rm -f
AR = ar
CP = cp
MAKE = make
HEADER_PATH = $(ROOT)/include
LIB_PATH = $(ROOT)/lib
BIN_PATH = $(ROOT)/bin
SRC_PATH = $(ROOT)/src
CCFLAGS = -g -I$(HEADER_PATH) -std=c++11 -Wall -Wconversion
LIBFLAGS = -L$(LIB_PATH)
