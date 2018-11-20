/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ManageFileRead.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:13 PM
 */

#ifndef MANAGEFILEREAD_H
#define MANAGEFILEREAD_H

#include <atomic>
#include <vector>

#include "ManageFile.h"

class ManageFileRead : public ManageFile {
private:
    //    int fdFileRead;
    vector<int> listFdFileRead;
public:
    ManageFileRead();
    ~ManageFileRead();
    int openFile(const string& path) override;
    int closeFile() const override;

    bool isEmptyFile() override;
    int getPosFile(const int& fdr) const override;
    void setPosEndFile(const int& fdr) override;
    void setPosFile(const int& fdr, const int& pos) override;

    int getFd(const int& index) override;
    int getFd() override;


};

#endif /* MANAGEFILEREAD_H */

