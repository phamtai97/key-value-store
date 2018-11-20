/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BytesDataOutputStore.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:27 PM
 */

#ifndef BYTESDATAOUTPUTSTORE_H
#define BYTESDATAOUTPUTSTORE_H

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

#endif /* BYTESDATAOUTPUTSTORE_H */

