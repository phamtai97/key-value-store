/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ManageFileWrite.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:16 PM
 */

#ifndef MANAGEFILEWRITE_H
#define MANAGEFILEWRITE_H

#include "ManageFile.h"

class ManageFileWrite : public ManageFile {
private:
    int fdFileWrite;
public:
    ManageFileWrite();
    ~ManageFileWrite();
    int openFile(const string& path) override;
    int closeFile() const override;

    bool isEmptyFile() override;
    int getPosFile(const int& fdw) const override;
    void setPosEndFile(const int& fdw) override;
    void setPosFile(const int& fdw, const int& pos) override;

    int getFd(const int& index) override;
    int getFd() override;

};


#endif /* MANAGEFILEWRITE_H */

