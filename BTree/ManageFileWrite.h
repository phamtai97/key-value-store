/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ManageFileWrite.h
 * Author: phamtai97
 *
 * Created on October 15, 2018, 12:56 PM
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
    int getPosFile() const override;
    void setPosEndFile() override;
    void setPosFile(const int& pos) override;
};

#endif /* MANAGEFILEWRITE_H */

