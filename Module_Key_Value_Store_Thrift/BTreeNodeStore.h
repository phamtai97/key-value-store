/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BTreeNodeStore.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:05 PM
 */

#ifndef BTREENODESTORE_H
#define BTREENODESTORE_H
#include "Comparetor.h"
#include "Entry.h"

template<class K, class V>
class BTreeStore;

template<class K, class V>
class BTreeNodeStore {
private:
    int nCurrentEntry;
    int t;
    char flag;
    int *arrayPosKey;
    int *arrayPosChild;
    int pos;
    Comparator<K, V>* myCompare;

public:
    BTreeNodeStore(const int& t, bool isLeaf);

    BTreeNodeStore(const int &t);

    ~BTreeNodeStore();

    void addPosEntry(const int &i, const int &pos);
    void addPosChild(const int &i, const int &pos);

    void increaseNCurrentEntry();

    int* getArrayPosKey() const;
    void setArrayPosKey(int* arrPosKey);
    int* getArrayPosChild() const;
    void setArrayPosChild(int* arrPosChild);

    int getPos() const;
    void setPost(const int& pos);

    char getFlag() const;
    void setFlag(char flag);

    int getNCurrentEntry() const;
    void setNCurrentEntry(const int& nCurrentEntry);

    int getPosChild(const int &i);
    int getPosEntry(const int &i) const;

    void setMinimumDegre(const int& t);
    int getMinimumDegre() const;

    bool checkIsLeaf() const;

    int findKeyBinarySearch(BTreeStore<K, V>* bTree, const K& key);

    void splitChild(BTreeStore<K, V>* bTree, const int &index, BTreeNodeStore<K, V>* &node);

    Entry<K, V>* getEntry(BTreeStore<K, V>* bTree, const int &i);

    BTreeNodeStore<K, V>* getBTreeNodeStore(BTreeStore<K, V>* bTree, const int &i);

    void insertNotFull(BTreeStore<K, V>* bTree, const Entry<K, V>* entry);

    void traverse(BTreeStore<K, V>* bTree);

    Entry<K, V>* search(BTreeStore<K, V>* bTree, const K& key);

    bool set(BTreeStore<K, V> *bTree, const K &key, const V &value);

    bool remove(BTreeStore<K, V>* bTree, const K& key);
    bool removeFromLeaf(BTreeStore<K, V>* bTree, const int& index);
    bool removeFromNonLeaf(BTreeStore<K, V>* bTree, const int& index);

    int getPosEntryPred(BTreeStore<K, V>* bTree, const int& index);
    int getPosEntrySucc(BTreeStore<K, V>* bTree, const int& index);

    void mergeNode(BTreeStore<K, V>* bTree, const int& index);

    void fillNode(BTreeStore<K, V>* bTree, const int& index);

    void borrowFromNodePrev(BTreeStore<K, V>* bTree, const int &index);
    void borrowFromNodeNext(BTreeStore<K, V>* bTree, const int &index);


};


#endif /* BTREENODESTORE_H */

#ifndef BTREENODESTORE_IMPL_H
#include "BTreeNodeStore_impl.h"
#endif

