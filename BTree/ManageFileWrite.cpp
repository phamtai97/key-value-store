/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ManageFileWrite.cpp
 * Author: phamtai97
 *
 * Created on October 15, 2018, 12:56 PM
 */

#include "ManageFileWrite.h"

#include <sys/stat.h>

ManageFileWrite::ManageFileWrite() {
    this->fdFileWrite = -1;
}

ManageFileWrite::~ManageFileWrite() {
    int flag = close(this->fdFileWrite);
    if (flag < 0) {
        cout << "close file error" << endl;
    }
}

int ManageFileWrite::openFile(const string& path) {
    int fdw;
    fdw = open(path.c_str(), O_WRONLY | O_CREAT, 0644);
    if (fdw == -1) {
        cout << "Open file error" << endl;
        return -1;
    }

    if (fdw > 0) {
        this->fdFileWrite = fdw;
    }
    return fdw;
}

int ManageFileWrite::closeFile() const {
    int flag = close(this->fdFileWrite);
    if (flag < 0) {
        cout << "close file error" << endl;
    }
    flag = close(this->fdFileWrite);
    return flag;
}

bool ManageFileWrite::isEmptyFile() {
    struct stat sb;
    fstat(this->fdFileWrite, &sb);
    return (sb.st_size == 0) ? true : false;
}

int ManageFileWrite::getPosFile() const {
    return lseek(this->fdFileWrite, 0, SEEK_CUR);
}

void ManageFileWrite::setPosFile(const int& pos) {
    lseek(this->fdFileWrite, pos, SEEK_SET);
}

void ManageFileWrite::setPosEndFile() {
    lseek(this->fdFileWrite, 0, SEEK_END);
}

