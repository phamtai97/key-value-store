package client;

import org.apache.thrift.TException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.transport.*;
import thirft.*;

public class ClientThrift {
    private final String host;
    private final int port;
    private final int MAXLEN = 16384000;
    private TTransport transport;
    private TProtocol protocol;
    private ServiceKeyValueStore.Client client;

    public ClientThrift(String host, int port) {
        this.host = host;
        this.port = port;

        this.transport = new TFramedTransport(new TSocket(host, port), MAXLEN);
        this.protocol = new TBinaryProtocol(transport);

        this.client = new ServiceKeyValueStore.Client(this.protocol);

        try {
            this.transport.open();

        } catch (TTransportException e) {
//            e.printStackTrace();
            System.out.println("Exception open transport: " + e.getMessage());
        }


    }

    public String get(String key) throws TException {
        MsgGetRequest msgGetRequest = new MsgGetRequest(key);
        MsgGetResponse msgGetResponse = new MsgGetResponse();

        msgGetResponse = this.client.getApi(msgGetRequest);
        if (msgGetResponse.getStatus() == 1) {
            return msgGetResponse.getValue();
        }

        System.out.println("Key: " + key + " doesn't Exist");
        return null;
    }

    public boolean set(String key, String value) throws TException {
        MsgSetRequest msgSetRequest = new MsgSetRequest(key, value);
        MsgSetResponse msgSetResponse;

        msgSetResponse = this.client.putApi(msgSetRequest);
        if (msgSetResponse.status == 1) {
            return true;
        }
        return false;
    }

    public boolean remove(String key) throws TException {
        MsgRemoveRequest msgRemoveRequest = new MsgRemoveRequest(key);
        MsgRemoveResponse msgRemoveResponse;
        msgRemoveResponse = this.client.removeApi(msgRemoveRequest);
        if (msgRemoveResponse.result) {
            return true;
        }
        return false;
    }

    public boolean exist(String key) {
        MsgExistRequest msgExistRequest = new MsgExistRequest(key);
        MsgExistResponse msgExistResponse;

        try {
            msgExistResponse = this.client.existApi(msgExistRequest);
            if (msgExistResponse.result) {
                return true;
            }
        } catch (TException e) {
            e.printStackTrace();
        }
        return false;
    }

    public void close() {
        this.transport.close();
    }

    public boolean isOpen() {
        return this.transport.isOpen();
    }

    public void connectServer() {
        try {
            this.transport.open();
        } catch (TTransportException e) {
            e.printStackTrace();
        }
    }
}