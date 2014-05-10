#include <string.h>
#include <exception>

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>

#include "gen-cpp/scribe.h"
#include "scribe_wrapper.h"

using namespace std;
using std::string;
using boost::shared_ptr;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift;
using namespace scribe::thrift;
using namespace scribe;

struct scribe_client {
    TTransport* transport;
    scribeClient * client;
};    
    
struct scribe_client* open_connection(const char *host, const int port) {
    struct scribe_client * c = (struct scribe_client *) 
                                    malloc(sizeof(struct scribe_client));

    shared_ptr<TTransport> socket(new TSocket(host, port));
    shared_ptr<TTransport> transport(new TFramedTransport(socket));
    shared_ptr<TProtocol>  protocol(new TBinaryProtocol(transport));
    c->client = new scribeClient(protocol);
	
	try {
		transport->open();
        c->transport = transport.get();
	} 
	catch (TException &tx) {
		return NULL;
	}
		
	return c;
}

int scribe_log(scribe_client * c, const char *category, const char *buf){
	LogEntry entry;
	entry.category = category;
	entry.message = buf;
	
	std::vector<LogEntry> msgs;
	msgs.push_back(entry);
	
	int result = c->client->Log(msgs);
	return result;
}

int close_connection(scribe_client *c) {
	c->transport->close();
	delete c->client;
	return 0;
}
