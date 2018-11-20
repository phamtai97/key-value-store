/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: taipham
 *
 * Created on September 24, 2018, 11:31 AM
 */

#include "KeyValueStore.h"
#include <string>
#include <thread>
#include  <sys/time.h>
using namespace std;


typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_usec + (timestamp_t) now.tv_sec * 1000000;
}

/*
 *
 */
#define PORTSERVER 8080
#define n  250

void testClientConnectServer() {
    string res;
    KeyValueStore* client = new KeyValueStore[n];
    for (int i = 0; i < n; ++i) {
        if (client[i].connectServer("127.0.0.1", PORTSERVER)) {
            cout << "client : " << client[i].getKeyValueStorefd() << " connect success" << endl;
        } else {
            cout << "connect failed" << endl;
        }
    }
    delete [] client;
}

void testClienUseAPIGetValueFromKeyValueStore() {
    string res;
    KeyValueStore* client = new KeyValueStore[n];
    for (int i = 0; i < n; ++i) {
        if (client[i].connectServer("127.0.0.1", PORTSERVER)) {
            cout << "client : " << client[i].getKeyValueStorefd() << " connect success" << endl;
            res = client[i].get(to_string(i));
            cout << "[value]: " << res << endl;
        } else {
            cout << "connect failed" << endl;
        }
    }
    delete [] client;
}

void testClientUseAPIExistFromKeyValueStore() {
    bool res;
    KeyValueStore* client = new KeyValueStore[n];
    for (int i = 0; i < n; ++i) {
        if (client[i].connectServer("127.0.0.1", PORTSERVER)) {
            cout << "client : " << client[i].getKeyValueStorefd() << " connect success" << endl;
            res = client[i].exist(to_string(i));
            if (res) {
                cout << "key " << i << " already exists" << endl;
            } else {
                cout << "key " << i << " does not exist" << endl;
            }
        } else {
            cout << "connect failed" << endl;
        }
    }

    delete [] client;
}

void testClientUseAPTSetFromKeyValueStore() {
    bool res;
    KeyValueStore* client = new KeyValueStore[n];
    for (int i = 0; i < n; ++i) {
        if (client[i].connectServer("127.0.0.1", PORTSERVER)) {
            cout << "client : " << client[i].getKeyValueStorefd() << " connect success" << endl;
            client[i].set(to_string(i), to_string(i));
        } else {
            cout << "connect failed" << endl;
        }
    }
    delete [] client;
}

void testClienUseAPIRemoveFromKeyValueStore() {
    bool res;
    KeyValueStore* client = new KeyValueStore[n];
    for (int i = 0; i < n; ++i) {
        if (client[i].connectServer("127.0.0.1", PORTSERVER)) {
            cout << "client : " << client[i].getKeyValueStorefd() << " connect success" << endl;
        } else {
            cout << "connect failed" << endl;
        }
    }

    for (int i = 0; i < n; ++i) {
        res = client[i].remove(to_string(i));
        if (res) {
            cout << "Remove success" << endl;
        } else {
            cout << "Remove failed" << endl;
        }
    }
    delete [] client;
}

void benchMarkGet() {
    timestamp_t timeFinish;
    int count = 0;
    int i = 0;
    KeyValueStore* client = new KeyValueStore[n];
    timestamp_t timeStart = get_timestamp();

    while (true) {


        if (timeFinish - timeStart == 1) {
            break;
        }
    }


}

int main(int argc, char** argv) {

    //    testClientConnectServer();
    //    testClienUseAPIGetValueFromKeyValueStore();
    //    testClientUseAPIExistFromKeyValueStore();
    //    testClientUseAPTSetFromKeyValueStore();
    //    testClienUseAPIRemoveFromKeyValueStore();

    //    KeyValueStore* client = new KeyValueStore();
    //    client->connectServer("127.0.0.1", PORTSERVER);
    //    cout << client->get("-1") << endl;
    //    delete client;

    //    std::thread clientGet(testClienUseAPIGetValueFromKeyValueStore);
    //    std::thread clientGet1(testClienUseAPIGetValueFromKeyValueStore);

    //    thread clientRemove(testClienUseAPIRemoveFromKeyValueStore);
    //    thread clientExist(testClientUseAPIExistFromKeyValueStore);
    //    thread clientSet(testClientUseAPTSetFromKeyValueStore);
    //
    //
    //
    //
    //    clientGet.join();
    //    clientExist.join();
    //    clientRemove.join();
    //    clientSet.join();
    //    clientGet1.join();



    return 0;
}

