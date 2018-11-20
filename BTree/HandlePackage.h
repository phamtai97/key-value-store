/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   HandlePackage.h
 * Author: taipham
 *
 * Created on October 2, 2018, 11:23 AM
 */

#ifndef HANDLEPACKAGE_H
#define HANDLEPACKAGE_H

class HandlePackage {
    virtual int handlePackageGet(const int &clientfd) = 0;
    virtual int handlePackageSet(const int &clientfd) = 0;
    virtual int handlePackageExits(const int &clientfd) = 0;
    virtual int handlePackageRemove(const int &clientfd) = 0;


};

#endif /* HANDLEPACKAGE_H */

