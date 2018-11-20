/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Worker.h
 * Author: taipham
 *
 * Created on September 25, 2018, 1:19 PM
 */

#ifndef WORKER_H
#define WORKER_H
#define GET 1
#define SET 2
#define EXITS 3
#define REMOVE 4
#define SIZERECV 1024
#define FLAG MSG_DONTWAIT
#include "header.h"
#include "HandlePackage.h"
#include "KeyValueStore.h"

typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_usec + (timestamp_t) now.tv_sec * 1000000000;
}


class ThreadPool;
class Server;

class Worker : public HandlePackage {
private:
    ThreadPool* threadPool;
    Server* server;
    KeyValueStore<string, string>* bTreeStore;

public:
    Worker(ThreadPool* pool, Server* server, KeyValueStore<string, string>* bTreeStore);
    ~Worker();
    void operator()();
private:
    int sendBytes(int sock, char* buf, int len, int flags);
    int recvBytes(int clientfd, char* buffer, const int &lenBuffer);
    void serializeInt32(char (&buf)[4], int32_t val);
    int32_t parseInt32(const char (&buf)[4]);
    int getTypePackage(const char* type);
    int manageRecvPackage(const int &clientfd);
    int handlePackageGet(const int& clientfd) override;
    int handlePackageSet(const int& clientfd) override;
    int handlePackageExits(const int& clientfd) override;
    int handlePackageRemove(const int& clientfd) override;
    char* createPackageGet(const char* value, bool flag);
    char createPackageExist(bool isExist);
    char createPackageRemove(bool isSuccess);

    void calTimeGet(int secs);
    void calTimeSet(int secs);
    void calTimeExist(int secs);
    void calTimeRemove(int secs);
};



#endif /* WORKER_H */

