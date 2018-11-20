/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BTree.h
 * Author: taipham
 *
 * Created on September 18, 2018, 2:53 PM
 */

#ifndef BTREE_H
#define BTREE_H
#include "header.h"
#include "BTreeNode.h"
#include "KeyValueStore.h"
#include "Comparetor.h"

template <class K, class V>
class BTree : public KeyValueStore<K, V> {
private:
    int t;
    BTreeNode<K, V> *root;
    Comparator<K, V>* myCompare;
public:

    BTree(int t);

    ~BTree();

    void traverse() override;

    const V * get(const K &key) override;

    const bool getValue(const K& key, V &value) override;

    void set(const K &key, const V &value) override;

    bool exist(const K &key) override;

    bool remove(const K &key) override;

private:
    void insert(const Entry<K, V>* entry);
};

#endif /* BTREE_H */

#ifndef BTREE_IMPL_H
#include "BTree_impl.h"
#endif
