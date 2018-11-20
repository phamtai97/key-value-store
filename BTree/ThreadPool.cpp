/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ThreadPool.h"
#include "Server.h"
#include "Worker.h"

ThreadPool::ThreadPool(const int &size, Server* server, KeyValueStore<string, string>* bTreeStore) {
    this->stop = false;
    for (int i = 0; i < size; ++i) {
        Worker* worker = new Worker(this, server, bTreeStore);
        this->workers.push_back(new thread(*worker));
    }
}

ThreadPool::~ThreadPool() {
    {
        unique_lock<mutex> lock(this->lockQueue);
        this->stop = true;
    }

    condition.notify_all();
    for (int i = 0; i < this->workers.size(); ++i) {
        if (this->workers[i]->joinable()) {
            this->workers[i]->join();
        }
    }

    for (int i = 0; i < this->workers.size(); ++i) {
        if (this->workers[i] != NULL) {
            delete this->workers[i];
            this->workers[i] = NULL;
        }
    }
}

void ThreadPool::addTask(int clientfd) {
    lockQueue.lock();
    this->taskQueue.push_back(clientfd);
    lockQueue.unlock();
    condition.notify_one();
}
