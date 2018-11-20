/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BTreeStore.h
 * Author: phamtai97
 *
 * Created on October 12, 2018, 8:05 AM
 */

#ifndef BTREESTORE_H
#define BTREESTORE_H
#include <bits/pthreadtypes.h>

#include "KeyValueStore.h"
#include "BTreeNodeStore.h"
#include "Comparetor.h"
#include "header.h"
#include "ManageFile.h"
#include "ManageFileRead.h"
#include "ManageFileWrite.h"
#include "DataOutput.h"
#include "DataInput.h"
#include "Entry.h"
#include "Serialization.h"


typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_usec + (timestamp_t) now.tv_sec * 1000000;
}

template<class K, class V>
class BTreeNodeStore;

template <class K, class V>
class BTreeStore : public KeyValueStore<K, V> {
private:
    const int MAXLEN = 1024;
    const char* PATH = "./database.txt";
    int t;
    pthread_rwlock_t rwLock;
    BTreeNodeStore<K, V>* root;
    Comparator<K, V>* myCompare;
    Serialization<K, V>* mySerialization;
    ManageFile* manageFileRead;
    ManageFile* manageFileWrite;
    DataOutput* writeDisk;
    DataInput* readDisk;

public:
    BTreeStore();
    ~BTreeStore();

    const V* get(const K& key) override;

    void set(const K& key, const V& value) override;

    bool remove(const K& key) override;

    bool exist(const K& key) override;

    const bool getValue(const K& key, V& value) override;

    void traverse() override;

    void writeNode(BTreeNodeStore<K, V>* node, const int pos);
    void readNode(BTreeNodeStore<K, V>* node, const int pos);
    void writeEntry(const Entry<K, V>* entry, const int& pos);
    void readEntry(Entry<K, V>* entry, const int& pos);

    void writeFlag(char flag, const int &pos);

    int getPosFileRead() const;
    void setPosFileRead(const int& i);
    void setPosEndFileRead();

    int getPosFileWrite() const;
    void setPosFileWrite(const int& i);
    void setPosEndFileWrite();

    void insert(const Entry<K, V>* entry);

private:

    void writeMinimumDegree(const int &t) const;
    void readHeader(int &t, int &posRoot);
    void writeHeader(const int &t, const int &posRoot);
    void writeHeaderNode(const char &flag, const int &nCurrentKey);
    void readHeaderNode(char &flag, int &nCurrentKey);
    void writeUpdatePosRoot(const int &posRoot);
};

#endif /* BTREESTORE_H */

#ifndef BTREESTORE_IMPL_H
#include "BTreeStore_impl.h"
#endif