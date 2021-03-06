// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include <thrift/protocol/TBinaryProtocol.h>

#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "rsg/services.hpp"
#include "client/RsgClientEngine.hpp"
#include "rsg/actor.hpp"
#include "rsg/mailbox.hpp"
#include "rsg/comm.hpp"
#include "rsg/host.hpp"
#include "rsg/global.hpp"

#include "xbt.h"
#include "simgrid/s4u.h"

#include <iostream>

XBT_LOG_NEW_CATEGORY(RSG_THRIFT_CLIENT, "Remote SimGrid");
XBT_LOG_NEW_DEFAULT_SUBCATEGORY(RSG_THRIFT_REMOTE_CLIENT, RSG_THRIFT_CLIENT , "RSG server (Remote SimGrid)");

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;
using namespace ::RsgService;
using namespace ::simgrid;



int actor(void *) {
  rsg::Mailbox *mbox = rsg::Mailbox::byName("toto");
  XBT_INFO("get clock before receive : %f", rsg::getClock());
  rsg::this_actor::recv(*mbox);
  XBT_INFO("get clock after receive : %f", rsg::getClock());
  rsg::this_actor::quit();
  return 1;
}

int main(int argc, char **argv) {
  const char *msg = "Do you copy ? ";
  rsg::Host host1 = rsg::Host::by_name("host1");

  XBT_INFO("get clock before execute : %f", rsg::getClock());
  rsg::this_actor::execute(8095000000 * 2);
  XBT_INFO("get clock after execute : %f", rsg::getClock());
  
  rsg::Actor::createActor("receiver" , host1 , actor, NULL);
  
  rsg::Mailbox *mbox = rsg::Mailbox::byName("toto");
  
  XBT_INFO("get clock before send : %f", rsg::getClock());
  rsg::this_actor::send(*mbox,msg, strlen(msg) + 1, 115476000);
  XBT_INFO("get clock after send : %f", rsg::getClock());
  
  rsg::this_actor::quit();
  return 0;
}

