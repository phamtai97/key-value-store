/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BytesStore.h
 * Author: phamtai97
 *
 * Created on October 11, 2018, 4:14 PM
 */

#ifndef BYTESSTORE_H
#define BYTESSTORE_H
#include "DataOutput.h"

class BytesDataOutputStore : public DataOutput {
private:
    char* buffer;
    int lenBuffer;
    int offsetBuffer;
    int fd;
public:
    BytesDataOutputStore(const int n, const int &fd);
    ~BytesDataOutputStore();
    void writeByte(uint8_t b) override;
    void writeBytes(const uint8_t* b, size_t offset, size_t length) override;
    void flush();
};

#endif /* BYTESSTORE_H */