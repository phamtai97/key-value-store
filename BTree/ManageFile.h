/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ManageFile.h
 * Author: phamtai97
 *
 * Created on October 15, 2018, 11:54 AM
 */

#ifndef MANAGEFILE_H
#define MANAGEFILE_H
#include "header.h"

class ManageFile {
public:
    virtual int openFile(const string &path) = 0;
    virtual int closeFile() const = 0;
    virtual bool isEmptyFile() = 0;

    virtual int getPosFile() const = 0;
    virtual void setPosFile(const int& pos) = 0;
    virtual void setPosEndFile() = 0;
};

#endif /* MANAGEFILE_H */

