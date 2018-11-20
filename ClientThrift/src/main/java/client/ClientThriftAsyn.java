//package client;
//
//import org.apache.thrift.TException;
//import org.apache.thrift.async.TAsyncClientManager;
//import org.apache.thrift.protocol.TBinaryProtocol;
//import org.apache.thrift.protocol.TProtocol;
//import org.apache.thrift.transport.*;
//import thirft.*;
//
//import java.io.IOException;
//
//public class ClientThriftAsyn {
//    private final String host;
//    private final int port;
//    private final int MAXLEN = 16384000;
//    private TTransport transport;
//    private TProtocol protocol;
//    private ServiceKeyValueStore.AsyncClient client;
//
//    public ClientThriftAsyn(String host, int port) {
//        this.host = host;
//        this.port = port;
//        try {
//            this.client = new ServiceKeyValueStore.AsyncClient(
//                    new TBinaryProtocol.Factory(),
//                    new TAsyncClientManager(),
//                    new TNonblockingSocket("localhost", 8080));
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//
//
//        try {
//            this.transport.open();
//
//        } catch (TTransportException e) {
////            e.printStackTrace();
//            System.out.println("Exception open transport: " + e.getMessage());
//        }
//
//
//    }
//
////    public String get(String key) {
////        MsgGetRequest msgGetRequest = new MsgGetRequest(key);
////        MsgGetResponse msgGetResponse = new MsgGetResponse();
////
////        try {
////            msgGetResponse = this.client.getApi(msgGetRequest);
////            if (msgGetResponse.getStatus() == 1) {
////                return msgGetResponse.getValue();
////            }
////        } catch (TException e) {
////            e.printStackTrace();
////        }
////
////        System.out.println("Key doesn't Exist");
////        return null;
////    }
//
//    public boolean set(String key, String value) throws TException {
//        MsgSetRequest msgSetRequest = new MsgSetRequest(key, value);
//        MsgSetResponse msgSetResponse;
//
//        msgSetResponse = this.client.putApi(msgSetRequest, new SetMethodCallBack());
//        if (msgSetResponse.status == 1) {
//            return true;
//        }
//        return false;
//    }
//
////    public boolean remove(String key){
////        MsgRemoveRequest msgRemoveRequest = new MsgRemoveRequest(key);
////        MsgRemoveResponse msgRemoveResponse;
////        try {
////            msgRemoveResponse = this.client.removeApi(msgRemoveRequest);
////            if(msgRemoveResponse.result){
////                return true;
////            }
////        } catch (TException e) {
////            e.printStackTrace();
////        }
////        return false;
////    }
////
////    public boolean exist(String key){
////        MsgExistRequest msgExistRequest = new MsgExistRequest(key);
////        MsgExistResponse msgExistResponse;
////
////        try {
////            msgExistResponse = this.client.existApi(msgExistRequest);
////            if(msgExistResponse.result){
////                return true;
////            }
////        } catch (TException e) {
////            e.printStackTrace();
////        }
////        return false;
////    }
//
//    public void close(){
//        this.transport.close();
//    }
//
//    public boolean isOpen(){
//        return this.transport.isOpen();
//    }
//
//    public void connectServer(){
//        try {
//            this.transport.open();
//        } catch (TTransportException e) {
//            e.printStackTrace();
//        }
//    }
//}