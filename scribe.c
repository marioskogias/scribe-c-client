#include <Python.h>
#include <stdio.h>

struct scribe_client {
    PyObject * socket;
    PyObject * protocol;
    PyObject * transport;
    PyObject * client;
    PyObject * log_entry;
    PyObject * log;
};

struct scribe_client * my_open() {

    PyObject *scribe_name, * transport_name, *socket_name, *protocol_name;
    PyObject *scribe_module, * transport_module, *socket_module, *protocol_module;
    PyObject * pArgs, *pValue, *pFunc;
    
    struct client * scribe_client;
    scribe_client = malloc(sizeof(struct client));

    Py_Initialize();
    scribe_name = PyString_FromString("scribe.scribe");
    socket_name = PyString_FromString("thrift.transport.TSocket");
    transport_name = PyString_FromString("thrift.transport.TTransport");
    protocol_name = PyString_FromString("thrift.protocol.TBinaryProtocol");
    
    
    scribe_module = PyImport_Import(scribe_name);
    Py_DECREF(scribe_name);

    transport_module = PyImport_Import(transport_name);
    Py_DECREF(transport_name);
    
    socket_module = PyImport_Import(socket_name);
    Py_DECREF(socket_name);
    
    protocol_module = PyImport_Import(protocol_name);
    Py_DECREF(protocol_name);


    //Initialize the socket
    if (socket_module != NULL) {

        pFunc = PyObject_GetAttrString(socket_module, "TSocket");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);

            //set host
            pValue = PyString_FromString(host);
            PyTuple_SetItem(pArgs, 0, pValue);

            //set port
            pValue = PyInt_FromLong(port);
            PyTuple_SetItem(pArgs, 1, pValue);

            scribe_client->socket = PyObject_CallObject(pFunc, pArgs);
            if (!scribe_client->socket) {
                perror("error socket\n");
                exit(1);
            }
        } else { 
            perror("error no socket function\n");
            exit(1);
        }
    } else {
        perror("error no socket module\n");
        exit(1);
    }
    
    //initialize transport
    if (transport_module != NULL) {

        pFunc = PyObject_GetAttrString(socket_module, "TFramedTransport");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);

            //set socket
            PyTuple_SetItem(pArgs, 0, scribe_client->socket);

            scribe_client->transport = PyObject_CallObject(pFunc, pArgs);
            if (!scribe_client->transport) {
                perror("error transport");
                exit(1);
            }
        } else {
            perror("error no transport function\n");
            exit(1);
        }
    } else {
        perror("error no transport module\n");
        exit(1);
    }

    printf("flag\n");
    //initialize protocol
    if (protocol_module != NULL) {

        pFunc = PyObject_GetAttrString(protocol_module, "TBinaryProtocol");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(3);

            //set transport
            PyTuple_SetItem(pArgs, 0, scribe_client->transport);

            //set booleans  
            pValue = PyBool_FromLong(0);
            PyTuple_SetItem(pArgs, 1, pValue);
            PyTuple_SetItem(pArgs, 2, pValue);

            scribe_client->protocol = PyObject_CallObject(pFunc, pArgs);
            if (!scribe_client->protocol) {
                perror("error protocol");
                exit(1);
            }
        } else { 
            perror("error no protocol function\n");
            exit(1);
        }
    } else {
        perror("error no protocol module\n");
        exit(1);
    } 
   
    PyObject * myClient; 
    //initialize client
    if (scribe_module != NULL) {

        pFunc = PyObject_GetAttrString(scribe_module, "Client");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);

            //set protocol
            PyTuple_SetItem(pArgs, 0, scribe_client->protocol);

            //scribe_client->client = PyObject_CallObject(pFunc, pArgs);
            myClient = PyObject_CallObject(pFunc, pArgs);
            /*if (!scribe_client->client) {
                perror("error client");
                exit(1);
            } */
        } else { 
            perror("error no client function \n");
            exit(1);
        }
    } else {
        perror("error no scribe module\n");
        exit(1);
    }
    
    //open transport
    pFunc = PyObject_GetAttrString(scribe_client->transport, "open");
    if (pFunc && PyCallable_Check(pFunc)) {
        pArgs = PyTuple_New(0);

        PyObject_CallObject(pFunc, pArgs);
    } else { 
        perror("error no open function \n");
        exit(1);
    }
    
   /* 
    
//create log entry
    PyObject * category, *message;
    category = PyString_FromString("LOGS");
    message = PyString_FromString("Hello from C");
*/
   //create log entry 
    myclient->log_entry = PyObject_GetAttrString(scribe_module, "LogEntry");
    if (myclient->log_entry && PyCallable_Check(myclient->log_entry)) {
/*        pArgs = PyTuple_New(2);

        //set category
        PyTuple_SetItem(pArgs, 0, category);

        //set message
        PyTuple_SetItem(pArgs, 1, message);

        pValue = PyObject_CallObject(myclient->log_entry, pArgs);
        if (!pValue)
            printf("error no log value");
*/
    } else 
        printf("error no log entry function\n");
/*
    PyObject* messages = PyList_New(1);
    PyList_SetItem(messages, 0, pValue);
*/    
    //get the log  function
    myclient->log = PyObject_GetAttrString(myclient->client, "Log");
    if (myclient->log && PyCallable_Check(myclient->log)) {
  /*      pArgs = PyTuple_New(1);

        //set message
        PyTuple_SetItem(pArgs, 0, messages);

        pValue = PyObject_CallObject(myclient->log, pArgs);
        if (!pValue)
            printf("error no result value");
*/    
   } else 
        printf("error no log entry function\n");
    
    return myclient;
}

void send(struct scribe_client * myclient) {

    //create log entry
    
    PyObject * category, *message, *pArgs, *pValue;
    category = PyString_FromString("LOGS");
    message = PyString_FromString("Hello from C");

   //create log entry 
        pArgs = PyTuple_New(2);

        //set category
        PyTuple_SetItem(pArgs, 0, category);

        //set message
        PyTuple_SetItem(pArgs, 1, message);

        pValue = PyObject_CallObject(myclient->log_entry, pArgs);
        if (!pValue)
            printf("error no log value");


    PyObject* messages = PyList_New(1);
    PyList_SetItem(messages, 0, pValue);
    
    //get the log  function
    pFunc = PyObject_GetAttrString(myClient, "Log");
    if (pFunc && PyCallable_Check(pFunc)) {
        pArgs = PyTuple_New(1);

        //set message
        PyTuple_SetItem(pArgs, 0, messages);

        //pValue = PyObject_CallObject(pFunc, pArgs);
        if (!pValue)
            printf("error no result value");
    } else 
        printf("error no log entry function\n");
return scribe_client;
}


int send(struct client * scribe_client, char * category, char * message) {

    PyObject * pArgs, *logEntry, *pValue;

    //create log entry
    PyObject * py_category, *py_message;
    py_category = PyString_FromString(category);
    py_message = PyString_FromString(message);

    pArgs = PyTuple_New(2);

    //set category
    PyTuple_SetItem(pArgs, 0, py_category);

    //set message
    PyTuple_SetItem(pArgs, 1, py_message);
    
    
    printf("flag\n");
    logEntry = PyObject_CallObject(scribe_client->log_entry, pArgs);
    if (!logEntry) {
        perror("error no log entry value");
        exit(1);
    } 
    
    printf("flag\n");
    PyObject* messages = PyList_New(1);
    PyList_SetItem(messages, 0, logEntry);
    
    printf("flag\n");

    pArgs = PyTuple_New(1);

    //set message
    PyTuple_SetItem(pArgs, 0, messages);

    printf("flag\n");
    if (!scribe_client->log || !PyCallable_Check(scribe_client->log)) {
        perror("error no log function\n");
        exit(1);
    }
    
    if (!pArgs)
        perror("no args\n");
    pValue = PyObject_CallObject(scribe_client->log, pArgs);
    
    printf("flag\n");
    if (!pValue) {
        perror("error no result value");
        exit(1);
    }  
}


int main() {

    struct client * myclient = open("83.212.113.88", 1463);
    printf("after open\n");
    //send(myclient, "LOGS", "Hello from C lib");    
}
