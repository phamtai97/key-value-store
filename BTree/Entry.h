/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Entry.h
 * Author: taipham
 *
 * Created on September 18, 2018, 2:51 PM
 */

#ifndef ENTRY_H
#define ENTRY_H
#include "header.h"

template <class K, class V>
class Entry {
private:
    K* key;
    V* value;
public:

    Entry() {
        this->key = new K();
        this->value = new V();
    }

    Entry(const K &key, const V &value) {
        this->key = new K();
        this->value = new V();
        *(this->key) = key;
        *(this->value) = value;
    }

    Entry(const Entry<K, V>* entry) {
        this->key = new K();
        this->value = new V();
        *(this->key) = entry->getKey();
        *(this->value) = entry->getValue();
    }

    ~Entry() {
        if (this->key != NULL) {
            delete this->key;
            this->key = NULL;
        }
        if (this->value != NULL) {
            delete this->value;
            this->value = NULL;
        }
    }

    void setEntry(const Entry<K, V>* &entry) {
        *(this->key) = entry->getKey();
        *(this->value) = entry->getValue();
    }

    const Entry<K, V>* editEntry(const K &key, const V &value) {
        *(this->key) = key;
        *(this->value) = value;
        return this;
    }

    void setKeyValue(const K &key, const V &value) {
        *(this->key) = key;
        *(this->value) = value;
    }

    K getKey() const {
        return *(this->key);
    }

    void setKey(const K &key) {
        *(this->key) = key;
    }

    V getValue() const {
        return *(this->value);
    }

    const V* getPointValue() {
        return this->value;
    }

    void setValue(const V &value) {
        *(this->value) = value;
    }
};


#endif /* ENTRY_H */

