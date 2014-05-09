#include <Python.h>

struct scribe_client {
    PyObject * socket;
    PyObject * protocol;
    PyObject * transport;
    PyObject * client;
    PyObject * log_entry;
    PyObject * log;
};

int test() {

    PyObject *scribe_name, * transport_name, *socket_name, *protocol_name;
    PyObject *scribe_module, * transport_module, *socket_module, *protocol_module;
    PyObject * pArgs, *pValue, *pFunc;
    PyObject * socket, *protocol, *transport, *client;

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


    struct scribe_client * myclient = malloc(sizeof (struct scribe_client));
    printf("flag\n");
    //Initialize the socket
    if (socket_module != NULL) {

        pFunc = PyObject_GetAttrString(socket_module, "TSocket");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);

            //set host
            pValue = PyString_FromString("83.212.113.88");
            PyTuple_SetItem(pArgs, 0, pValue);

            //set port
            pValue = PyInt_FromLong(1463);
            PyTuple_SetItem(pArgs, 1, pValue);

            myclient->socket = PyObject_CallObject(pFunc, pArgs);
            if (!myclient->socket)
                printf("error socket\n");
        } else 
            printf("error no socket function\n");
    } else
        printf("error no socket module\n");

    printf("flag\n");
    //initialize transport
    if (transport_module != NULL) {

        pFunc = PyObject_GetAttrString(socket_module, "TFramedTransport");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);

            //set socket
            PyTuple_SetItem(pArgs, 0, myclient->socket);

            myclient->transport = PyObject_CallObject(pFunc, pArgs);
            if (!myclient->transport)
                printf("error transport");
        } else 
            printf("error no transport function\n");
    } else
        printf("error no transport module\n");

    printf("flag\n");
    //initialize protocol
    if (protocol_module != NULL) {

        pFunc = PyObject_GetAttrString(protocol_module, "TBinaryProtocol");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(3);

            //set transport
            PyTuple_SetItem(pArgs, 0, myclient->transport);

            //set booleans  
            pValue = PyBool_FromLong(0);
            PyTuple_SetItem(pArgs, 1, pValue);
            PyTuple_SetItem(pArgs, 2, pValue);

            myclient->protocol = PyObject_CallObject(pFunc, pArgs);
            if (!myclient->protocol)
                printf("error protocol");
        } else 
            printf("error no protocol function\n");
    } else
        printf("error no protocol module\n");
    
    printf("flag\n");
    //initialize client
    if (scribe_module != NULL) {
        
        pFunc = PyObject_GetAttrString(scribe_module, "Client");
        if (pFunc && PyCallable_Check(pFunc)) {
        pArgs = PyTuple_New(1);

        //set protocol
        PyTuple_SetItem(pArgs, 0, myclient->protocol);
       
        myclient->client = PyObject_CallObject(pFunc, pArgs);
        if (!myclient->client)
            printf("error client");
    } else 
        printf("error no client function \n");
    } else
        printf("error no client module\n");

    printf("flag\n");
    //open transport
    pFunc = PyObject_GetAttrString(myclient->transport, "open");
    if (pFunc && PyCallable_Check(pFunc)) {
        pArgs = PyTuple_New(0);

        pValue = PyObject_CallObject(pFunc, pArgs);
    } else 
        printf("error no open function \n");

    
    printf("flag\n");
    //create log entry
    PyObject * category, *message;
    category = PyString_FromString("LOGS");
    message = PyString_FromString("Hello from C");

   //create log entry 
    myclient->log_entry = PyObject_GetAttrString(scribe_module, "LogEntry");
    if (myclient->log_entry && PyCallable_Check(myclient->log_entry)) {
        pArgs = PyTuple_New(2);

        //set category
        PyTuple_SetItem(pArgs, 0, category);

        //set message
        PyTuple_SetItem(pArgs, 1, message);

        pValue = PyObject_CallObject(myclient->log_entry, pArgs);
        if (!pValue)
            printf("error no log value");
    } else 
        printf("error no log entry function\n");

    PyObject* messages = PyList_New(1);
    PyList_SetItem(messages, 0, pValue);
    
    //get the log  function
    myclient->log = PyObject_GetAttrString(myclient->client, "Log");
    if (myclient->log && PyCallable_Check(myclient->log)) {
        pArgs = PyTuple_New(1);

        //set message
        PyTuple_SetItem(pArgs, 0, messages);

        pValue = PyObject_CallObject(myclient->log, pArgs);
        if (!pValue)
            printf("error no result value");
    } else 
        printf("error no log entry function\n");
}

int main() {
    test();
}
