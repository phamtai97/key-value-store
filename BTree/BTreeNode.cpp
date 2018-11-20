///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
//#include "BTreeNode.h"
//
//template <class K, class V>
//void BTreeNode<K, V> ::traverse() {
//    int i = 0;
//    for (int i = 0; i < this->nCurrentEntry; i++) {
//        if (!this->isLeaf) {
//            this->childs[i]->traverse();
//        }
//        cout << this->entrys[i].getKey();
//    }
//    if (!this->isLeaf) {
//        this->childs[i]->traverse();
//    }
//}
//
//template <class K, class V>
//V BTreeNode<K, V>::search(K key) {
//    int i = 0;
//    while (i < this->nCurrentEntry && key > this->entrys[i].getKey()) {
//        i++;
//    }
//    if (this->entrys[i].getKey() == key) {
//        return this->entrys[i].getValue();
//    }
//    if (this->isLeaf) {
//        return NULL;
//    }
//    return this->childs[i]->search(key);
//}
//
//template<class K, class V>
//void BTreeNode<K, V>::splitChild(int index, BTreeNode<K, V>* node) {
//    //Create a new node which is going to store (t-1) keys of y
//    BTreeNode<K, V>* newNode = new BTreeNode(node->t, node->isLeaf);
//    newNode->nCurrentEntry = this->t - 1;
//    //Copy the last (t-1) keys of node to newNode
//
//    for (int i = 0; i < this->t - 1; i++) {
//        newNode->entrys[i] = node->entrys[i + t];
//    }
//    //Copy the last (t-1) child of node to newNode
//    if (!node->isLeaf) {
//        for (int i = 0; i < this->t; i++) {
//            newNode->childs[i] = node->childs[i + t];
//        }
//    }
//    // Reduce the number of keys in
//    node->nCurrentEntry = this->t - 1;
//
//    for (int i = this->nCurrentEntry; i >= index + 1; i--) {
//        this->childs[i + 1] = this->childs[i];
//    }
//    this->childs[index + 1] = newNode;
//
//    for (int i = this->nCurrentEntry - 1; i >= index; i--) {
//        this->entrys[i + 1] = this->entrys[i];
//    }
//    //go up entry middlle node
//    this->entrys[index] = node->entrys[this->t - 1];
//    this->nCurrentEntry = this->nCurrentEntry + 1;
//}
//
//template<class K, class V>
//void BTreeNode<K, V>::insertNonFull(Entry<K, V> entry) {
//    int i = this->nCurrentEntry - 1;
//    if (this->isLeaf) {
//        while (i >= 0 && this->entrys[i].getKey() > entry.getKey()) {
//            this->entrys[i + 1] = this->entrys[i];
//            i--;
//        }
//        this->entrys[i + 1] = entry;
//        this->nCurrentEntry = this->nCurrentEntry + 1;
//    } else {
//        //Find the child which is going to have the new key
//        while (i >= 0 && this->entrys[i].getKey() > entry.getKey()) {
//            i--;
//        }
//        if (this->childs[i + 1]->nCurrentEntry == 2 * this->t - 1) {
//            this->splitChild(i + 1, this->childs[i + 1]);
//            if (this->entrys[i + 1] < entry.getKey()) {
//                i++;
//            }
//        }
//        this->childs[i + 1]->insertNonFull(entry);
//    }
//}
//
//
