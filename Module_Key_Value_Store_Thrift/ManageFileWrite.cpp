/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ManageFileWrite.cpp
 * Author: phamtai97
 *
 * Created on October 30, 2018, 11:16 PM
 */

#include "ManageFileWrite.h"

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

int ManageFileWrite::getPosFile(const int& fdw) const {
    return lseek(fdw, 0, SEEK_CUR);
}

void ManageFileWrite::setPosFile(const int& fdw, const int& pos) {
    lseek(fdw, pos, SEEK_SET);
}

void ManageFileWrite::setPosEndFile(const int& fdw) {
    lseek(fdw, 0, SEEK_END);
}

int ManageFileWrite::getFd(const int& index) {

}

int ManageFileWrite::getFd() {
    return this->fdFileWrite;
}
