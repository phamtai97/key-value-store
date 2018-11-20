//package client;
//
//import org.apache.thrift.TException;
//import org.apache.thrift.async.AsyncMethodCallback;
//import thirft.MsgSetResponse;
//import thirft.ServiceKeyValueStore;
//
//public class SetMethodCallBack implements AsyncMethodCallback<ServiceKeyValueStore.AsyncClient.putApi_call> {
//    @Override
//    public void onComplete(ServiceKeyValueStore.AsyncClient.putApi_call response) {
//        try {
//            MsgSetResponse result = response.getResult();
//
//        } catch (TException e) {
//            e.printStackTrace();
//        }
//    }
//
//    @Override
//    public void onError(Exception exception) {
//
//    }
//}
