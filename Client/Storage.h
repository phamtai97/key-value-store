/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Storage.h
 * Author: taipham
 *
 * Created on October 1, 2018, 8:17 AM
 */

#ifndef STORAGE_H
#define STORAGE_H

class Storage {
protected:
    virtual string get(string key) = 0;
    virtual void set(string key, string value) = 0;
    virtual bool exist(string key) = 0;
    virtual bool remove(string key) = 0;
};

#endif /* STORAGE_H */

