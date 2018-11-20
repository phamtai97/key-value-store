/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   KeyValueStore.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:03 PM
 */

#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

template <class K, class V>
class KeyValueStore {
public:
    virtual const V * get(const K &key) = 0;
    virtual void set(const K &key, const V& value) = 0;
    virtual bool exist(const K &key) = 0;
    virtual bool remove(const K &key) = 0;
    virtual void traverse() = 0;
    virtual const bool getValue(const K& key, V& value) = 0;

    virtual ~KeyValueStore() {

    }
};


#endif /* KEYVALUESTORE_H */

