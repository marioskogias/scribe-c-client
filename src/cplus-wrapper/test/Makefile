CURRENT_DIR = $(shell pwd)
LIB_DIR = $(CURRENT_DIR)/../lib

CFLAGS = -fPIC -g -pipe -m64
LDFLAGS = -L$(LIB_DIR) -lscribe_client
INCLUDES = -I$(LIB_DIR)

CC = gcc

all: test 

test:
	$(CC) test.c $(CFLAGS)  $(LDFLAGS) $(INCLUDES) -o test

clean: 
	rm -f *.o test
