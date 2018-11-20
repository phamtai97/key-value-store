/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BTreeNode_impl.h
 * Author: taipham
 *
 * Created on September 20, 2018, 9:28 PM
 */

#ifndef BTREENODE_IMPL_H
#define BTREENODE_IMPL_H

#include "Comparetor.h"
#include "Entry.h"


#ifndef BTREENODE_H
#include "BTreeNode.h"
#endif

template <class K, class V>
BTreeNode<K, V>::BTreeNode(int t, bool isLeaf) {
    this->t = t;
    if (isLeaf) {
        this->flag = 1;
    } else {
        this->flag = 0;
    }
    this->entries = new Entry<K, V> * [2 * t - 1];
    this->childs = new BTreeNode<K, V> * [2 * t];
    this->nCurrentEntry = 0;
    myCompare = new StringStringComparator();
    //        myCompare = new IntStringComparator();
}

template <class K, class V>
BTreeNode<K, V>::~BTreeNode() {
    if (!this->checkDeleteChild()) {
        for (int i = 0; i < this->nCurrentEntry; ++i) {
            delete this->entries[i];
            this->entries[i] = NULL;
        }
        for (int i = 0; i <= this->nCurrentEntry; ++i) {
            delete this->childs[i];
            this->childs[i] = NULL;
        }
    }
    if (this->entries != NULL) {
        delete []entries;
        this->entries = NULL;
    }
    if (this->childs != NULL) {
        delete []childs;
        this->childs = NULL;
    }
    if (this->myCompare != NULL) {
        delete this->myCompare;
        this->myCompare = NULL;
    }
}

template <class K, class V>
int BTreeNode<K, V>::getNCurrentEntry() {
    return this->nCurrentEntry;
}

template <class K, class V>
int BTreeNode<K, V>::increaseNCurrentEntry() {
    this->nCurrentEntry++;
}

template <class K, class V>
int BTreeNode<K, V>::setNCurrentEntry(const int &n) {
    this->nCurrentEntry = n;
}

template <class K, class V>
const Entry<K, V>* BTreeNode<K, V>::getEntry(const int &i) const {
    return this->entries[i];
}

template <class K, class V>
void BTreeNode<K, V>::addEntry(const int &i, Entry<K, V>* &entry) {
    this->entries[i] = entry;
}

template <class K, class V>
BTreeNode<K, V>* BTreeNode<K, V>::getChild(const int &i) const {
    return this->childs[i];
}

template <class K, class V>
void BTreeNode<K, V>::addChild(const int &i, BTreeNode<K, V>* child) const {
    this->childs[i] = child;
}

template <class K, class V>
bool BTreeNode<K, V>::checkIsLeaf() const {
    return (this->flag & 1) == 1;
}

template <class K, class V>
void BTreeNode<K, V>::setDeleteChild(const bool &value) {
    if (value) {
        this->flag = this->flag | (1 << 1);
    } else {
        this->flag = this->flag & (~(1 << 1));
    }
}

template <class K, class V>
bool BTreeNode<K, V>::checkDeleteChild() {
    return ((this->flag >> 1) & 1) == 1;
}

template <class K, class V>
void BTreeNode<K, V> ::traverse() {
    int i;
    for (i = 0; i < this->nCurrentEntry; ++i) {
        if (!this->checkIsLeaf()) {
            cout << endl;
            this->childs[i]->traverse();
            cout << endl;

        }
        cout << this->entries[i]->getKey() << " ";
    }
    if (!this->checkIsLeaf()) {
        cout << endl;
        this->childs[i]->traverse();
        cout << endl;
    }
}

template <class K, class V>
const Entry<K, V>* BTreeNode<K, V>::search(const K &key) const {
    int i = 0;
    i = this->findKeyBinarySearch(key);
    if (i < this->nCurrentEntry && this->myCompare->compareKey(
            this->entries[i]->getKey(), key) == 0) {
        return this->entries[i];
    }
    if (this->checkIsLeaf()) {
        return NULL;
    }
    return this->childs[i]->search(key);
}

template<class K, class V>
void BTreeNode<K, V>::splitChild(const int &index, BTreeNode<K, V>* &node) {
    //Create a new node which is going to store (t-1) keys of y
    BTreeNode<K, V>* newNode = new BTreeNode(node->t, node->checkIsLeaf());
    newNode->nCurrentEntry = this->t - 1;
    //Copy the last (t-1) keys of node to newNode

    for (int i = 0; i < this->t - 1; i++) {
        newNode->entries[i] = node->entries[i + t];
    }
    //Copy the last (t-1) child of node to newNode
    if (!node->checkIsLeaf()) {
        for (int i = 0; i < this->t; i++) {
            newNode->childs[i] = node->childs[i + t];
        }
    }
    // Reduce the number of keys in
    node->nCurrentEntry = this->t - 1;

    for (int i = this->nCurrentEntry; i >= index + 1; --i) {
        this->childs[i + 1] = this->childs[i];
    }
    this->childs[index + 1] = newNode;

    for (int i = this->nCurrentEntry - 1; i >= index; --i) {
        this->entries[i + 1] = this->entries[i];
    }
    //go up entry middlle node
    this->entries[index] = node->entries[this->t - 1];
    this->nCurrentEntry = this->nCurrentEntry + 1;
}

template<class K, class V>
void BTreeNode<K, V>::insertNonFull(const Entry<K, V>* entry) {
    int i = this->nCurrentEntry - 1;
    if (this->checkIsLeaf()) {
        while (i >= 0 && this->myCompare->compareKey(this->entries[i]->getKey(),
                entry->getKey()) > 0) {
            this->entries[i + 1] = this->entries[i];
            i--;
        }
        this->entries[i + 1] = const_cast<Entry<K, V>*> (entry);
        this->nCurrentEntry = this->nCurrentEntry + 1;
    } else {
        //Find the child which is going to have the new key
        while (i >= 0 && this->myCompare->compareKey(this->entries[i]->getKey(),
                entry->getKey()) > 0) {
            i--;
        }
        if (this->childs[i + 1]->nCurrentEntry == 2 * this->t - 1) {
            this->splitChild(i + 1, this->childs[i + 1]);
            if (this->myCompare->compareKey(this->entries[i + 1]->getKey(),
                    entry->getKey()) < 0) {
                i++;
            }
        }
        this->childs[i + 1]->insertNonFull(entry);
    }
}

template<class K, class V>
void BTreeNode<K, V>::set(const K &key, const V &value) {
    Entry<K, V>* entry = const_cast<Entry<K, V>*> (this->search(key));
    entry->setValue(value);
}

template<class K, class V>
int BTreeNode<K, V>::findKey(const K &key) const {
    int i = 0;

    while (i < this->nCurrentEntry && this->myCompare->compareKey(
            this->entries[i]->getKey(), key) < 0) {
        ++i;
    }
    return i;
}

template<class K, class V>
int BTreeNode<K, V> ::findKeyBinarySearch(const K& key) const {
    int low = 0;
    int hight = this->nCurrentEntry - 1;

    //    cout << this->nCurrentEntry << endl;

    int middle = (low + hight) / 2;
    while (low <= hight) {
        if (this->myCompare->compareKey(this->entries[middle]->getKey(), key) == 0) {
            return middle;
        } else if (this->myCompare->compareKey(this->entries[middle]->getKey(), key) > 0) {
            hight = middle - 1;
        } else {
            low = middle + 1;
        }

        middle = (low + hight) / 2;
    }
    return hight + 1;
}

template<class K, class V>
bool BTreeNode<K, V>::remove(const K &key) {
    int index = this->findKeyBinarySearch(key);
    cout << "index: " << index << endl;
    bool res;
    if (index < this->nCurrentEntry && this->myCompare->compareKey(
            this->entries[index]->getKey(), key) == 0) {
        if (this->checkIsLeaf()) {
            res = this->removeFromLeaf(index);
        } else {
            res = this->removeFromNonLeaf(index);
        }
    } else {
        if (this->checkIsLeaf()) {
            return false;
        }
        bool flag = index == this->nCurrentEntry ? true : false;
        if (this->childs[index]->nCurrentEntry < this->t) {
            this->fillNode(index);
        }
        //int main(int argc, char** argv) {
        //    //    testRemoveKeyBTree();
        if (flag && index > this->nCurrentEntry) {
            res = this->childs[index - 1]->remove(key);
        } else {
            res = this->childs[index]->remove(key);
        }
    }
    return res;
}

template<class K, class V>
bool BTreeNode<K, V>::removeFromLeaf(const int &index) {
    for (int i = index + 1; i < this->nCurrentEntry; ++i) {
        this->entries[i - 1] = this->entries[i];
    }
    this->nCurrentEntry--;
    return true;
}

template<class K, class V>
bool BTreeNode<K, V>::removeFromNonLeaf(const int &index) {
    Entry<K, V>* entry = this->entries[index];
    //find the predecessor of entry
    if (this->childs[index]->nCurrentEntry >= t) {
        Entry<K, V>* entryPred = const_cast<Entry<K, V>*> (this->getPred(index));
        this->entries[index] = entryPred;
        return this->childs[index]->remove(entryPred->getKey());
    }//find the successor of entry
    else if (this->childs[index + 1]->nCurrentEntry >= t) {
        Entry<K, V>* entrySucc = const_cast<Entry<K, V>*> (this->getSucc(index));
        this->entries[index] = entrySucc;
        return this->childs[index + 1]->remove(entrySucc->getKey());
    } else {
        this->mergeNode(index);
        return this->childs[index]->remove(entry->getKey());
    }
}

template<class K, class V>
const Entry<K, V>* BTreeNode<K, V>::getPred(const int &index) const {
    BTreeNode<K, V>* nodeCurrent = this->childs[index];
    while (!nodeCurrent->checkIsLeaf()) {
        nodeCurrent = nodeCurrent->childs[nodeCurrent->nCurrentEntry];
    }
    return nodeCurrent->entries[nodeCurrent->nCurrentEntry - 1];
}

template<class K, class V>
const Entry<K, V>* BTreeNode<K, V>::getSucc(const int &index) const {
    BTreeNode<K, V>* nodeCurrent = this->childs[index + 1];
    while (!nodeCurrent->checkIsLeaf()) {
        nodeCurrent = nodeCurrent->childs[0];
    }
    return nodeCurrent->entries[0];
}

template<class K, class V>
void BTreeNode<K, V>::mergeNode(const int &index) {
    BTreeNode<K, V>* child = this->childs[index];
    BTreeNode<K, V>* childNext = this->childs[index + 1];
    child->entries[this->t - 1] = this->entries[index];
    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i = 0; i < childNext->nCurrentEntry; ++i) {
        child->entries[i + this->t] = childNext->entries[i];
    }
    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->checkIsLeaf()) {
        for (int i = 0; i <= childNext->nCurrentEntry; ++i) {
            child->childs[i + this->t] = childNext->childs[i];
        }
    }
    for (int i = index + 1; i < this->nCurrentEntry; ++i) {
        this->entries[i - 1] = this->entries[i];
    }
    for (int i = index + 1; i < this->nCurrentEntry; ++i) {
        this->childs[i] = this->childs[i + 1];
    }
    child->nCurrentEntry = child->nCurrentEntry + childNext->nCurrentEntry + 1;
    this->nCurrentEntry--;
    childNext->setDeleteChild(true);
    delete childNext;
}

template<class K, class V>
void BTreeNode<K, V>::fillNode(const int &index) {
    if (index != 0 && this->childs[index - 1]->nCurrentEntry >= t) {
        this->borrowFromNodePrev(index);
    } else if (index != this->nCurrentEntry && this->childs[index + 1]->nCurrentEntry >= t) {
        this->borrowFromNodeNext(index);
    } else {
        if (index != this->nCurrentEntry) {
            this->mergeNode(index);
        } else {
            this->mergeNode(index - 1);
        }
    }
}

template<class K, class V>
void BTreeNode<K, V>::borrowFromNodePrev(const int &index) {
    BTreeNode<K, V>* child = this->childs[index];
    BTreeNode<K, V>* childPrev = this->childs[index - 1];
    for (int i = child->nCurrentEntry - 1; i >= 0; --i) {
        child->entries[i + 1] = child->entries[i];
    }
    if (!child->checkIsLeaf()) {
        for (int i = child->nCurrentEntry; i >= 0; --i) {
            child->childs[i + 1] = child->childs[i];
        }
    }
    child->entries[0] = this->entries[index - 1];
    if (!child->checkIsLeaf()) {
        child->childs[0] = childPrev->childs[childPrev->nCurrentEntry];
    }
    this->entries[index - 1] = childPrev->entries[childPrev->nCurrentEntry - 1];
    child->nCurrentEntry++;
    childPrev->nCurrentEntry--;
}

template<class K, class V>
void BTreeNode<K, V>::borrowFromNodeNext(const int &index) {
    BTreeNode<K, V>* child = this->childs[index];
    BTreeNode<K, V>* childNext = this->childs[index + 1];
    child->entries[child->nCurrentEntry] = this->entries[index];
    if (!child->checkIsLeaf()) {
        child->childs[child->nCurrentEntry + 1] = childNext->childs[0];
    }
    this->entries[index] = childNext->entries[0];
    for (int i = 1; i < childNext->nCurrentEntry; ++i) {
        childNext->entries[i - 1] = childNext->entries[i];
    }
    if (!childNext->checkIsLeaf()) {
        for (int i = 1; i <= childNext->nCurrentEntry; ++i) {
            childNext->childs[i - 1] = childNext->childs[i];
        }
    }
    child->nCurrentEntry++;
    childNext->nCurrentEntry--;
}
#endif /* BTREENODE_IMPL_H */

