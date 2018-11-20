package main;

import com.bigsonata.swarm.Locust;
import swarm.ClientSwarmGet;
import swarm.ClientSwarmRemove;
import swarm.ClientSwarmSet;
import worker.WorkerGet;
import worker.WorkerSet;

public class Benchmark {
    private Locust locust;

    public void initialize() throws Exception {
        String masterHost = "localhost";
        int masterPort = 5557;

        locust = Locust.Builder.newInstance()
                .setMasterHost(masterHost)
                .setMasterPort(masterPort)

                // Optionally set the interval (in ms) to report statistics
                // Default: 2000
                .setStatInterval(2000)

                // Optionally set a seed number to generate nodeId
                .setRandomSeed(0)

                // Optionally set the number of threads to stimulate Crons
                // Default: 8
                .setThreads(8)

                // Optionally set the number of maximum requests per second
                .setMaxRps(7000)

                .build();
        locust.register(
//                new ClientSwarmSet("127.0.0.1", 8080)
                new ClientSwarmGet("127.0.0.1", 8080)
//                new ClientSwarmRemove("127.0.0.1", 8080)
        );


    }

    void benchmark(){
        try {
            this.initialize();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    void testWorkerSet(){
        WorkerSet workerSet = new WorkerSet("worker 0");
        Thread thread = new Thread(workerSet);

//        WorkerSet workerSet1 = new WorkerSet("worker 1");
//        Thread thread1 = new Thread(workerSet1);
//
//        WorkerSet workerSet2 = new WorkerSet("worker 2");
//        Thread thread2 = new Thread(workerSet2);
//
//        WorkerSet workerSet3 = new WorkerSet("worker 3");
//        Thread thread3 = new Thread(workerSet3);
//
//        WorkerSet workerSet4 = new WorkerSet("worker 4");
//        Thread thread4 = new Thread(workerSet4);
//
//        WorkerSet workerSet5 = new WorkerSet("worker 5");
//        Thread thread5 = new Thread(workerSet5);
//
//        WorkerSet workerSet6 = new WorkerSet("worker 6");
//        Thread thread6 = new Thread(workerSet6);



        thread.start();
//        thread1.start();
//        thread2.start();
//        thread3.start();
//        thread4.start();
//        thread5.start();
//        thread6.start();
    }

    public static void main(String[] args) {
        Benchmark benchmark = new Benchmark();
        benchmark.benchmark();
//        benchmark.testWorkerSet();


    }

}
