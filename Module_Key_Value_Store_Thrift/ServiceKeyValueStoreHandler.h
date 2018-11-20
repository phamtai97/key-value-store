/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ServiceKeyValueStoreHandler.h
 * Author: phamtai97
 *
 * Created on October 30, 2018, 2:19 PM
 */

#ifndef SERVICEKEYVALUESTOREHANDLER_H
#define SERVICEKEYVALUESTOREHANDLER_H

#include "ServiceKeyValueStore.h"
#include "header.h"
#include "KeyValueStore.h"

class ServiceKeyValueStoreHandler : virtual public ServiceKeyValueStoreIf {
private:
    KeyValueStore<string, string>* bTreeStore;
public:

    ServiceKeyValueStoreHandler();

    ServiceKeyValueStoreHandler(KeyValueStore<string, string>* bTreeStore);

    void getApi(MsgGetResponse& _return, const MsgGetRequest& msgGetRequest);

    void putApi(MsgSetResponse& _return, const MsgSetRequest& msgSetRequest);

    void removeApi(MsgRemoveResponse& _return, const MsgRemoveRequest& msgRemoveRequest);

    void existApi(MsgExistResponse& _return, const MsgExistRequest& msgExistRequest);



};


#endif /* SERVICEKEYVALUESTOREHANDLER_H */

