/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Serialization.h
 * Author: phamtai97
 *
 * Created on October 14, 2018, 12:38 AM
 */

#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include "header.h"

template<class K, class V>
class Serialization {
public:
    virtual string serializationKey(K key) = 0;
    virtual string serializationValue(V value) = 0;
};

class StringSerialization : public Serialization<string, string> {
public:

    string serializationKey(string key) override {
        int len = key.length();
        //        char* res = new char[len + 4];
        string res;
        res.resize(len + 4);

        memcpy((char*) res.c_str(), &len, 4);
        memcpy((char*) res.c_str() + 4, key.c_str(), len);
        return res;
    }

    string serializationValue(string value) override {
        int len = value.length();
        //        char* res = new char[len + 4];
        string res;
        res.resize(len + 4);

        memcpy((char*) res.c_str(), &len, 4);
        memcpy((char*) res.c_str() + 4, value.c_str(), len);
        return res;
    }
};
#endif /* SERIALIZATION_H */

