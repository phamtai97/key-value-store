/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Printer.cpp
 * Author: phamtai97
 *
 * Created on October 26, 2018, 1:33 PM
 */

#include "Printer.h"

Printer::Printer(Server* server) {
    this->server = server;
}

Printer::~Printer() {
}

void Printer::operator()() {
    while (true) {
        sleep(2);
        cout << "------------------- Time Handle -------------------------" << endl;
        cout << "time API get: " << this->server->sumTimeHandleGet << " microsecond" << endl;
        cout << "time API set: " << this->server->sumTimeHandleSet << " microsecond" << endl;
        cout << "time API exist: " << this->server->sumTimeHandleExist << " microsecond" << endl;
        cout << "time API remove: " << this->server->sumTimeHandleRemove << " microsecond" << endl;
        cout << "---------------------------------------------------------" << endl;
    }
}
