/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SocketClient.cpp
 * Author: taipham
 *
 * Created on September 27, 2018, 5:53 PM
 */

#include "SocketClient.h"

SocketClient::SocketClient(int clientfd, int index) {
    this->clientfd = clientfd;
    this->index = index;
}

int SocketClient::getClienfd() const {
    return this->clientfd;
}

int SocketClient::getIndex() const {
    return this->index;
}




