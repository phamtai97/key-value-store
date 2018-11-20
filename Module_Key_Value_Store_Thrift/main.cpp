/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: phamtai97
 *
 * Created on October 29, 2018, 9:31 PM
 */


#include "Server.h"

void testPerformanceSet() {
    KeyValueStore<string, string>* bTreeStore = new BTreeStore<string, string>();

    ifstream inputfile;
    ofstream outputfile;

    inputfile.open("./dataset.txt", ios::in);
    outputfile.open("./result_set.csv", ios::out);

    string line;
    string result;

    int i = 0;
    int numberKey = 0;
    timestamp_t timeStart;
    timestamp_t timeEnd;
    double sumTime = 0.0L;

    outputfile << "T = 40" << endl;
    outputfile << "Number Of Key" << ";" << "Time Insert" << endl;

    while (getline(inputfile, line)) {
        timeStart = get_timestamp();
        //        bTreeStore->getValue(line, result);
        bTreeStore->set(line, line);
        timeEnd = get_timestamp();
        ++i;
        sumTime += (timeEnd - timeStart) / 1000000.0L;
        if (i == 100000) {
            numberKey += i;
            outputfile << numberKey << ";" << sumTime << endl;
            cout << "numberkey: " << numberKey << " key ------- time: " << sumTime << " seconds" << " timeAVG: " << sumTime / numberKey << endl;
            i = 0;
            if (numberKey == 3000000) {
                break;
            }
        }
    }
    inputfile.close();
    outputfile.close();
    delete bTreeStore;
}

void testPerformanceGet() {
    KeyValueStore<string, string>* bTreeStore = new BTreeStore<string, string>();

    ifstream inputfile;
    ofstream outputfile;

    inputfile.open("./dataset.txt", ios::in);
    outputfile.open("./result_get.csv", ios::out);

    string line;
    string result;

    int i = 0;
    int numberKey = 0;
    timestamp_t timeStart;
    timestamp_t timeEnd;
    double sumTime = 0.0L;

    outputfile << "Number Of Key" << ";" << "Time Get" << endl;

    while (getline(inputfile, line)) {
        timeStart = get_timestamp();
        bTreeStore->getValue(line, result);
        timeEnd = get_timestamp();
        ++i;
        sumTime += (timeEnd - timeStart) / 1000000.0L;
        if (i == 100000) {
            numberKey += i;
            outputfile << numberKey << ";" << sumTime << endl;
            cout << "numberkey: " << numberKey << " key ------- time: " << sumTime << " seconds" << " timeAVG: " << sumTime / numberKey << endl;
            i = 0;
            if (numberKey == 3000000) {
                break;
            }
        }
    }
    inputfile.close();
    outputfile.close();
    delete bTreeStore;
}

int main(int argc, char **argv) {

    //    Server server;
    //    server.start();
    //    server.stop();

    testPerformanceSet();

    //    testPerformanceGet();

    return 0;
}
