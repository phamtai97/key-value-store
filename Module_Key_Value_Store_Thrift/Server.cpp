/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Server.cpp
 * Author: phamtai97
 *
 * Created on October 30, 2018, 1:53 PM
 */

#include "Server.h"

//Server::Server() : handler(new ServiceKeyValueStoreHandler(this->bTreeStore)),
//processor(new ServiceKeyValueStoreProcessor(handler)),
//protocolFactory(new TBinaryProtocolFactory()),
//transportFactory(new TFramedTransportFactory()),
//socket(new TNonblockingServerSocket(port)),
//threadManager(ThreadManager::newSimpleThreadManager(NWORKER)),
//threadFactory(shared_ptr<PosixThreadFactory>(new PosixThreadFactory())) {
//
//    threadManager->threadFactory(threadFactory);
//    threadManager->start();
//}

Server::Server() : handler(new ServiceKeyValueStoreHandler(this->bTreeStore)),
processor(new ServiceKeyValueStoreProcessor(handler)),
protocolFactory(new TBinaryProtocolFactory()),
transportFactory(new TFramedTransportFactory),
socket(new TNonblockingServerSocket(port)) {

    TFramedTransportFactory* framedFactory
            = dynamic_cast<TFramedTransportFactory*> (transportFactory.get());
    if (framedFactory == NULL) {
        throw TException("TNonblockingServer must use TFramedTransport");
    }

    threadManager = ThreadManager::newSimpleThreadManager(NWORKER);
    threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
}

Server::~Server() {
}

void Server::start() {
    this->server = new TNonblockingServer(processor, protocolFactory, socket, threadManager);
    this->server->serve();
}

void Server::stop() {
    this->server->stop();
    if (server != NULL) {
        delete this->server;
        this->server = NULL;
    }
    if (this->bTreeStore != NULL) {
        delete this->bTreeStore;
        this->bTreeStore = NULL;
    }
}

//void Server::creatBTreeStore() {
//    this->bTreeStore = new BTreeStore<string, string>();
//}
