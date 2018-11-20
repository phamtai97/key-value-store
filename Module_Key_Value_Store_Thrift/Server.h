/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Server.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 1:53 PM
 */

#ifndef SERVER_H
#define SERVER_H
#define PORT 8080


#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/concurrency/Monitor.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TNonblockingServerSocket.h>


#include "ServiceKeyValueStoreHandler.h"
#include "header.h"
#include "KeyValueStore.h"
#include "BTreeStore.h"

using namespace ::apache::thrift;
using namespace apache::thrift::concurrency;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class Server {
private:
    int port = PORT;
    KeyValueStore<string, string>* bTreeStore = new BTreeStore<string, string>();
    ::apache::thrift::stdcxx::shared_ptr<ServiceKeyValueStoreHandler> handler;
    ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor;
    ::apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory;
    ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory;
    ::apache::thrift::stdcxx::shared_ptr<TNonblockingServerSocket> socket;
    ::apache::thrift::stdcxx::shared_ptr<PosixThreadFactory> threadFactory;
    ::apache::thrift::stdcxx::shared_ptr<ThreadManager> threadManager;
    TNonblockingServer* server;
public:
    Server();
    virtual ~Server();
    void start();
    void stop();
    //    void creatBTreeStore();

};

#endif /* SERVER_H */

