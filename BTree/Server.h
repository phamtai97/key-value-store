/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Server.h
 * Author: taipham
 *
 * Created on September 24, 2018, 9:40 AM
 */

#ifndef SERVER_H
#define SERVER_H



#include "header.h"
#include "BTree.h"
#include "DataInput.h"
#include "DataOutput.h"
#include "ManageFileRead.h"
#include "Printer.h"


class Printer;
class ThreadPool;

class Server {
private:
    const int maxWorker = 20;
    int serverfd;
    int opt = 1;
    struct sockaddr_in address;
    int PORT = 8080;
    int addrlen = sizeof (address);

    ThreadPool* threadPool;
    Printer *printer;
    thread* threadPrinter;

    struct timeval timeout;
    fd_set masterSet, workingSet;
    atomic<int> maxSd;
    set<int> setClients;
    mutex lockSet, lockDequeCloseSocket, lockDequeRemoveSocket;
    deque<int> dequeCloseSocket;
    deque<int> dequeRemoveSocketToSet;

    KeyValueStore<string, string>* bTreeStore;

public:
    Server(const int &port);
    ~Server();

    void createBtree();
    void addTaskCloseSocketToDeque(int clientfd);
    void addTaskRemoveSocketToDeque(int clientfd);

    atomic<int> sumTimeHandleGet{0};
    atomic<int> sumTimeHandleSet{0};
    atomic<int> sumTimeHandleRemove{0};
    atomic<int> sumTimeHandleExist{0};

private:
    void eventLoop();
    int acceptClient() const;
    void listenToClient();
    int getSocket(int i);
    int getMaxIndex() const;
    void removeClientToSet(int clientfd);
    void handleCloseSocket();
    void handleRemoveClientToSet();

};

#endif /* SERVER_H */

