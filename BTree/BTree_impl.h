/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BTree_impl.h
 * Author: taipham
 *
 * Created on September 20, 2018, 9:25 PM
 */

#ifndef BTREE_IMPL_H
#define BTREE_IMPL_H
#ifndef BTREE_H

#include "Entry.h"


#include "Comparetor.h"


#include "BTreeNode.h"

#include "BTree.h"
#endif /* BTREE_H */

template<class K, class V>
BTree<K, V>::BTree(int t) {
    this->root = NULL;
    this->t = t;
    this->myCompare = new StringStringComparator();
    //        myCompare = new IntStringComparator();
}

template<class K, class V>
BTree<K, V>::~BTree() {
    if (this->root != NULL) {
        delete root;
        root = NULL;
    }
    if (this->myCompare != NULL) {
        delete this->myCompare;
        this->myCompare = NULL;
    }
}

template<class K, class V>
void BTree<K, V>::traverse() {
    if (this->root != NULL) {
        this->root->traverse();
    }
}

template<class K, class V>
void BTree<K, V>::insert(const Entry<K, V>* entry) {
    Entry<K, V>* entryTmp = new Entry<K, V>(entry);
    if (this->root == NULL) {
        this->root = new BTreeNode<K, V>(this->t, true);
        this->root->addEntry(0, entryTmp);
        this->root->increaseNCurrentEntry();
    } else {
        if (this->root->getNCurrentEntry() == 2 * this->t - 1) {
            //new node root
            BTreeNode<K, V>* newRoot = new BTreeNode<K, V>(this->t, false);
            newRoot->addChild(0, this->root);
            newRoot->splitChild(0, this->root);
            //find child have new key
            int i = 0;
            if (this->myCompare->compareKey(newRoot->getEntry(0)->getKey(),
                    entry->getKey()) < 0) {
                i++;
            }
            newRoot->getChild(i)->insertNonFull(entryTmp);
            this->root = newRoot;
        } else {
            this->root->insertNonFull(entryTmp);
        }
    }
}

template<class K, class V>
const V * BTree<K, V>::get(const K &key) {
    Entry<K, V>* entry = const_cast<Entry<K, V>*> (this->root->search(key));
    if (entry == NULL) {
        return NULL;
    }
    return entry->getPointValue();
}

template<class K, class V>
void BTree<K, V>::set(const K &key, const V &value) {
    if (this->root == NULL) {
        Entry<K, V>* entry = new Entry<K, V>(key, value);
        this->insert(entry);
    } else if (this->exist(key)) {
        this->root->set(key, value);
    } else {
        Entry<K, V>* entry = new Entry<K, V>(key, value);
        this->insert(entry);
    }
}

template<class K, class V>
bool BTree<K, V>::exist(const K &key) {
    return (this->root->search(key) == NULL) ? false : true;
}

template<class K, class V>
bool BTree<K, V>::remove(const K &key) {
    bool res;
    if (!this->root) {
        return false;
    }
    res = this->root->remove(key);
    if (this->root->getNCurrentEntry() == 0) {
        BTreeNode<K, V>* rootTmp = this->root;
        if (this->root->checkIsLeaf()) {
            this->root = NULL;
        } else {
            this->root = this->root->getChild(0);
        }
        delete rootTmp;
    }
    return res;
}

template<class K, class V>
const bool BTree<K, V> ::getValue(const K& key, V &value) {
    Entry<K, V>* entry = const_cast<Entry<K, V>*> (this->root->search(key));
    if (entry == NULL) {
        return false;
    }
    return true;
}


#endif /* BTREE_IMPL_H */

