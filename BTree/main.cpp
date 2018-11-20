/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: taipham
 *
 * Created on September 18, 2018, 9:12 AM
 */

#include "BTree.h"
#include "Server.h"
#include "ThreadPool.h"
#include "BytesDataOutputStore.h"
#include "BytesDataInputStore.h"
#include "BTreeStore.h"
#include <sstream>
#define n 1000
using namespace std;

/*
 *
 */

void testBuildBTree(KeyValueStore<string, string>* bTree) {
    bTree->set("f", "f");
    bTree->set("s", "s");
    bTree->set("q", "q");
    bTree->set("k", "k");
    bTree->set("c", "c");
    bTree->set("l", "l");
    bTree->set("h", "h");
    bTree->set("t", "t");
    bTree->set("v", "v");
    bTree->set("w", "w");
    bTree->set("m", "y");
    bTree->set("r", "r");
    bTree->set("n", "n");
    bTree->set("p", "p");
    bTree->set("a", "a");
    bTree->set("b", "b");
    bTree->set("x", "x");
    bTree->set("y", "y");
    bTree->set("d", "d");
    bTree->set("z", "z");
    bTree->set("e", "e");
    bTree->set("g", "g");
    bTree->set("i", "i");

    cout << "Traversal of the constucted tree is " << endl;
    cout << "\n----------------" << endl;
    bTree->traverse();
    cout << "\n----------------" << endl;
}

void testRemoveKeyBTree() {
    KeyValueStore<string, string>* bTree = new BTree<string, string>(3);
    testBuildBTree(bTree);
    string key;
    key = "n";
    if (bTree->remove(key)) {
        cout << "remove success" << endl;
        cout << "\n----------------" << endl;
        bTree->traverse();
        cout << "\n----------------" << endl;
    } else {
        cout << "remove failed" << endl;
    }
}

void testGetValue() {
    KeyValueStore<string, string>* bTree = new BTree<string, string>(3);
    testBuildBTree(bTree);
    string key = "i";
    const string* res = bTree->get(key);
    cout << *res << endl;
}

void testExistKey() {
    KeyValueStore<string, string>* bTree = new BTree<string, string>(3);
    testBuildBTree(bTree);
    string key = "k";
    if (bTree->exist(key)) {
        cout << "find" << endl;
    } else {
        cout << "not find" << endl;
    }
}

void testBuildBTreeStore() {
    KeyValueStore<string, string>* bTreeStore = new BTreeStore<string, string>();

    for (int i = 0; i < n; i++) {
        bTreeStore->set(to_string(i), to_string(i));
    }
    //
    //    cout << "Traversal of the constucted tree is " << endl;
    //    cout << "\n----------------" << endl;
    //    bTreeStore->traverse();
    //    cout << "\n----------------" << endl;
    delete bTreeStore;
}

void testFunctionGet() {
    KeyValueStore<string, string>* bTreeStore = new BTreeStore<string, string>();

    string res;

    cout << "---------------Test Get Value-------------------" << endl;

    for (int i = 0; i < n; ++i) {
        if (bTreeStore->getValue(to_string(i), res)) {
            cout << res << endl;
        } else {
            cout << "no exist" << endl;
        }

    }
    cout << "---------------------------------------------" << endl;

    delete bTreeStore;
}

void testFunctionRemove() {
    KeyValueStore<string, string>* bTreeStore = new BTreeStore<string, string>();

    cout << "---------------Test Remove-------------------" << endl;

    cout << "\n----------------------------------" << endl;
    for (int i = 0; i < n; ++i) {
        bTreeStore->remove(to_string(i));
    }

    cout << "---------------------------------------------" << endl;

}

void testFunctionExist() {
    KeyValueStore<string, string>* bTreeStore = new BTreeStore<string, string>();
    cout << "---------------Test Exist-------------------" << endl;

    string key;
    string value;
    for (int i = 0; i < n; ++i) {
        key = to_string(i);
        if (bTreeStore->exist(key)) {
            cout << "Key is exist" << endl;
            value = bTreeStore->getValue("b", value);
            cout << "[value]: " << value << endl;
        } else {
            cout << "Key is not exist" << endl;
        }
    }
    cout << "---------------------------------------------" << endl;

}

void testPerformanceInsertBTree() {
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

void testPerformanceGetBTree() {
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

int main(int argc, char** argv) {
    //    testBuildBTreeStore();
    //    testFunctionGet();
    //    testFunctionRemove();
    //    testFunctionExist();

    //
    //    Server* server = new Server(8080);
    //    delete server;
    //    testPerformanceInsertBTree();

    //    testPerformanceGetBTree();
    return 0;
}
