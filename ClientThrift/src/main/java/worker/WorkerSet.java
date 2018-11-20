package worker;

import client.ClientThrift;
import org.apache.thrift.TException;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class WorkerSet implements Runnable {
    String nameWorker;
    final String FILENAME = "./dataset.txt";
    ClientThrift clientThrift;

    public WorkerSet(String nameWorker){
        this.nameWorker = nameWorker;
        clientThrift = new ClientThrift("127.0.0.1", 8080);
    }

    @Override
    public void run() {
        try {
            BufferedReader br = new BufferedReader(new FileReader(FILENAME));
            String key;
            int count = 0;
            int numberKey = 0;
            String res;
            long startTime = System.currentTimeMillis();
            while ((key = br.readLine()) != null){
                ++count;
                try {
                    clientThrift.set(key, key);
                } catch (TException e) {
                    e.printStackTrace();
                }
                if(count == 100000){
                    numberKey += count;
                    long elapsed = System.currentTimeMillis() - startTime;
                    System.out.println(this.nameWorker + " number key: " + numberKey + " time: " + elapsed + "miliseconds");
                    count = 0;
                }
            }
            this.clientThrift.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
