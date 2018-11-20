/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ManageFile.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:12 PM
 */

#ifndef MANAGEFILE_H
#define MANAGEFILE_H
#include "header.h"

class ManageFile {
public:
    virtual int openFile(const string &path) = 0;
    virtual int closeFile() const = 0;
    virtual bool isEmptyFile() = 0;

    virtual int getPosFile(const int& fd) const = 0;
    virtual void setPosFile(const int& fd, const int& pos) = 0;
    virtual void setPosEndFile(const int& fd) = 0;

    virtual int getFd(const int& index) = 0;
    virtual int getFd() = 0;
};

#endif /* MANAGEFILE_H */

