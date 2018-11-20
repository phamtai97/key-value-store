/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Printer.h
 * Author: phamtai97
 *
 * Created on October 26, 2018, 1:33 PM
 */

#ifndef PRINTER_H
#define PRINTER_H
#include "header.h"
#include "Server.h"

class Server;

class Printer {
private:
    Server* server;
public:
    Printer(Server* server);
    virtual ~Printer();
    void operator()();

};

#endif /* PRINTER_H */

