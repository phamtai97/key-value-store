/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BTreeNodeStore_impl.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:06 PM
 */

#ifndef BTREENODESTORE_IMPL_H
#define BTREENODESTORE_IMPL_H

#include "Comparetor.h"
#include "Entry.h"


#ifndef BTREENODESTORE_H
#include "BTreeNodeStore.h"
#include "BTreeStore.h"
#endif

template<class K, class V>
BTreeNodeStore<K, V> ::BTreeNodeStore(const int& t, bool isLeaf) {
    this->t = t;
    if (isLeaf) {
        this->flag = 1;
    } else {
        this->flag = 0;
    }
    int size = 2 * t;
    this->arrayPosKey = new int[size - 1];
    this->arrayPosChild = new int [size];
    for (int i = 0; i < size - 1; ++i) {
        this->arrayPosKey[i] = -1;
        this->arrayPosChild[i] = -1;
    }
    this->arrayPosChild[size - 1] = -1;
    this->nCurrentEntry = 0;
    this->myCompare = new StringStringComparator();
}

template<class K, class V>
BTreeNodeStore<K, V> ::BTreeNodeStore(const int &t) {
    int size = 2 * t;
    this->arrayPosKey = new int[size - 1];
    this->arrayPosChild = new int [size];
    for (int i = 0; i < size - 1; ++i) {
        this->arrayPosKey[i] = -1;
        this->arrayPosChild[i] = -1;
    }
    this->arrayPosChild[size - 1] = -1;
    this->nCurrentEntry = 0;
    this->myCompare = new StringStringComparator();
}

template<class K, class V>
BTreeNodeStore<K, V> ::~BTreeNodeStore() {
    if (this->arrayPosKey != NULL) {
        delete[] this->arrayPosKey;
        this->arrayPosKey = NULL;
    }

    if (this->arrayPosChild != NULL) {
        delete[] this->arrayPosChild;
        this->arrayPosChild = NULL;
    }

    if (this->myCompare != NULL) {
        delete this->myCompare;
        this->myCompare = NULL;
    }
}

template<class K, class V>
void BTreeNodeStore<K, V> ::addPosEntry(const int &i, const int &pos) {
    this->arrayPosKey[i] = pos;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::addPosChild(const int &i, const int &pos) {
    this->arrayPosChild[i] = pos;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::increaseNCurrentEntry() {
    this->nCurrentEntry++;
}

template<class K, class V>
int* BTreeNodeStore<K, V> ::getArrayPosKey() const {
    return this->arrayPosKey;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::setArrayPosKey(int* arrPosKey) {
    int t = this->t;
    memcpy(this->arrayPosKey, arrPosKey, (2 * this->t - 1) * sizeof (int));
}

template<class K, class V>
int* BTreeNodeStore<K, V> ::getArrayPosChild() const {
    return this->arrayPosChild;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::setArrayPosChild(int* arrPosChild) {
    memcpy(this->arrayPosChild, arrPosChild, (2 * this->t) * sizeof (int));
}

template<class K, class V>
int BTreeNodeStore<K, V> ::getPos() const {
    return this->pos;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::setPost(const int& pos) {
    this->pos = pos;
}

template<class K, class V>
char BTreeNodeStore<K, V>::getFlag() const {
    return this->flag;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::setFlag(char flag) {
    this->flag = flag;
}

template<class K, class V>
int BTreeNodeStore<K, V> ::getNCurrentEntry() const {
    return this->nCurrentEntry;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::setNCurrentEntry(const int& nCurrentEntry) {
    this->nCurrentEntry = nCurrentEntry;
}

template<class K, class V>
bool BTreeNodeStore<K, V>::checkIsLeaf() const {
    return (this->flag & 1) == 1;
}

template<class K, class V>
int BTreeNodeStore<K, V> ::getPosChild(const int& i) {
    return this->arrayPosChild[i];
}

template<class K, class V>
int BTreeNodeStore<K, V> ::getPosEntry(const int& i) const {
    return this->arrayPosKey[i];
}

template<class K, class V>
void BTreeNodeStore<K, V> ::setMinimumDegre(const int& t) {
    this->t = t;
}

template<class K, class V>
int BTreeNodeStore<K, V> ::getMinimumDegre() const {
    return this->t;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::splitChild(BTreeStore<K, V>* bTree, const int &index, BTreeNodeStore<K, V>* &node) {
    BTreeNodeStore<K, V>* newNode = new BTreeNodeStore<K, V>(node->t, node->checkIsLeaf());
    newNode->nCurrentEntry = this->t - 1;
    for (int i = 0; i < this->t - 1; i++) {
        newNode->arrayPosKey[i] = node->arrayPosKey[i + t];
        node->arrayPosKey[i + t] = -1;
    }
    if (!node->checkIsLeaf()) {
        for (int i = 0; i < this->t; i++) {
            newNode->arrayPosChild[i] = node->arrayPosChild[i + t];
            node->arrayPosChild[i + t] = -1;
        }
    }

    bTree->setPosEndFileWrite();
    newNode->setPost(bTree->getPosFileWrite());
    //write new node
    bTree->writeNode(newNode, newNode->getPos());

    node->nCurrentEntry = this->t - 1;

    //write node
    bTree->writeNode(node, node->getPos());

    for (int i = this->nCurrentEntry; i >= index + 1; --i) {
        this->arrayPosChild[i + 1] = this->arrayPosChild[i];
    }
    this->arrayPosChild[index + 1] = newNode->getPos();

    for (int i = this->nCurrentEntry - 1; i >= index; --i) {
        this->arrayPosKey[i + 1] = this->arrayPosKey[i];
    }

    this->arrayPosKey[index] = node->arrayPosKey[this->t - 1];
    this->nCurrentEntry = this->nCurrentEntry + 1;

    //write node
    bTree->writeNode(this, this->pos);
    delete newNode;
}

template<class K, class V>
Entry<K, V>* BTreeNodeStore<K, V> ::getEntry(BTreeStore<K, V>* bTree, const int& i) {
    if (i < 0 || i > nCurrentEntry - 1) {
        return NULL;
    }

    int pos = this->arrayPosKey[i];
    Entry<K, V>* entry = new Entry<K, V>();

    //read entry
    bTree->readEntry(entry, pos);
    return entry;
}

template<class K, class V>
BTreeNodeStore<K, V>* BTreeNodeStore<K, V> ::getBTreeNodeStore(BTreeStore<K, V>* bTree, const int& i) {
    if (i < 0 || i > this->nCurrentEntry) {
        return NULL;
    }

    int pos = this->arrayPosChild[i];
    BTreeNodeStore<K, V>* node = new BTreeNodeStore(this->t);

    //read node
    bTree->readNode(node, pos);
    return node;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::insertNotFull(BTreeStore<K, V>* bTree, const Entry<K, V>* entry) {
    int i = this->nCurrentEntry - 1;
    Entry<K, V>* entryTmp;
    entryTmp = this->getEntry(bTree, i);
    int pos;

    if (this->checkIsLeaf()) {
        while (i >= 0 && entryTmp != NULL &&
                this->myCompare->compareKey(entryTmp->getKey(), entry->getKey()) > 0) {
            this->arrayPosKey[i + 1] = this->arrayPosKey[i];
            i--;
            delete entryTmp;
            entryTmp = this->getEntry(bTree, i);
        }

        bTree->setPosEndFileWrite();
        pos = bTree->getPosFileWrite();

        //write entry
        bTree->writeEntry(entry, pos);

        this->arrayPosKey[i + 1] = pos;
        this->nCurrentEntry = this->nCurrentEntry + 1;

        //write node
        bTree->writeNode(this, this->pos);
    } else {
        //nho dung binary search
        //        while (i >= 0 && entryTmp != NULL && this->myCompare->compareKey(entryTmp->getKey(),
        //                entry->getKey()) > 0) {
        //            i--;
        //            delete entryTmp;
        //            entryTmp = this->getEntry(bTree, i);
        //        }

        i = this->findKeyBinarySearch(bTree, entry->getKey());

        BTreeNodeStore<K, V>* node = this->getBTreeNodeStore(bTree, i);

        if (node->nCurrentEntry == 2 * this->t - 1) {
            this->splitChild(bTree, i, node);

            entryTmp = this->getEntry(bTree, i);

            if (this->myCompare->compareKey(entryTmp->getKey(), entry->getKey()) < 0) {
                i++;
            }
            delete entryTmp;

            delete node;
        }

        node = this->getBTreeNodeStore(bTree, i);
        node->insertNotFull(bTree, entry);

        delete node;
    }
}

template<class K, class V>
void BTreeNodeStore<K, V> ::traverse(BTreeStore<K, V>* bTree) {
    int i;
    int pos;
    BTreeNodeStore<K, V>* node;
    Entry<K, V>* entry;
    for (i = 0; i < this->nCurrentEntry; ++i) {
        if (!this->checkIsLeaf()) {
            node = this->getBTreeNodeStore(bTree, i);
            cout << endl;
            node->traverse(bTree);
            cout << endl;
            delete node;
        }
        entry = this->getEntry(bTree, i);
        cout << "[key]: " << entry->getKey() << " - [value]: " << entry->getValue() << " ";
        delete entry;
    }
    if (!this->checkIsLeaf()) {
        node = this->getBTreeNodeStore(bTree, i);
        cout << endl;
        node->traverse(bTree);
        cout << endl;
        delete node;
    }
}

template<class K, class V>
int BTreeNodeStore<K, V> ::findKeyBinarySearch(BTreeStore<K, V>*bTree, const K& key) {
    int low = 0;
    int hight = this->nCurrentEntry - 1;
    int middle = (low + hight) / 2;
    Entry<K, V>* entry = this->getEntry(bTree, middle);
    while (low <= hight) {
        if (this->myCompare->compareKey(entry->getKey(), key) == 0) {
            delete entry;
            return middle;
        } else if (this->myCompare->compareKey(entry->getKey(), key) > 0) {
            hight = middle - 1;
        } else {
            low = middle + 1;
        }
        delete entry;
        middle = (low + hight) / 2;
        entry = this->getEntry(bTree, middle);
    }
    delete entry;
    return hight + 1;
}

//su dung ham search nho delete con tro tra ve

template<class K, class V>
Entry<K, V>* BTreeNodeStore<K, V>::search(BTreeStore<K, V>* bTree, const K& key) {
    int i = 0;
    i = this->findKeyBinarySearch(bTree, key);
    Entry<K, V>* entry = NULL;
    BTreeNodeStore<K, V>* node;

    if (i < this->nCurrentEntry) {
        entry = const_cast<Entry<K, V>*> (this->getEntry(bTree, i));
        if (this->myCompare->compareKey(entry->getKey(), key) == 0) {
            return entry;
        }
    }

    if (this->checkIsLeaf()) {
        delete entry;
        return NULL;
    }

    if (entry != NULL) {
        delete entry;
        entry = NULL;
    }

    node = this->getBTreeNodeStore(bTree, i);

    entry = node->search(bTree, key);

    delete node;
    return entry;
}

template<class K, class V>
bool BTreeNodeStore<K, V> ::set(BTreeStore<K, V>* bTree, const K& key, const V& value) {
    int i = 0;
    int pos;
    i = this->findKeyBinarySearch(bTree, key);
    Entry<K, V>* entry = NULL;
    BTreeNodeStore<K, V>* node;
    bool res = false;
    if (i < this->nCurrentEntry) {
        entry = this->getEntry(bTree, i);
        if (this->myCompare->compareKey(entry->getKey(), key) == 0 &&
                this->myCompare->compareValue(entry->getValue(), value) != 0) {
            bTree->writeFlag('0', this->arrayPosKey[i]);

            bTree->setPosEndFileWrite();
            pos = bTree->getPosFileWrite();

            this->arrayPosKey[i] = pos;
            entry->setValue(value);

            bTree->writeEntry(entry, pos);

            bTree->writeNode(this, this->pos);

            delete entry;
            return true;
        }
        if (this->myCompare->compareKey(entry->getKey(), key) == 0 &&
                this->myCompare->compareValue(entry->getValue(), value) == 0) {
            return true;
        }
    }

    if (this->checkIsLeaf()) {
        delete entry;
        return false;
    }
    if (entry != NULL) {
        delete entry;
        entry = NULL;
    }

    node = this->getBTreeNodeStore(bTree, i);
    res = node->set(bTree, key, value);

    delete node;
    return res;
}

template<class K, class V>
bool BTreeNodeStore<K, V>::remove(BTreeStore<K, V>* bTree, const K& key) {
    int index = this->findKeyBinarySearch(bTree, key);
    bool res;
    Entry<K, V>* entry = this->getEntry(bTree, index);
    if (index < this->nCurrentEntry && this->myCompare->compareKey(entry->getKey(), key) == 0) {
        if (this->checkIsLeaf()) {
            res = this->removeFromLeaf(bTree, index);
        } else {
            res = this->removeFromNonLeaf(bTree, index);
        }
        //write node;
        bTree->writeNode(this, this->pos);
    } else {
        if (this->checkIsLeaf()) {
            delete entry;
            return false;
        }

        bool flag = (index == this->nCurrentEntry) ? true : false;
        BTreeNodeStore<K, V>* node = this->getBTreeNodeStore(bTree, index); // nho delete node

        if (node->nCurrentEntry < this->t) {
            this->fillNode(bTree, index);
            node = this->getBTreeNodeStore(bTree, index);
        }
        if (flag && index > this->nCurrentEntry) {
            BTreeNodeStore<K, V>* nodePrev = this->getBTreeNodeStore(bTree, index - 1);
            nodePrev->remove(bTree, key);

            //write node
            bTree->writeNode(nodePrev, nodePrev->pos);
            delete nodePrev;
        } else {
            res = node->remove(bTree, key);
            bTree->writeNode(node, node->pos);
        }

        //write node

        delete node;
    }

    delete entry;

    return res;
}

template<class K, class V>
bool BTreeNodeStore<K, V> ::removeFromLeaf(BTreeStore<K, V>* bTree, const int& index) {
    bTree->writeFlag('0', this->arrayPosKey[index]); //gan flag danh dau remove

    for (int i = index + 1; i < this->nCurrentEntry; ++i) {
        this->arrayPosKey[i - 1] = this->arrayPosKey[i];
    }
    this->nCurrentEntry--;

    return true;
}

template<class K, class V>
bool BTreeNodeStore<K, V> ::removeFromNonLeaf(BTreeStore<K, V>* bTree, const int& index) {
    Entry<K, V>* entry = this->getEntry(bTree, index);
    BTreeNodeStore<K, V>* node = this->getBTreeNodeStore(bTree, index); //nho delete node
    BTreeNodeStore<K, V>* nodeNext = this->getBTreeNodeStore(bTree, index + 1); // nho delete

    int pos;
    bool res;

    if (node->nCurrentEntry >= t) {
        pos = this->getPosEntryPred(bTree, index);
        this->arrayPosKey[index] = pos;

        entry = new Entry<K, V> ();
        bTree->readEntry(entry, pos);

        K key = entry->getKey();
        delete entry;

        res = node->remove(bTree, key);
    } else if (nodeNext->nCurrentEntry >= t) {
        pos = this->getPosEntrySucc(bTree, index);
        this->arrayPosKey[index] = pos;

        entry = new Entry<K, V>();
        bTree->readEntry(entry, pos);

        K key = entry->getKey();
        delete entry;

        res = nodeNext->remove(bTree, key);
    } else {
        this->mergeNode(bTree, index);
        K key = entry->getKey();
        delete entry;

        node = this->getBTreeNodeStore(bTree, index);
        res = node->remove(bTree, key);
    }

    bTree->writeNode(node, node->pos);

    delete node;
    delete nodeNext;

    return res;
}

template<class K, class V>
int BTreeNodeStore<K, V>::getPosEntryPred(BTreeStore<K, V>* bTree, const int& index) {
    //    BTreeNodeStore<K, V>* nodeCurrent = this->getBTreeNodeStore(bTree, index);
    BTreeNodeStore<K, V>* nodeCurrent = new BTreeNodeStore<K, V>(this->t);
    bTree->readNode(nodeCurrent, this->arrayPosChild[index]);
    int tmp;
    while (!nodeCurrent->checkIsLeaf()) {
        bTree->readNode(nodeCurrent, nodeCurrent->arrayPosChild[nodeCurrent->nCurrentEntry]);
    }

    int pos = nodeCurrent->arrayPosKey[nodeCurrent->nCurrentEntry - 1];
    delete nodeCurrent;

    return pos;
}

template<class K, class V>
int BTreeNodeStore<K, V> ::getPosEntrySucc(BTreeStore<K, V>* bTree, const int& index) {
    //    BTreeNodeStore<K, V>* nodeCurrent = this->getBTreeNodeStore(bTree, index + 1);
    BTreeNodeStore<K, V>* nodeCurrent = new BTreeNodeStore<K, V>(this->t);
    bTree->readNode(nodeCurrent, this->arrayPosChild[index + 1]);
    while (!nodeCurrent->checkIsLeaf()) {
        bTree->readNode(nodeCurrent, nodeCurrent->arrayPosChild[0]);
    }

    int pos = nodeCurrent->arrayPosKey[0];
    delete nodeCurrent;

    return pos;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::mergeNode(BTreeStore<K, V>* bTree, const int& index) {
    BTreeNodeStore<K, V>* child = this->getBTreeNodeStore(bTree, index); //nho delete
    BTreeNodeStore<K, V>* childNext = this->getBTreeNodeStore(bTree, index + 1); //nho delete

    child->arrayPosKey[this->t - 1] = this->arrayPosKey[index];

    for (int i = 0; i < childNext->nCurrentEntry; ++i) {
        child->arrayPosKey[i + this->t] = childNext->arrayPosKey[i];
    }
    if (!child->checkIsLeaf()) {
        for (int i = 0; i <= childNext->nCurrentEntry; ++i) {
            child->arrayPosChild[i + this->t] = childNext->arrayPosChild[i];
        }
    }

    child->nCurrentEntry = child->nCurrentEntry + childNext->nCurrentEntry + 1;

    //write node
    bTree->writeNode(child, this->arrayPosChild[index]);

    childNext->flag = childNext->flag | (1 << 1); //bat co da xoa node nay
    //write node
    bTree->writeNode(childNext, this->arrayPosChild[index + 1]);

    for (int i = index + 1; i < this->nCurrentEntry; ++i) {
        this->arrayPosKey[i - 1] = this->arrayPosKey[i];
    }
    for (int i = index + 1; i < this->nCurrentEntry; ++i) {

        this->arrayPosChild[i] = this->arrayPosChild[i + 1];
    }

    this->nCurrentEntry--;
    bTree->writeNode(this, this->pos);

    delete child;
    delete childNext;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::fillNode(BTreeStore<K, V>* bTree, const int& index) {
    BTreeNodeStore<K, V>* childPrev = this->getBTreeNodeStore(bTree, index - 1); // nho delete
    BTreeNodeStore<K, V>* childNext = this->getBTreeNodeStore(bTree, index + 1); // nho delete

    if (index != 0 && childPrev->nCurrentEntry >= t) {
        this->borrowFromNodePrev(bTree, index);
    } else if (index != this->nCurrentEntry && childNext->nCurrentEntry >= t) {
        this->borrowFromNodeNext(bTree, index);
    } else {
        if (index != this->nCurrentEntry) {
            this->mergeNode(bTree, index);
        } else {

            this->mergeNode(bTree, index - 1);
        }
    }

    delete childPrev;
    delete childNext;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::borrowFromNodePrev(BTreeStore<K, V>* bTree, const int& index) {
    BTreeNodeStore<K, V>* childPrev = this->getBTreeNodeStore(bTree, index - 1); // nho delete
    BTreeNodeStore<K, V>* child = this->getBTreeNodeStore(bTree, index); // nho delete
    for (int i = child->nCurrentEntry - 1; i >= 0; --i) {
        child->arrayPosKey[i + 1] = child->arrayPosKey[i];
    }
    if (!child->checkIsLeaf()) {
        for (int i = child->nCurrentEntry; i >= 0; --i) {
            child->arrayPosChild[i + 1] = child->arrayPosChild[i];
        }
    }

    child->arrayPosKey[0] = this->arrayPosKey[index - 1];
    if (!child->checkIsLeaf()) {

        child->arrayPosChild[0] = childPrev->arrayPosChild[childPrev->nCurrentEntry];
    }
    this->arrayPosKey[index - 1] = childPrev->arrayPosKey[childPrev->nCurrentEntry - 1];
    child->nCurrentEntry++;
    childPrev->nCurrentEntry--;

    bTree->writeNode(child, child->pos);
    bTree->writeNode(childPrev, childPrev->pos);
    bTree->writeNode(this, this->pos);

    delete childPrev;
    delete child;
}

template<class K, class V>
void BTreeNodeStore<K, V> ::borrowFromNodeNext(BTreeStore<K, V>* bTree, const int& index) {
    BTreeNodeStore<K, V>* childNext = this->getBTreeNodeStore(bTree, index + 1); // nho delete
    BTreeNodeStore<K, V>* child = this->getBTreeNodeStore(bTree, index); // nho delete
    child->arrayPosKey[child->nCurrentEntry] = this->arrayPosKey[index];

    if (!child->checkIsLeaf()) {
        child->arrayPosChild[child->nCurrentEntry + 1] = childNext->arrayPosChild[0];
    }

    this->arrayPosKey[index] = childNext->arrayPosKey[0];
    for (int i = 1; i < childNext->nCurrentEntry; ++i) {
        childNext->arrayPosKey[i - 1] = childNext->arrayPosKey[i];
    }
    if (!childNext->checkIsLeaf()) {
        for (int i = 1; i <= childNext->nCurrentEntry; ++i) {
            childNext->arrayPosChild[i - 1] = childNext->arrayPosChild[i];
        }
    }
    child->nCurrentEntry++;
    childNext->nCurrentEntry--;

    bTree->writeNode(child, child->pos);
    bTree->writeNode(childNext, childNext->pos);
    bTree->writeNode(this, this->pos);

    delete childNext;
    delete child;

}
#endif /* BTREENODESTORE_IMPL_H */