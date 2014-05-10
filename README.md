scribe-c-client
===============

This is a minimal client written in C for the Facebook Scribe logging server.
There are two attempts-versions of the client. 
The first one is a wrapper for C++ and builds the needed Thrift files itself.
The second is based on the python module facebook-scribe and it's a python
wrapper around it.


C++ wrapper
------------

In order to build the C++ wrapper you will need the following

[thrift] Thrift framework

[fb303] Facebook Bassline (included in thrift/contrib/fb303/)
   fb303 r697294 or later is required.

After having a working version of thrift installed do:

make

In order to run the test, change the ip and port of the server in test.c and do:

make run


Python wrapper
------------

For the Python wrapper you will need:

1. facebook-scribe

    Installation: pip install facebook-scribe

2. Python devtools
    
    Installation: apt-get install python-dev
