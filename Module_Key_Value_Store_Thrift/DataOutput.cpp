/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DataOutput.cpp
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:21 PM
 */

#include "DataOutput.h"

DataOutput::DataOutput() {


}

DataOutput::~DataOutput() {

}

void DataOutput::writeInt(int32_t i) {
    writeBytes(reinterpret_cast<const uint8_t*> (&i), 0, sizeof (i));
}

void DataOutput::writeString(const std::string& s) {
    size_t size = s.length();
    writeInt(static_cast<uint32_t> (size));
    writeBytes(reinterpret_cast<const uint8_t*> (s.data()), 0, size);
}

void DataOutput::writeArrayInt(const int* arri, int len) {
    writeBytes(reinterpret_cast<const uint8_t*> (arri), 0, len * sizeof (int));
}

void DataOutput::flush() {

}
