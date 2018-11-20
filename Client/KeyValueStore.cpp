/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   KeyValueStore.cpp
 * Author: taipham
 *
 * Created on September 24, 2018, 11:32 AM
 */

#include "KeyValueStore.h"
#include <sstream>
#include "assert.h"

KeyValueStore::KeyValueStore() {
    if ((this->clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "\n Socket creation error\n";
        assert(false);
    }
}

KeyValueStore::~KeyValueStore() {
    close(this->clientfd);
}

bool KeyValueStore::connectServer(string localHost, int port) {
    this->PORT = port;
    this->localHost = localHost;
    memset(&(this->serv_addr), '0', sizeof (this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_port = htons(this->PORT);
    if (inet_pton(AF_INET, this->localHost.c_str(), &(this->serv_addr.sin_addr)) <= 0) {
        cout << "\nInvalid address/ Address not supported \n";
        return false;
    }
    if (connect(this->clientfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        return false;
    }
    return true;
}

void KeyValueStore::sendBytes(const char* &mess, const int &size, const int flag) const {
    int bytesSent = 0;
    int bytesTmp = 0;
    while (bytesSent != size) {
        bytesTmp = send(this->clientfd, mess, size, flag);
        if (bytesSent == -1) {
            return;
        }
        bytesSent += bytesTmp;
    }
}

int KeyValueStore::recvBytes(char* buffer, const int &lenBuffer) {
    int result = 0;
    int rc = 0;

    while (1) {
        rc = recv(this->clientfd, buffer + result, lenBuffer, FLAG);
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

int KeyValueStore::getKeyValueStorefd() const {
    return this->clientfd;
}

void KeyValueStore::serializeInt32(char (&buf)[4], int32_t val) {
    memcpy(buf, &val, 4);
}

int32_t KeyValueStore::parseInt32(const char (&buf)[4]) {
    int32_t val;
    memcpy(&val, buf, 4);
    return val;
}

const char* KeyValueStore::createPackageGet(const char* key) {
    int len = strlen(key);
    char *buffer = new char[len + 5];
    char strLen[4];
    buffer[0] = 1;
    this->serializeInt32(strLen, len);
    memcpy(buffer + 1, strLen, 4 * sizeof (strLen[0]));
    memcpy(buffer + 5, key, len * sizeof (key[0]));
    return buffer;
}

const char* KeyValueStore::createPackageSet(const char* key, const char* value) {
    int lenKey = strlen(key);
    int lenValue = strlen(value);
    char *buffer = new char[lenKey + lenValue + 9];
    char strLenKey[4];
    char strLenValue[4];

    buffer[0] = 1;
    buffer[0] = buffer[0] | (1 << 1);

    this->serializeInt32(strLenKey, lenKey);
    this->serializeInt32(strLenValue, lenValue);

    memcpy(buffer + 1, strLenKey, 4 * sizeof (strLenKey[0]));
    memcpy(buffer + 5, strLenValue, 4 * sizeof (strLenValue[0]));

    memcpy(buffer + 9, key, lenKey * sizeof (key[0]));
    memcpy(buffer + 9 + lenKey, value, lenValue * sizeof (value[0]));
    return buffer;
}

const char* KeyValueStore::createPackageExits(const char* key) {
    int len = strlen(key);
    char *buffer = new char[len + 5];
    char strLen[4];

    buffer[0] = buffer[0] | (1 << 2);
    this->serializeInt32(strLen, len);

    memcpy(buffer + 1, strLen, 4 * sizeof (strLen[0]));
    memcpy(buffer + 5, key, len * sizeof (key[0]));
    return buffer;
}

const char* KeyValueStore::createPackageRemove(const char* key) {
    int len = strlen(key);
    char *buffer = new char[len + 5];
    char strLen[4];

    buffer[0] = buffer[0] | (1 << 3);

    this->serializeInt32(strLen, len);

    memcpy(buffer + 1, strLen, 4 * sizeof (strLen[0]));
    memcpy(buffer + 5, key, len * sizeof (key[0]));

    return buffer;
}

string KeyValueStore::get(string key) {
    string res;
    int size = key.length() + sizeof (int) + sizeof (char);
    int rc;
    const char* package = this->createPackageGet(key.c_str());

    char* buffer;
    this->sendBytes(package, size, 0);

    //Recv package to server
    rc = this->handlePackageGet(buffer);

    if (rc < 0) {
        cout << "Key is not exist" << endl;
        return "";
    }

    res = string(buffer);

    delete []package;
    delete []buffer;

    return res;
}

void KeyValueStore::set(string key, string value) {
    if (!key.length()) {
        cout << "key is not empty" << endl;
        return;
    }

    int size = key.length() + value.length() + 9;
    const char* package = this->createPackageSet(key.c_str(), value.c_str());

    this->sendBytes(package, size, 0);
    //Recv package to server
    delete[] package;
}

bool KeyValueStore::exist(string key) {
    int size = key.length() + 5;
    const char* package = this->createPackageExits(key.c_str());
    bool isExist;

    this->sendBytes(package, size, 0);
    //Recv package to server
    this->handlePackageExist(isExist);

    delete[] package;

    return isExist;
}

bool KeyValueStore::remove(string key) {
    int size = key.length() + 5;
    bool isSuccess;

    const char* package = this->createPackageRemove(key.c_str());
    this->sendBytes(package, size, 0);

    //Recv package to server
    this->handlePackageRemove(isSuccess);

    delete[]package;

    return isSuccess;
}

int KeyValueStore::handlePackageGet(char* &buffer) {
    char strLenValue[4];
    int lenValue;
    int rc;
    char flag;
    rc = this->recvBytes(&flag, sizeof (char));

    rc = this->recvBytes(strLenValue, sizeof (int));

    lenValue = this->parseInt32(strLenValue);

    buffer = new char[lenValue + 1];

    rc = this->recvBytes(buffer, lenValue);

    if (flag == 0) {
        return -1;
    }
    return rc;
}

int KeyValueStore::handlePackageExist(bool& isExist) {
    int rc;
    char res;
    rc = this->recvBytes(&res, sizeof (char));
    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }
    if (res == 1) {
        isExist = true;
    } else {

        isExist = false;
    }
}

int KeyValueStore::handlePackageRemove(bool& isSuccess) {
    int rc;
    char res;
    rc = this->recvBytes(&res, sizeof (char));
    if (rc < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            return -1;
        }
    }
    if (res == 1) {
        isSuccess = true;
    } else {

        isSuccess = false;
    }
}
