///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//#include "BTree.h"
//
//template<class K, class V>
//V BTree<K, V>::get(K key) {
//    return this->root->search(key);
//}
//
//template<class K, class V>
//void BTree<K, V>::insert(Entry<K, V> entry) {
//    if (this->root == NULL) {
//        this->root = new BTreeNode<K, V>(this->t, true);
//        this->root->addEntry(0, entry);
//        this->root->increaseNCurrentEntry();
//    } else {
//        if (this->root->getNCurrentEntry() == 2 * this->t - 1) {
//            //new node root
//            BTreeNode<K, V>* newRoot = new BTreeNode<K, V>(this->t, false);
//            newRoot->addChild(0, this->root);
//            newRoot->splitChild(0, this->root);
//            //find child have new key
//            int i = 0;
//            if (newRoot->getEntry(0).getKey() < entry.getKey()) {
//                i++;
//            }
//            newRoot->getChild(i)->insertNonFull(entry);
//            this->root = newRoot;
//        } else {
//            this->root->insertNonFull(entry);
//        }
//    }
//}
//
