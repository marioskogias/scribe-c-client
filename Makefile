PYTHON_INCLUDES = -I/usr/include/python2.7
PYTHON_FLAGS = -lpython2.7


scribe: scribe.c  
	$(CC) $< $(PYTHON_INCLUDES) $(PYTHON_FLAGS) -o $@
