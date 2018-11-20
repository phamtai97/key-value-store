/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ThreadPool.h"
#include "Server.h"
#include "Worker.h"
#define NANOS 1000000000.0L

Worker::Worker(ThreadPool* pool, Server* server, KeyValueStore<string, string>* bTreeStore) {
    this->threadPool = pool;
    this->server = server;
    this->bTreeStore = bTreeStore;
}

void Worker::operator()() {
    int clientfd;
    int result;
    while (true) {
        {
            unique_lock<mutex> lock(this->threadPool->lockQueue);
            while (!this->threadPool->stop && this->threadPool->taskQueue.empty()) {
                this->threadPool->condition.wait(lock);
            }

            if (this->threadPool->stop) {
                return;
            }
            clientfd = this->threadPool->taskQueue.front();
            this->threadPool->taskQueue.pop_front();
        }
        result = this->manageRecvPackage(clientfd);


        if (result > 0) {
            this->server->addTaskRemoveSocketToDeque(clientfd);
        } else if (result == -1) {
            this->server->addTaskCloseSocketToDeque(clientfd);
            this->server->addTaskRemoveSocketToDeque(clientfd);
        } else if (result == 0) {
            this->server->addTaskCloseSocketToDeque(clientfd);
            this->server->addTaskRemoveSocketToDeque(clientfd);
        }
    }
}

Worker::~Worker() {
}

void Worker::serializeInt32(char (&buf)[4], int32_t val) {
    memcpy(buf, &val, 4);
}

int32_t Worker::parseInt32(const char (&buf)[4]) {
    int32_t val;
    memcpy(&val, buf, 4);
    return val;
}

int Worker::getTypePackage(const char* type) {
    int typePackage;
    if (type[0] == 1) {
        typePackage = GET;
    } else if (((type[0] >> 1) & 1) == 1) {
        typePackage = SET;
    } else if (((type[0] >> 2) & 1) == 1) {
        typePackage = EXITS;
    } else if (((type[0] >> 3) & 1) == 1) {
        typePackage = REMOVE;
        cout << "Remove";
    }
    return typePackage;
}

int Worker::manageRecvPackage(const int &clientfd) {
    char type[1];
    int rc = 0;
    int typePackage;
    rc = this->recvBytes(clientfd, type, 1);
    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }

    if (rc == 0) {
        return 0;
    }

    typePackage = this->getTypePackage(type);


    if (typePackage == GET) {
        return this->handlePackageGet(clientfd);
    } else if (typePackage == SET) {
        return this->handlePackageSet(clientfd);
    } else if (typePackage == EXITS) {
        return this->handlePackageExits(clientfd);
    } else if (typePackage == REMOVE) {
        return this->handlePackageRemove(clientfd);
    }

    return 0;
}

int Worker::recvBytes(int clientfd, char* buffer, const int &lenBuffer) {
    int result = 0;
    int rc = 0;

    while (1) {
        rc = recv(clientfd, buffer + result, lenBuffer, FLAG);

        if (rc > 0) {
            result = result + rc;
        }
        if (result == lenBuffer) {
            break;
        }
        if (rc < 0) {
            if (errno != EWOULDBLOCK || errno != EAGAIN) {
                result = -1;
                break;
            }
        } else if (rc == 0) {
            result = 0;
            break;
        }
    }
    buffer[result] = '\0';
    return result;
}

int Worker::sendBytes(int sock, char* buf, int len, int flags) {
    int bytesSent = 0;
    int bytesTmp = 0;

    while (bytesSent != len) {
        bytesTmp = send(sock, buf, len, flags);
        if (bytesSent == -1) {
            if (errno != EWOULDBLOCK || errno != EAGAIN) {
                return -1;
            }
        }
        bytesSent += bytesTmp;
    }

    return bytesSent;
}

int Worker::handlePackageGet(const int &clientfd) {
    int rc;
    char* buffer;
    char* bufferSend;
    int lenPackage;
    char strLenPackage[4];
    int size;
    string req;
    string value;
    bool res;


    rc = this->recvBytes(clientfd, strLenPackage, 4);
    if (rc < 0) {
        return rc;
    }

    lenPackage = this->parseInt32(strLenPackage);
    buffer = new char[lenPackage];

    rc = this->recvBytes(clientfd, buffer, lenPackage);
    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }

    //code get
    //    cout << "[ Client " << clientfd << " ] send: " << buffer << endl;

    req = string(buffer, lenPackage);

    res = this->bTreeStore->getValue(req, value);

    //create package get
    bufferSend = this->createPackageGet(value.c_str(), res);

    size = value.length() + sizeof (int) + sizeof (bool);

    //send
    this->sendBytes(clientfd, bufferSend, size, 0);

    delete[] buffer;
    delete[] bufferSend;

    return rc;
}

int Worker::handlePackageSet(const int &clientfd) {
    int rc;
    char* bufferKey;
    char* bufferValue;

    int lenKey;
    int lenValue;
    char strLenKey[4];
    char strLenValue[4];

    string reqKey;
    string reqValue;

    rc = this->recvBytes(clientfd, strLenKey, 4);

    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }
    lenKey = this->parseInt32(strLenKey);

    rc = recv(clientfd, strLenValue, 4, FLAG);
    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }
    lenValue = this->parseInt32(strLenValue);

    bufferKey = new char[lenKey];

    rc = this->recvBytes(clientfd, bufferKey, lenKey);
    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }

    bufferValue = new char[lenValue];
    if (lenValue != 0) {
        rc = this->recvBytes(clientfd, bufferValue, lenValue);

    }

    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }

    //code get
    //    cout << "[ Client " << clientfd << " ] send: " << "Key: " << bufferKey << endl;
    //    cout << "[ Client " << clientfd << " ] send: " << "Value: " << bufferValue << endl;

    //code set
    reqKey = string(bufferKey, lenKey);
    reqValue = string(bufferValue, lenValue);

    this->bTreeStore->set(reqKey, reqValue);

    delete[] bufferKey;
    delete[] bufferValue;

    return rc;
}

int Worker::handlePackageExits(const int& clientfd) {
    int rc;
    char* buffer;
    int lenPackage;
    char strLenPackage[4];
    char isExist;
    char bufferSend;
    bool res;
    string req;

    rc = this->recvBytes(clientfd, strLenPackage, 4);
    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }

    lenPackage = this->parseInt32(strLenPackage);

    buffer = new char[lenPackage];

    rc = this->recvBytes(clientfd, buffer, lenPackage);

    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }

    cout << "[ Client " << clientfd << " ] send: " << buffer << endl;

    //code exits
    req = string(buffer, lenPackage);
    res = this->bTreeStore->exist(req);

    //create package exist
    bufferSend = this->createPackageExist(res);

    //send
    this->sendBytes(clientfd, &bufferSend, 1, 0);

    delete[] buffer;

    return rc;
}

int Worker::handlePackageRemove(const int& clientfd) {
    int rc;
    char* buffer;
    int lenPackage;
    char strLenPackage[4];
    char bufferSend;

    rc = this->recvBytes(clientfd, strLenPackage, 4);

    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }

    lenPackage = this->parseInt32(strLenPackage);
    buffer = new char[lenPackage];

    rc = this->recvBytes(clientfd, buffer, lenPackage);
    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }

    //cout << "[ Client " << clientfd << " ] send: " << buffer << endl;

    //code remove
    string req = string(buffer, lenPackage);
    bool res = this->bTreeStore->remove(req);

    //create package remove
    bufferSend = this->createPackageRemove(res);

    //send
    this->sendBytes(clientfd, &bufferSend, 1, 0);

    delete[] buffer;

    return rc;
}

char* Worker::createPackageGet(const char* value, bool flag) {
    int len = strlen(value);
    int size = len + sizeof (int) + sizeof (bool);
    char *buffer = new char[size];
    char strLenValue[4];
    this->serializeInt32(strLenValue, len);

    if (flag) {
        buffer[0] = 1;
    } else {
        buffer[0] = 0;
    }
    memcpy(buffer + sizeof (bool), strLenValue, 4 * sizeof (strLenValue[0]));
    memcpy(buffer + sizeof (int) + sizeof (bool), value, len * sizeof (value[0]));
    return buffer;
}

char Worker::createPackageExist(bool isExist) {
    return isExist ? 1 : 0;
}

char Worker::createPackageRemove(bool isSuccess) {
    return isSuccess ? 1 : 0;
}

void Worker::calTimeGet(int secs) {
    this->server->sumTimeHandleGet += secs;
}

void Worker::calTimeSet(int secs) {
    this->server->sumTimeHandleSet += secs;
}

void Worker::calTimeExist(int secs) {
    this->server->sumTimeHandleExist += secs;
}

void Worker::calTimeRemove(int secs) {
    this->server->sumTimeHandleRemove += secs;
}


