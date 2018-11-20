/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Comparetor.h"

int StringStringComparator::compareKey(const string& a, const string& b) {
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}

int StringStringComparator::compareValue(const string& a, const string& b) {
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}

int IntStringComparator::compareKey(const int& a, const int& b) {
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}

int IntStringComparator::compareValue(const string& a, const string& b) {
    return a.compare(b);
}
