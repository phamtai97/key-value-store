/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <sys/stat.h>

#include "ManageFileRead.h"

ManageFileRead::ManageFileRead() {
    this->fdFileRead = -1;
}

ManageFileRead::~ManageFileRead() {
    int flag = close(this->fdFileRead);
    if (flag < 0) {
        cout << "close file error" << endl;
    }
}

int ManageFileRead::openFile(const string& path) {
    int fdr;
    //    fdw = open(path.c_str(), O_WRONLY | O_CREAT, 0644);
    fdr = open(path.c_str(), O_RDONLY);
    if (fdr == -1) {
        cout << "Open file error" << endl;
        return -1;
    }

    if (fdr > 0) {
        this->fdFileRead = fdr;
    }
    return fdr;
}

int ManageFileRead::closeFile() const {
    int flag = close(this->fdFileRead);
    if (flag < 0) {
        cout << "close file error" << endl;
    }
    flag = close(this->fdFileRead);
    return flag;
}

bool ManageFileRead::isEmptyFile() {
    struct stat sb;
    fstat(this->fdFileRead, &sb);
    return (sb.st_size == 0) ? true : false;
}

int ManageFileRead::getPosFile() const {
    return lseek(this->fdFileRead, 0, SEEK_CUR);
}

void ManageFileRead::setPosFile(const int& pos) {
    lseek(this->fdFileRead, pos, SEEK_SET);
}

void ManageFileRead::setPosEndFile() {
    lseek(this->fdFileRead, 0, SEEK_END);
}
