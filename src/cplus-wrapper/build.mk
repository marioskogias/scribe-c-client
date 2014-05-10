UNAME=$(shell uname)
CURRENT_DIR = $(shell pwd)

DLIB=libscribe_client.so

CC = gcc
CXX = g++
CFLAGS=-fPIC -g -pipe -m64

THRIFT_INCLUDES=-I/usr/local/include/thrift -I/usr/local/include/thrift/fb303
COMMON_LDFLAGS= -L/usr/lib64
SHARED_LDFLAGS=-shared

CPP_INCLUDES= $(THRIFT_INCLUDES) -I$(CURRENT_DIR)/gen-cpp
CPP_LDFLAGS=-lthrift -lfb303 -levent -lpthread -lboost_system

INCLUDES := $(CPP_INCLUDES) -I$(CURRENT_DIR)
LDFLAGS := $(MYSQL_FLAGS) $(COMMON_LDFLAGS) $(C_LDFLAGS) $(CPP_LDFLAGS) 

CPP_DIRECTORIES= gen-cpp lib
CPP_OBJFILES= $(patsubst %.cpp, %.o, $(foreach SUBDIRECTORIES, $(CPP_DIRECTORIES), $(wildcard $(SUBDIRECTORIES)/*.cpp)))

all: clean $(DLIB)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(DLIB): $(CPP_OBJFILES) 
	$(CC) $(SHARED_LDFLAGS) -o lib/$(DLIB) $^ $(INCLUDES) $(LDFLAGS)

clean: force
	$(shell find . -name '*.o' -exec rm -f {} \;)
	rm -f lib/$(DLIB) 

.PHONY: all force
