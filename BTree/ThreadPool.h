/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ThreadPool.h
 * Author: taipham
 *
 * Created on September 24, 2018, 6:33 PM
 */

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "header.h"
#include "KeyValueStore.h"

class Worker;
class Server;

class ThreadPool {
private:
    friend class Worker;
    vector<thread*> workers;
    deque<int> taskQueue;
    bool stop;
    condition_variable condition;
    mutex lockQueue;
public:
    ThreadPool(const int &size, Server* server, KeyValueStore<string, string>* bTreeStore);
    ~ThreadPool();
    void addTask(int clientfd);
};

#endif /* THREADPOOL_H */

