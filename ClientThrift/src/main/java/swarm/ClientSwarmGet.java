package swarm;

import client.ClientThrift;
import com.bigsonata.swarm.Cron;
import com.bigsonata.swarm.Props;
import org.apache.thrift.TException;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Random;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ClientSwarmGet extends Cron {
    private final int port;
    private final String host;
    private final String PATH = "dataset.txt";
    private ClientThrift clientThrift;
    private Lock lock, lockFile;
    private BufferedReader br;

    public ClientSwarmGet(String host, int port) {
        super(
                Props.create()
                        .setType("GET")
                        .setName("Key-value-service")
        );
        this.port = port;
        this.host = host;

        clientThrift = new ClientThrift(this.host, this.port);
        lock = new ReentrantLock();
        lockFile = new ReentrantLock();
    }

    @Override
    public void process() {
        try {
            lockFile.lock();
            String key = this.br.readLine();
            if(key == null){
                br.reset();
                key = br.readLine();
                System.out.println("End of file");
            }
            lockFile.unlock();

            long startTime = System.currentTimeMillis();
            try {
                lock.lock();
                String succeeded = this.clientThrift.get(key);
                lock.unlock();

                if (succeeded.length() >= 0) {
                    long elapsed = System.currentTimeMillis() - startTime;
                    recordSuccess(elapsed);
//                    System.out.println("key: " + succeeded);
                }
            } catch (TException e) {
                long elapsed = System.currentTimeMillis() - startTime;
                recordFailure(elapsed, e.getMessage());
                System.out.println("Exception set key-value: " + e.getMessage());
            }
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println(e.getMessage());
        }
    }

    @Override
    public Cron clone() {
        return new ClientSwarmGet(this.host, this.port);
    }

    @Override
    public void dispose() {

    }

    @Override
    public void initialize() {
        try {
            br = new BufferedReader(new FileReader(PATH));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}
