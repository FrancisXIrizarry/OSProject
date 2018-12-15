#ifndef _hardDisk_h_
#define _hardDisk_h_
#pragma once
#include <iostream>
#include <queue>
#include <utility> 
using namespace std;
class ProcessCB;
class hardDisk {
    public:
        hardDisk() {
            processINHDD = false;
            noCompetition = true;
        }
    void addProcess(int newP, string fileN) {
        if (processINHDD == false) {
            hardDriveP = newP;
            processINHDD = true;
            pFile = fileN;
            noCompetition = false;
        } else {
            InputOutput_Q.push(make_pair(newP, fileN));
        }

    }
    bool isQEmpty() {
        return InputOutput_Q.empty();
    }
    bool isHDDEmpty() {
        return noCompetition;
    }
    int getHDDP() {
        return hardDriveP;
    }
    string getFile() {
        return pFile;
    }
    void getIOQ() {
        queue < pair < int, string > > copyOfQueue = InputOutput_Q;
        if ((getHDDP() == 0 && getFile() == "") || noCompetition) {
            cerr << "Nothing in hard disk drive nor in queue" << endl;
        } else {
            cout << "HDP*: " << hardDriveP << "\tpFile: " << getFile() << endl;
            while (!copyOfQueue.empty()) {
                cout << "HDP: " << copyOfQueue.front().first << "\tpFile: " << copyOfQueue.front().second << endl;
                copyOfQueue.pop();
            }
        }
    }
    void assignHDP() {
        hardDriveP = InputOutput_Q.front().first;
        pFile = InputOutput_Q.front().second;
        InputOutput_Q.pop();
        if (isQEmpty()) {
            lastP = true;
        } else {
            noCompetition = false;
        }
    }
    int finishP() {
        int tempC = hardDriveP;
        if (!isQEmpty()) {
            assignHDP();
            return tempC;
        } else if (lastP == false) {
            noCompetition = true;
            lastP = true;
            return tempC;
        } else {
            hardDriveP = 0;
            pFile = "";
            cerr << "No processes on drive" << endl;
            noCompetition = true;
            processINHDD = false;
            return tempC;
        }

    }
    private:
        bool noCompetition;
    string pFile;
    bool lastP = false;
    int hardDriveP; //Swap pair of ProcessCB String to int string. We only need to keep track of processID which we can call processTable
    bool processINHDD;
    queue < pair < int, string > > InputOutput_Q;
};
#endif
