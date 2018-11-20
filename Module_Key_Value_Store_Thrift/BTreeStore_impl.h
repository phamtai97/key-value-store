/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BTreeStore_impl.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:02 PM
 */

#ifndef BTREESTORE_IMPL_H
#define BTREESTORE_IMPL_H
#ifndef BTREESTORE_H

#include "BTreeNodeStore.h"
#include "BTreeStore.h"

#endif /* BTREESTORE_H */

template<class K, class V>
BTreeStore<K, V> ::BTreeStore() {
    int fdr, fdw, pos, t;
    char flag;
    int nCurrentKey;
    std::thread::id idThread = std::this_thread::get_id();
    cout << "thread current: " << idThread << endl;

    this->manageFileWrite = new ManageFileWrite();

    this->manageFileRead = new ManageFileRead();

    fdw = this->manageFileWrite->openFile(this->PATH);
    if (fdw < 0) {
        exit(EXIT_FAILURE);
    }

    fdr = this->manageFileRead->openFile(this->PATH);
    if (fdr < 0) {
        exit(EXIT_FAILURE);
    }


    this->writeDisk = new BytesDataOutputStore(this->MAXLEN, fdw);
    DataInput* readDisk = new BytesDataInputStore(this->MAXLEN, fdr);

    mapReadFile.insert(pair<std::thread::id, DataInput*>(idThread, readDisk));

    this->indexMap++;
    //    this->readDisk = new BytesDataInputStore(this->MAXLEN, fdr);

    this->myCompare = new StringStringComparator();
    this->mySerialization = new StringSerialization();

    pthread_rwlock_init(&(this->rwLock), NULL);

    if (this->manageFileRead->isEmptyFile()) {
        this->root = NULL;
        return;
    }

    this->readHeader(t, pos);

    this->t = t;

    if (pos == -1) {
        this->root = NULL;
        return;
    }

    this->root = new BTreeNodeStore<K, V>(t);
    this->readNode(this->root, pos);
}

template<class K, class V>
BTreeStore<K, V> ::~BTreeStore() {
    if (this->root != NULL) {
        delete this-> root;
        this->root = NULL;
    }

    if (this->myCompare != NULL) {
        delete this->myCompare;
        this->myCompare = NULL;
    }

    if (this->manageFileRead != NULL) {
        delete this->manageFileRead;
        this->manageFileRead = NULL;
    }

    if (this->manageFileWrite != NULL) {
        delete this->manageFileWrite;
        this->manageFileWrite = NULL;
    }

    if (this->mySerialization != NULL) {
        delete this->mySerialization;
        this->mySerialization = NULL;

    }

    if (this->writeDisk != NULL) {
        delete this->writeDisk;
        this->writeDisk = NULL;
    }

    //delete map
    map<std::thread::id, DataInput*>::iterator temp;
    for (temp = this->mapReadFile.begin(); temp != this->mapReadFile.end(); temp++) {
        if (temp->second != NULL) {
            delete temp->second;
            temp->second = NULL;
        }
    }
    //    if (this->readDisk != NULL) {
    //        delete this->readDisk;
    //        this->readDisk = NULL;
    //    }

    pthread_rwlock_destroy(&(this->rwLock));
}

template<class K, class V>
void BTreeStore<K, V>::writeMinimumDegree(const int &t) const {
    this->writeDisk->writeInt(t);
    this->writeDisk->flush();
}

template<class K, class V>
void BTreeStore<K, V>::readHeader(int& t, int& posRoot) {
    std::map<std::thread::id, DataInput*>::iterator it;

    std::thread::id idThread = std::this_thread::get_id();
    DataInput* readDisk;

    it = this->mapReadFile.find(idThread);

    if (it != mapReadFile.end()) {
        readDisk = it->second;
    } else {
        lockMapReadFile.lock();
        readDisk = new BytesDataInputStore(this->MAXLEN, this->manageFileRead->getFd(this->indexMap));
        this->mapReadFile.insert(pair<std::thread::id, DataInput*> (idThread, readDisk));
        this->indexMap++;
        cout << "thread id1: " << idThread << endl;
        lockMapReadFile.unlock();
    }

    this->manageFileRead->setPosFile(readDisk->getFd(), 0);

    readDisk->resetBuffer();
    readDisk->readInt(t);
    readDisk->readInt(posRoot);
}

template<class K, class V>
void BTreeStore<K, V> ::writeHeader(const int& t, const int& posRoot) {
    this->manageFileWrite->setPosFile(this->manageFileWrite->getFd(), 0);

    this->writeDisk->writeInt(t);
    this->writeDisk->writeInt(posRoot);
    this->writeDisk->flush();
}

template<class K, class V>
void BTreeStore<K, V> ::writeUpdatePosRoot(const int& posRoot) {
    this->manageFileWrite->setPosFile(this->manageFileWrite->getFd(), 4);

    this->writeDisk->writeInt(posRoot);
    this->writeDisk->flush();
}

template<class K, class V>
void BTreeStore<K, V>::writeHeaderNode(const char& flag, const int& nCurrentKey) {
    this->writeDisk->writeByte(flag); // write 1 byte flag = 1
    this->writeDisk->writeInt(nCurrentKey); //write 4 byte : nCurrent = 1;
    this->writeDisk->flush();
}

template<class K, class V>
void BTreeStore<K, V>::readHeaderNode(char& flag, int& nCurrentKey) {
    std::map<std::thread::id, DataInput*>::iterator it;

    std::thread::id idThread = std::this_thread::get_id();
    DataInput* readDisk;

    it = this->mapReadFile.find(idThread);

    if (it != mapReadFile.end()) {
        readDisk = it->second;
    } else {
        lockMapReadFile.lock();
        readDisk = new BytesDataInputStore(this->MAXLEN, this->manageFileRead->getFd(this->indexMap));
        this->mapReadFile.insert(pair<std::thread::id, DataInput*> (idThread, readDisk));
        this->indexMap++;
        cout << "thread id2: " << idThread << endl;
        lockMapReadFile.unlock();
    }

    readDisk->resetBuffer();

    readDisk->readByte((uint8_t&) flag);
    readDisk->readInt(nCurrentKey);
}

template<class K, class V>
void BTreeStore<K, V> ::writeNode(BTreeNodeStore<K, V>* node, const int pos) {
    std::thread::id idThread = std::this_thread::get_id();

    this->manageFileWrite->setPosFile(this->manageFileWrite->getFd(), pos);

    int* arrPosKey = node->getArrayPosKey();
    int* arrPosChild = node->getArrayPosChild();
    char flag = node->getFlag();
    int nCurrentEntry = node->getNCurrentEntry();
    int size = 2 * this->t;

    this->writeDisk->writeByte(flag);
    this->writeDisk->writeInt(nCurrentEntry);
    this->writeDisk->writeArrayInt(arrPosKey, size - 1);
    this->writeDisk->writeArrayInt(arrPosChild, size);
    this->writeDisk->flush();
}

template<class K, class V>
void BTreeStore<K, V>::readNode(BTreeNodeStore<K, V>* node, const int pos) {
    int nCurrentKey;
    char flag;
    int size = 2 * this->t;
    int *arrPosKey = new int[size - 1];
    int *arrPosChild = new int[size];

    std::map<std::thread::id, DataInput*>::iterator it;

    std::thread::id idThread = std::this_thread::get_id();
    DataInput* readDisk;

    it = this->mapReadFile.find(idThread);

    if (it != mapReadFile.end()) {
        readDisk = it->second;
    } else {
        lockMapReadFile.lock();
        readDisk = new BytesDataInputStore(this->MAXLEN, this->manageFileRead->getFd(this->indexMap));
        this->mapReadFile.insert(pair<std::thread::id, DataInput*> (idThread, readDisk));
        this->indexMap++;
        cout << "thread id3: " << idThread << endl;

        lockMapReadFile.unlock();
    }

    this->manageFileRead->setPosFile(readDisk->getFd(), pos);

    readDisk->resetBuffer();

    readDisk->readByte((uint8_t&) flag);
    readDisk->readInt(nCurrentKey);
    readDisk->readArrayInt(arrPosKey, size - 1);
    readDisk->readArrayInt(arrPosChild, size);

    node->setFlag(flag);
    node->setPost(pos);
    node->setMinimumDegre(this->t);
    node->setNCurrentEntry(nCurrentKey);
    node->setArrayPosKey(arrPosKey);
    node->setArrayPosChild(arrPosChild);
}

template<class K, class V>
void BTreeStore<K, V>::writeEntry(const Entry<K, V>* entry, const int& pos) {
    char flag = 1;
    string strKey = entry->getKey();
    string strValue = entry->getValue();

    string key = this->mySerialization->serializationKey(strKey);
    string value = this->mySerialization->serializationValue(strValue);

    this->manageFileWrite->setPosFile(this->manageFileWrite->getFd(), pos);
    //write flag: danh dau da remove or active or edit
    this->writeDisk->writeByte(flag);
    //write key
    this->writeDisk->writeBytes((uint8_t*) key.c_str(), 0, key.length());
    //write value
    this->writeDisk->writeBytes((uint8_t*) value.c_str(), 0, value.length());

    this->writeDisk->flush();
    //
    //    delete[] key;
    //    delete[] value;
}

template<class K, class V>
void BTreeStore<K, V>::readEntry(Entry<K, V>* entry, const int& pos) {
    string key;
    string value;
    char flag;
    int lenKey, lenValue;

    std::map<std::thread::id, DataInput*>::iterator it;

    std::thread::id idThread = std::this_thread::get_id();
    DataInput* readDisk;

    it = this->mapReadFile.find(idThread);

    if (it != mapReadFile.end()) {
        readDisk = it->second;
    } else {
        lockMapReadFile.lock();
        readDisk = new BytesDataInputStore(this->MAXLEN, this->manageFileRead->getFd(this->indexMap));
        this->mapReadFile.insert(pair<std::thread::id, DataInput*> (idThread, readDisk));
        this->indexMap++;
        cout << "thread id4: " << idThread << endl;
        lockMapReadFile.unlock();
    }

    this->manageFileRead->setPosFile(readDisk->getFd(), pos);

    readDisk->resetBuffer();

    readDisk->readByte((uint8_t&) flag);

    readDisk->readBytes(reinterpret_cast<uint8_t*> (&lenKey), 0, sizeof (lenKey));

    key.resize(lenKey);
    readDisk->readBytes((uint8_t*) key.c_str(), 0, lenKey);

    readDisk->readBytes(reinterpret_cast<uint8_t*> (&lenValue), 0, sizeof (lenValue));
    value.resize(lenValue);
    readDisk->readBytes((uint8_t*) value.c_str(), 0, lenValue);

    entry->setKeyValue(key, value);
}

template<class K, class V>
void BTreeStore<K, V> ::writeFlag(char flag, const int& pos) {
    this->manageFileWrite->setPosFile(this->manageFileWrite->getFd(), pos);

    this->writeDisk->writeByte(flag);
    this->writeDisk->flush();
}

template<class K, class V>
void BTreeStore<K, V> ::insert(const Entry<K, V>* entry) {
    int pos = -1;
    int t = -1;
    if (this->root == NULL) {
        t = MyT;
        this->root = new BTreeNodeStore<K, V>(t, true);
        this->writeHeader(t, 8);
        this->root->setPost(8);
        this->t = t;

        this->manageFileWrite->setPosEndFile(this->manageFileWrite->getFd());
        pos = this->manageFileWrite->getPosFile(this->manageFileWrite->getFd());
        pos = pos + sizeof (int) * (2 * t - 1) + sizeof (int) * (2 * t) + 5; // 1 byte flag + 4 byte nCurrentKey

        this->root->addPosEntry(0, pos);
        this->root->setFlag(1);
        this->root->increaseNCurrentEntry();

        //write node root
        this->writeNode(this->root, root->getPos());

        //write key value
        this->writeEntry(entry, pos);
    } else {
        if (this->root->getNCurrentEntry() == 2 * this->t - 1) {
            BTreeNodeStore<K, V>* newRoot = new BTreeNodeStore<K, V>(this->t, false);

            newRoot->addPosChild(0, this->root->getPos());

            this->manageFileWrite->setPosEndFile(this->manageFileWrite->getFd());

            newRoot->setPost(this->manageFileWrite->getPosFile(this->manageFileWrite->getFd()));
            //write node
            this->writeNode(newRoot, newRoot->getPos());

            newRoot->splitChild(this, 0, this->root);
            //find child have new key
            int i = 0;
            Entry<K, V>* entryOfRoot = newRoot->getEntry(this, 0);
            if (this->myCompare->compareKey(entryOfRoot->getKey(), entry->getKey()) < 0) {
                i++;
            }
            delete entryOfRoot;

            BTreeNodeStore<K, V>* node = new BTreeNodeStore<K, V>(this->t, false);
            pos = newRoot->getPosChild(i);

            //read node
            this->readNode(node, pos);

            node->insertNotFull(this, entry);

            this->readNode(this->root, newRoot->getPos());

            //cap nhat lai header
            this->writeUpdatePosRoot(newRoot->getPos());

            delete newRoot;

            delete node;
        } else {
            this->root->insertNotFull(this, entry);
        }
    }
}

template<class K, class V>
const V* BTreeStore<K, V> ::get(const K& key) {

}

template<class K, class V>
const bool BTreeStore<K, V> ::getValue(const K& key, V& value) {
    pthread_rwlock_rdlock(&(this->rwLock));

    if (this->root == NULL) {
        pthread_rwlock_unlock(&(this->rwLock));
        return false;
    }

    Entry<K, V>* entry = this->root->search(this, key);

    if (entry == NULL) {
        pthread_rwlock_unlock(&(this->rwLock));
        return false;
    }
    value = entry->getValue();

    delete entry;
    pthread_rwlock_unlock(&(this->rwLock));
    return true;
}

template<class K, class V>
void BTreeStore<K, V> ::set(const K& key, const V& value) {
    pthread_rwlock_wrlock(&(this->rwLock));

    if (this->root == NULL) {
        Entry<K, V>* entry = new Entry<K, V>(key, value);
        this->insert(entry);
    } else if (!this->root->set(this, key, value)) {
        Entry<K, V>* entry = new Entry<K, V>(key, value);
        this->insert(entry);
    }

    pthread_rwlock_unlock(&(this->rwLock));
}

template<class K, class V>
bool BTreeStore<K, V> ::exist(const K& key) {
    ManageFile* manageFileRead = new ManageFileRead();

    int fdr = manageFileRead->openFile(this->PATH);
    if (fdr < 0) {
        exit(EXIT_FAILURE);
    }

    pthread_rwlock_rdlock(&(this->rwLock));


    if (this->root == NULL) {
        pthread_rwlock_unlock(&(this->rwLock));
        return false;
    }

    bool res;

    Entry<K, V>* entry = this->root->search(this, key);

    if (entry == NULL) {
        res = false;
    } else {
        delete entry;
        res = true;
    }

    pthread_rwlock_unlock(&(this->rwLock));
    return res;
}

template<class K, class V>
bool BTreeStore<K, V> ::remove(const K& key) {
    bool res;
    pthread_rwlock_wrlock(&(this->rwLock));

    if (!this->root) {
        pthread_rwlock_unlock(&(this->rwLock));
        return false;
    }

    res = this->root->remove(this, key);

    if (this->root->getNCurrentEntry() == 0) {
        if (this->root->checkIsLeaf()) {
            char flag = this->root->getFlag();
            flag = flag | (1 << 1);
            this->writeFlag(flag, this->root->getPos());
            delete this->root;
            this->root = NULL;
            this->writeUpdatePosRoot(-1);
        } else {
            int pos = this->root->getPosChild(0);
            this->writeUpdatePosRoot(pos);
            this->readNode(this->root, pos);
        }
    }

    pthread_rwlock_unlock(&(this->rwLock));
    return res;
}

template<class K, class V>
void BTreeStore<K, V> ::traverse() {
    if (this->root != NULL) {
        this->root->traverse(this);
    }
}

template<class K, class V>
int BTreeStore<K, V> ::getPosFileRead() const {

    //    return this->manageFileRead->getPosFile();
}

template<class K, class V>
void BTreeStore<K, V> ::setPosFileRead(const int& i) {

    //    this->manageFileRead->setPosFile(i);
}

template<class K, class V>
void BTreeStore<K, V> ::setPosEndFileRead() {

    //    this->manageFileRead->setPosEndFile();
}

template<class K, class V>
int BTreeStore<K, V> ::getPosFileWrite() const {
    return this->manageFileWrite->getPosFile(this->manageFileWrite->getFd());
}

template<class K, class V>
void BTreeStore<K, V>::setPosEndFileWrite() {

    this->manageFileWrite->setPosEndFile(this->manageFileWrite->getFd());
}

template<class K, class V>
void BTreeStore<K, V> ::setPosFileWrite(const int& i) {
    this->manageFileWrite->setPosFile(this->manageFileWrite->getFd(), i);
}
#endif /* BTREESTORE_IMPL_H */

