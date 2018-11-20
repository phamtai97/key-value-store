/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BytesDataInputStore.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:29 PM
 */

#ifndef BYTESDATAINPUTSTORE_H
#define BYTESDATAINPUTSTORE_H

#include "DataInput.h"

class BytesDataInputStore : public DataInput {
private:
    char* buffer;
    int lenBuffer;
    int offsetBuffer;
    int fd;
    int max;
    void readBuffer();
public:
    BytesDataInputStore(int n, const int &fd);
    ~BytesDataInputStore();
    void readByte(uint8_t& b) override;
    void readBytes(uint8_t* b, size_t offset, size_t length) override;
    void resetBuffer() override;
    int getFd() override;

};

#endif /* BYTESDATAINPUTSTORE_H */

