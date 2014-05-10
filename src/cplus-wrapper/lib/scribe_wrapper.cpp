#include <string.h>
#include <exception>

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>

#include "gen-cpp/scribe.h"

using namespace std;
using std::string;
using boost::shared_ptr;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift;
using namespace scribe::thrift;
using namespace scribe;

struct scribe_client {
    shared_ptr<TTransport> socket; 
    shared_ptr<TTransport> transport;
    shared_ptr<TProtocol>  protocol;
    scribeClient * client;
};    
    
struct scribe_client* open_connection(const char *host, const int port) {
    struct scribe_client * c = malloc(sizeof(struct scribe_client));

	c->socket(new TSocket(p->host, p->port));
	c->transport(new TFramedTransport(socket));
	c->protocol(new TBinaryProtocol(transport));
	
	c->client = new scribeClient(protocol);
	
	try {
		transport->open();
	} 
	catch (TException &tx) {
		return 1;
	}
		
	return 0;
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
	c->transport.close();
	delete c->scribeClient;
	return 0;
}
