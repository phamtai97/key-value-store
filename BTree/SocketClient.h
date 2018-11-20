/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SocketClient.h
 * Author: taipham
 *
 * Created on September 27, 2018, 5:53 PM
 */

#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

class SocketClient {
private:
    int clientfd;
    int index;
public:
    SocketClient(int clientfd, int index);
    int getClienfd() const;
    int getIndex() const;
};

#endif /* SOCKETCLIENT_H */

