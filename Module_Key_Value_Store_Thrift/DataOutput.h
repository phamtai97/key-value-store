/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DataOutput.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:21 PM
 */

#ifndef DATAOUTPUT_H
#define DATAOUTPUT_H

#include "header.h"

class DataOutput {
public:
    DataOutput();
    virtual ~DataOutput();
    virtual void writeByte(uint8_t b) = 0;
    virtual void writeBytes(const uint8_t* b, size_t offset, size_t length) = 0;

public:
    void writeString(const string& s);
    void writeInt(int32_t i);
    void writeArrayInt(const int* arr, int len);
    virtual void flush();
};

#endif /* DATAOUTPUT_H */

