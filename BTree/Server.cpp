/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Server.cpp
 * Author: taipham
 *
 * Created on September 24, 2018, 9:40 AM
 */

#include "ThreadPool.h"
#include "assert.h"
#include "Server.h"
#include "BytesDataOutputStore.h"
#include "BytesDataInputStore.h"
#include "BTreeStore.h"

Server::Server(const int &port) {
    int flag, fd;
    if (port > 0) {
        this->PORT = port;
    }
    //create server
    if ((this->serverfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(this->serverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
            &opt, sizeof (opt)) < 0) {
        perror("setsocketopt");
        exit(EXIT_FAILURE);
    }

    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons(this->PORT);
    if (bind(this->serverfd, (struct sockaddr *) &address,
            sizeof (address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    flag = fcntl(serverfd, F_GETFL, 0);
    if (flag < 0) {
        cout << "Could not get server socket flags: %s\n" << endl;
    }

    if (fcntl(serverfd, F_SETFL, flag | O_NONBLOCK) < 0) {
        cout << "Could set server socket to be non blocking: %s\n" << endl;
    }
    cout << "[server]: " << this->serverfd << endl;
    //create btree
    this->createBtree();

    this->threadPool = new ThreadPool(this->maxWorker, this, this->bTreeStore);
    FD_ZERO(&(this->masterSet));
    FD_SET(this->serverfd, &(this->masterSet));

    this->printer = new Printer(this);
    this->threadPrinter = new thread(*printer);
    this->eventLoop();
}

Server::~Server() {
    for (int i = 0; i <= FD_SETSIZE; ++i) {
        if (FD_ISSET(i, &(this->masterSet))) {
            close(i);
        }
    }

    if (this->bTreeStore != NULL) {
        cout << "Release bTreeStore" << endl;
        delete this->bTreeStore;
    }

    close(this->serverfd);
    cout << "Closed Server" << endl;

    delete this->threadPool;

    //    if (this->threadPrinter != NULL) {
    //        delete this->threadPrinter;
    //        this->threadPrinter = NULL;
    //    }

    this->setClients.clear();
    dequeCloseSocket.clear();
    dequeRemoveSocketToSet.clear();
}

void Server::createBtree() {
    this->bTreeStore = new BTreeStore<string, string>();
}

void Server::listenToClient() {
    if (listen(this->serverfd, SOMAXCONN) < 0) {

        perror("listen");
        exit(EXIT_FAILURE);
    }
    cout << "server listing...." << endl;
}

int Server::acceptClient() const {
    int clientfd, flag;
    clientfd = accept(this->serverfd, (struct sockaddr *) &address,
            (socklen_t*) & this->addrlen);
    if (clientfd < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return clientfd;
            perror("accept failed");
        }
    }

    flag = fcntl(serverfd, F_GETFL, 0);
    if (flag < 0) {
        cout << "Could not get socket flags: %s\n" << endl;
    }
    //    if (this->keyValueStore != NULL) {
    //        delete this->keyValueStore;
    //    }

    if (fcntl(serverfd, F_SETFL, flag | O_NONBLOCK) < 0) {

        cout << "Could set server to be non blocking: %s\n" << endl;
    }
    return clientfd;
}

void Server::removeClientToSet(int clientfd) {

    this->lockSet.lock();
    this->setClients.erase(clientfd);
    this->lockSet.unlock();
}

void Server::addTaskCloseSocketToDeque(int clientfd) {

    this->lockDequeCloseSocket.lock();
    this->dequeCloseSocket.push_back(clientfd);
    this->lockDequeCloseSocket.unlock();
}

void Server::addTaskRemoveSocketToDeque(int clientfd) {

    this->lockDequeRemoveSocket.lock();
    this->dequeRemoveSocketToSet.push_back(clientfd);
    this->lockDequeRemoveSocket.unlock();
}

void Server::handleCloseSocket() {
    int clientfd;
    while (!this->dequeCloseSocket.empty()) {
        clientfd = this->dequeCloseSocket.front();
        this->dequeCloseSocket.pop_front();
        close(clientfd);
        FD_CLR(clientfd, &(this->masterSet));
        if (clientfd == this->maxSd) {
            while (FD_ISSET(this->maxSd, &(this->masterSet)) == false) {

                this->maxSd -= 1;
            }
        }
        memcpy(&(this->workingSet), &(this->masterSet), sizeof (this->masterSet));
        removeClientToSet(clientfd);
        cout << "server disconnect client: " << clientfd << endl;
    }
}

void Server::handleRemoveClientToSet() {
    int clientfd;
    while (!this->dequeRemoveSocketToSet.empty()) {

        clientfd = this->dequeRemoveSocketToSet.front();
        this->dequeRemoveSocketToSet.pop_front();
        this->setClients.erase(clientfd);
    }
}

void Server::eventLoop() {
    int listen_sd, new_sd;
    int clientfd;
    int socketReady;
    bool flag;
    timeout.tv_sec = 3 * 60;
    timeout.tv_usec = 0;
    this->maxSd = this->serverfd;
    this->listenToClient();
    while (1) {
        thread::id id = std::this_thread::get_id();
        memcpy(&(this->workingSet), &(this->masterSet), sizeof (this->masterSet));
        this->handleRemoveClientToSet();
        //        cout << "Wait select" << endl;
        socketReady = select(this->maxSd + 1, &(this->workingSet), NULL, NULL, NULL);
        this->handleCloseSocket();

        if (socketReady <= 0 && (errno != EINTR)) {
            cout << "select() failed" << endl;
            //            break;
        } else if (FD_ISSET(this->serverfd, &(this->workingSet))) {
            do {
                clientfd = acceptClient();
                if (clientfd < 0) {
                    break;
                }
                cout << "Server accept client: " << clientfd << endl;
                FD_SET(clientfd, &masterSet);

                if (clientfd > this->maxSd) {
                    this->maxSd = clientfd;
                }
                socketReady--;
            } while (clientfd != 0);

        } else {
            for (int i = 4; i <= this->maxSd; ++i) {
                if (FD_ISSET(i, &(this->workingSet))) {
                    flag = false;
                    if (this->setClients.find(i) == this->setClients.end()) {
                        this->setClients.insert(i);
                        flag = true;
                    }
                    if (flag == true) {
                        this->threadPool->addTask(i);
                        if (--socketReady <= 0) {
                            break;
                        }
                    }
                }
            }
        }
    }
}
