/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ManageFle.h
 * Author: phamtai97
 *
 * Created on October 13, 2018, 6:24 PM
 */

#ifndef MANAGEFLE_H
#define MANAGEFLE_H
#include "header.h"
#include "ManageFile.h"

class ManageFileRead : public ManageFile {
private:
    int fdFileRead;
public:
    ManageFileRead();
    ~ManageFileRead();
    int openFile(const string& path) override;
    int closeFile() const override;

    bool isEmptyFile() override;
    int getPosFile() const override;
    void setPosEndFile() override;
    void setPosFile(const int& pos) override;
};

#endif /* MANAGEFLE_H */

