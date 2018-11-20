/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BytesDataOutputStore.cpp
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:27 PM
 */

#include "BytesDataOutputStore.h"

BytesDataOutputStore::BytesDataOutputStore(int n, const int &fd) {
    this->buffer = new char[n];
    this->lenBuffer = n;
    this->offsetBuffer = 0;
    this->fd = fd;

}

BytesDataOutputStore::~BytesDataOutputStore() {
    this->flush();

    if (this->buffer != NULL) {
        delete[] this->buffer;
        this->buffer = NULL;
    }
}

void BytesDataOutputStore::writeByte(uint8_t b) {
    this->writeBytes(&b, 0, 1);
}

void BytesDataOutputStore::writeBytes(const uint8_t* b, size_t offset, size_t length) {
    int remain = length;
    int minByteWrite;
    int remainBuffer;
    while (remain > 0) {
        remainBuffer = this->lenBuffer - this->offsetBuffer;
        minByteWrite = remain > remainBuffer ? remainBuffer : remain;

        memcpy(this->buffer + this->offsetBuffer, b + offset, minByteWrite);

        remain -= minByteWrite;
        this->offsetBuffer += minByteWrite;
        offset += minByteWrite;

        if (this->offsetBuffer == this->lenBuffer) {
            this->flush();
        }
    }
}

void BytesDataOutputStore::flush() {
    if (offsetBuffer != 0) {
        int b = write(fd, this->buffer, this->offsetBuffer);
    }
    this->offsetBuffer = 0;
}

