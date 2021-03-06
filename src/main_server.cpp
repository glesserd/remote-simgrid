// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.




#include "xbt.h"
#include "simgrid/s4u.h"

#include "rsg/services.hpp"
#include "rsg/Server.hpp"

#include <thrift/processor/TMultiplexedProcessor.h>

#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;
using namespace ::simgrid;

std::vector<std::thread*> threads;

XBT_LOG_NEW_CATEGORY(RSG_THRIFT, "Remote SimGrid");
XBT_LOG_NEW_DEFAULT_SUBCATEGORY(RSG_THRIFT_SERVER, RSG_THRIFT , "RSG server (Remote SimGrid)");

/* Fork a remote process, and serve it until it CMD_QUITs */
static int rsg_representative(int argc, char **argv) {

  if (! fork()) {
    int newargc = argc-1+2+1;
    char **newargv = (char**)calloc(newargc, sizeof(char*));
    newargv[0] = (char*)"/usr/bin/env";
    newargv[1] = (char*)"--";
    for(int i=1; i < argc; i++) {
      newargv[1+i] = argv[i];
    }
    newargv[newargc-1] = NULL;
    execv(newargv[0], newargv);
	}

  shared_ptr<rsg::RsgActorHandler> handler(new rsg::RsgActorHandler());
  shared_ptr<rsg::RsgMailboxHandler> mbHandler(new rsg::RsgMailboxHandler());
  shared_ptr<rsg::RsgHostHandler> hostHandler(new rsg::RsgHostHandler());
  shared_ptr<rsg::RsgGlobalServiceHandler> gblServiceHandler(new rsg::RsgGlobalServiceHandler());
  shared_ptr<rsg::RsgCommHandler> commHandler(new rsg::RsgCommHandler());

  TMultiplexedProcessor* processor = new TMultiplexedProcessor();

  processor->registerProcessor(
      "RsgActor",
      shared_ptr<RsgActorProcessor>(new RsgActorProcessor(handler)));

  processor->registerProcessor(
      "RsgMailbox",
      shared_ptr<RsgMailboxProcessor>(new RsgMailboxProcessor(mbHandler)));

  processor->registerProcessor(
      "RsgHost",
      shared_ptr<RsgHostProcessor>(new RsgHostProcessor(hostHandler)));

  processor->registerProcessor(
      "RsgComm",
      shared_ptr<RsgCommProcessor>(new RsgCommProcessor(commHandler)));
  
  processor->registerProcessor(
      "RsgGlobalService",
      shared_ptr<RsgGlobalServiceProcessor>(new RsgGlobalServiceProcessor(gblServiceHandler)));
  
  SocketServer &socketServer = SocketServer::getSocketServer();
  RsgThriftServerFramework *server = socketServer.acceptClient(processor);

  handler->setServer(server);
  server->listen();
  server->serve();
  delete server;
	return 0;
}

int main(int argc, char **argv) {

  SocketServer &socketServer = SocketServer::createSocketServer(std::string("127.0.0.1"), 9090);
  socketServer.connect();

  s4u::Engine *e = new s4u::Engine(&argc,argv);

  if (argc < 3) {
		fprintf(stderr,"Usage: rsg platform.xml deploy.xml port\n");
		exit(1);
	}

  /* Initialize the SimGrid world */
  e->loadPlatform(argv[1]);
  e->registerDefault(rsg_representative);
  e->loadDeployment(argv[2]);
  e->run();
  
  socketServer.closeServer();
  return 0;
}
