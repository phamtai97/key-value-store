/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DataInput.h
 * Author: phamtai97
 *
 * Created on October 11, 2018, 3:56 PM
 */

#ifndef DATAINPUT_H
#define DATAINPUT_H
#include "header.h"

class DataInput {
public:
    DataInput();
    virtual ~DataInput();
    virtual void readByte(uint8_t& b) = 0;
    virtual void readBytes(uint8_t* b, size_t offset, size_t length) = 0;
    virtual void resetBuffer() = 0;
public:
    void readString(string& s);
    void readInt(int32_t& i);
    void readArrayInt(int* arri, int len);
};
#endif /* DATAINPUT_H */

