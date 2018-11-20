/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ManageFileRead.cpp
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:13 PM
 */



#include "ManageFileRead.h"

ManageFileRead::ManageFileRead() {
    //    this->fdFileRead = -1;

}

ManageFileRead::~ManageFileRead() {
    //    int flag = close(this->fdFileRead);
    //    if (flag < 0) {
    //        cout << "close file error" << endl;
    //    }
    int flag;
    for (int i = 0; i < this->listFdFileRead.size(); ++i) {
        flag = close(this->listFdFileRead[i]);
        if (flag < 0) {
            cout << "close file: " << this->listFdFileRead[i] << " error" << endl;
        }
    }
}

int ManageFileRead::openFile(const string& path) {
    int fdr;
    //    fdw = open(path.c_str(), O_WRONLY | O_CREAT, 0644);
    for (int i = 0; i <= NWORKER; ++i) {
        fdr = open(path.c_str(), O_RDONLY);
        if (fdr == -1) {
            cout << "Open file error" << endl;
            return -1;
        }
        this->listFdFileRead.push_back(fdr);
    }

    //    if (fdr > 0) {
    //        this->fdFileRead = fdr;
    //    }

    return listFdFileRead[0];
}

int ManageFileRead::closeFile() const {
    int flag;
    for (int i = 0; i < this->listFdFileRead.size(); ++i) {
        flag = close(this->listFdFileRead[i]);
        if (flag < 0) {
            cout << "close file: " << this->listFdFileRead[i] << " error" << endl;
        }
    }
}

bool ManageFileRead::isEmptyFile() {
    struct stat sb;
    fstat(this->listFdFileRead[0], &sb);
    return (sb.st_size == 0) ? true : false;
}

int ManageFileRead::getPosFile(const int& fdr) const {
    return lseek(fdr, 0, SEEK_CUR);
}

void ManageFileRead::setPosFile(const int& fdr, const int& pos) {
    lseek(fdr, pos, SEEK_SET);
}

void ManageFileRead::setPosEndFile(const int& fdr) {
    lseek(fdr, 0, SEEK_END);
}

int ManageFileRead::getFd(const int& index) {
    return this->listFdFileRead[index];
}

int ManageFileRead::getFd() {

}
