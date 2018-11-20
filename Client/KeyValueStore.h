/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   KeyValueStore.h
 * Author: taipham
 *
 * Created on September 24, 2018, 11:32 AM
 */

#ifndef CLIENT_H
#define CLIENT_H
#include "header.h"
#include "Storage.h"
#include "HandleCreatePackage.h"
#define FLAG MSG_DONTWAIT
#define SIZERECV 1024

class KeyValueStore : public Storage, public HandleCreatePackage {
private:
    struct sockaddr_in address;
    struct sockaddr_in serv_addr;
    int clientfd;
    int PORT;
    string localHost;
public:
    KeyValueStore();
    ~KeyValueStore();
    bool connectServer(string localHost, int port);
    string get(string key) override;
    void set(string key, string value) override;
    bool exist(string key) override;
    bool remove(string key) override;
    int getKeyValueStorefd() const;


    void sendBytes(const char* &mess, const int &size, const int flag) const;
    int recvBytes(char* buffer, const int &lenBuffer);

private:
    const char* createPackageGet(const char* key) override;
    const char* createPackageSet(const char* key, const char* value) override;
    const char* createPackageExits(const char* key) override;
    const char* createPackageRemove(const char* key) override;

    void serializeInt32(char (&buf)[4], int32_t val);
    int32_t parseInt32(const char (&buf)[4]);
    int handlePackageGet(char* &buffer);
    int handlePackageExist(bool& isExist);
    int handlePackageRemove(bool& isSuccess);

};

#endif /* CLIENT_H */

