/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BytesDataInputStore.cpp
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:29 PM
 */

#include "BytesDataInputStore.h"

BytesDataInputStore::BytesDataInputStore(int n, const int &fd) {
    this->buffer = new char[n];
    this->lenBuffer = 0;
    this->offsetBuffer = 0;
    this->max = n;
    this->fd = fd;
}

BytesDataInputStore::~BytesDataInputStore() {
    if (this->buffer != NULL) {
        delete[] this->buffer;
        this->buffer = NULL;
    }
}

void BytesDataInputStore::readByte(uint8_t& b) {
    this->readBytes(&b, 0, 1);
}

void BytesDataInputStore::readBytes(uint8_t* b, size_t offset, size_t length) {
    int remain = length;
    int minByteRead;
    int remainBuffer;
    while (remain > 0) {
        remainBuffer = this->lenBuffer - this->offsetBuffer;
        minByteRead = remain > remainBuffer ? remainBuffer : remain;
        memcpy(b + offset, this->buffer + this->offsetBuffer, minByteRead);
        remain -= minByteRead;
        offset += minByteRead;
        this->offsetBuffer += minByteRead;
        if (this->offsetBuffer == this->lenBuffer) {
            this->readBuffer();
        }
    }
}

void BytesDataInputStore::readBuffer() {
    this->lenBuffer = ::read(fd, this->buffer, max);
    this->offsetBuffer = 0;
}

void BytesDataInputStore::resetBuffer() {
    this->lenBuffer = 0;
    this->offsetBuffer = 0;
}

int BytesDataInputStore::getFd() {
    return this->fd;
}

