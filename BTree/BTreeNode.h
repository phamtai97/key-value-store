/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BTreeNode.h
 * Author: taipham

 * Created on September 18, 2018, 2:52 PM
 */

#ifndef BTREENODE_H
#define BTREENODE_H
#include "Entry.h"
#include "Comparetor.h"

template<class K, class V>
class BTreeNode {
private:
    int nCurrentEntry;
    int t;
    char flag;
    Entry<K, V> **entries;
    BTreeNode<K, V> **childs;
    Comparator<K, V>* myCompare;
public:

    BTreeNode(int t, bool isLeaf);

    ~BTreeNode();

    int getNCurrentEntry();

    int increaseNCurrentEntry();

    int setNCurrentEntry(const int &n);

    const Entry<K, V>* getEntry(const int &i) const;

    void addEntry(const int &i, Entry<K, V>* &entry);

    BTreeNode<K, V>* getChild(const int &i) const;

    void addChild(const int &i, BTreeNode<K, V>* child) const;

    bool checkIsLeaf() const;

    void setDeleteChild(const bool &value);

    bool checkDeleteChild();

    void traverse();

    const Entry<K, V>* search(const K &key) const;

    void splitChild(const int &i, BTreeNode<K, V>* &node);

    void insertNonFull(const Entry<K, V>* entry);

    void set(const K &key, const V &value);

    int findKey(const K &key) const;

    int findKeyBinarySearch(const K &key) const;

    bool remove(const K &key);

    bool removeFromLeaf(const int &index);

    bool removeFromNonLeaf(const int &index);

    const Entry<K, V>* getPred(const int &index) const;

    const Entry<K, V>* getSucc(const int &index) const;

    void mergeNode(const int &index);

    void fillNode(const int &index);

    void borrowFromNodePrev(const int &ndex);

    void borrowFromNodeNext(const int &index);
};

#endif /* BTREENODE_H */

#ifndef BTREENODE_IMPL_H
#include "BTreeNode_impl.h"
#endif
