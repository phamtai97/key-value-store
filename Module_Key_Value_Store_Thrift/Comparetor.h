/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Comparetor.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:08 PM
 */

#ifndef COMPARATOR_H
#define COMPARATOR_H
#include "header.h"

template <class K, class V>
class Comparator {
public:
    virtual int compareKey(const K& a, const K& b) = 0;
    virtual int compareValue(const V& a, const V& b) = 0;
};

class StringStringComparator : public Comparator<string, string> {
public:

    StringStringComparator() {
    }

    int compareKey(const string& a, const string& b);

    int compareValue(const string& a, const string& b);
};

class IntStringComparator : public Comparator<int, string> {
public:

    IntStringComparator() {
    }

    int compareKey(const int& a, const int& b);

    int compareValue(const string& a, const string& b);
};
#endif /* COMPARATOR_H */

