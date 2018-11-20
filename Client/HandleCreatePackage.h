/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   HandleCreatePackage.h
 * Author: taipham
 *
 * Created on October 2, 2018, 11:12 AM
 */

#ifndef HANDLECREATEPACKAGE_H
#define HANDLECREATEPACKAGE_H

class HandleCreatePackage {
    virtual const char* createPackageGet(const char* key) = 0;
    virtual const char* createPackageSet(const char* key, const char* value) = 0;
    virtual const char* createPackageExits(const char* key) = 0;
    virtual const char* createPackageRemove(const char* key) = 0;
};

#endif /* HANDLECREATEPACKAGE_H */

