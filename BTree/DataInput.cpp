/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "DataInput.h"

DataInput::DataInput() {

}

DataInput::~DataInput() {

}

void DataInput::readInt(int32_t& i) {
    readBytes(reinterpret_cast<uint8_t*> (&i), 0, sizeof (i));
}

void DataInput::readString(std::string& s) {
    int size = 0;

    readInt(size);
    s.resize(size);

    char* data = const_cast<char*> (s.data());

    readBytes(reinterpret_cast<uint8_t*> (data), 0, size);
}

void DataInput::readArrayInt(int* arri, int len) {
    readBytes(reinterpret_cast<uint8_t*> (arri), 0, len * sizeof (int));
}

