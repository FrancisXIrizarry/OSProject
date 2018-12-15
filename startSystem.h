#ifndef _startSystem_h_
#define _startSystem_h_
#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <queue> 
#include <vector>
#include <limits>
#include <map>
#include <list>
#include <assert.h>
#include "ProcessCB.h"
#include "hardDisk.h"

using namespace std;

typedef unsigned long int longInt;

vector < string > splitInput(string inputStr);

class CompareDist {
    public:
        bool operator()(pair < int, int > n1, pair < int, int > n2) {

            return n1.second < n2.second;
        }
};

class CPU {
    public:
        CPU() {}
    void terminateP() {
        onlyProc.clear();
    }
    void terminateP(ProcessCB p) {
        onlyProc.clear();
        setProcess(p);
    }
    void setProcess(ProcessCB p) {
        if (emptyCPU()) {
            onlyProc.push_back(p);
        } else {
            onlyProc.at(0) = p;
        }
    }

    ProcessCB getProcess() {
        return onlyProc.at(0);
    }
    bool emptyCPU() {
        return onlyProc.empty();
    }

    private:
        vector < ProcessCB > onlyProc;
    //ProcessCB currentP;
    //bool NoProcess;
};

class startSystem {
    public:
        startSystem() {}
    void preemptiveCheck();
    void startOS();
    void checkInput(string inputStr, priority_queue < pair < int, int > , vector < pair < int, int > > , CompareDist > & readyQ);
    void addToCPU(ProcessCB cpuP) {
        cpu.setProcess(cpuP);
    }
    int getCPUP() {
        return cpu.getProcess().get_ValID(); //return cpu.getProcess.get_validID(), change function to int
    }
    bool isDigit(char c) {
        return ('0' <= c && c <= '9');
    }
    void displayReadyQ(priority_queue < pair < int, int > , vector < pair < int, int > > , CompareDist > );
    void funcSR();
    void funcSI();
    void funcSM();
    bool removeProcessInMemory(int pid) {
        for (int loc = 0; loc < ram.size(); loc++) {
            if (ram.at(loc).PID == pid) {
                ram.erase(ram.begin() + loc);
            }
        }

    }
    bool addProcessToMemory(int pid, longInt memV) {

        if (memV > memoryMax && memV != 0) {
            cerr << "Too high/equal to 0. Cannot be in ram" << endl;
            return false;
        }

        if (ram.empty()) {
            memoryObj newObj(pid, 0, memV - 1);
            ram.push_back(newObj);
        } else {

            enum side {
                left,
                right,
                fail
            };
            longInt bMem = 0;
            longInt eMem = 0;
            int loc = 0;
            longInt currSpace = memoryMax;
            side currSide = fail;
            for (int pos = 0; pos < ram.size(); pos++) {
                memoryObj * tempObjB = NULL;
                memoryObj * tempObjE = NULL;
                //cout << "Before huh" << endl;
                int tempP = pos - 1;
                //cout << tempP << endl;
                if (tempP >= 0) {
                    tempObjB = & ram.at(tempP);
                }
                tempP += 2;
                //cout << tempP << endl;
                if (tempP < ram.size()) {
                    //cout << ram.at(pos).beginMem << " \t EEEEHH\t" <<  tempP << "\t Pos " << pos << endl;
                    //cout << ram.at(tempP).beginMem << " \t EEEEHH\t" <<  tempP << endl;
                    tempObjE = & ram.at(tempP);
                }
                //cout << "Huh" << endl;
                long long int currDis1 = -1;
                long long int currDis2 = -1;
                bool fail1 = false;
                bool fail2 = false;

                if (tempObjB == NULL) {

                    currDis1 = ram.at(pos).beginMem;

                    if (currDis1 >= memV) {
                        currDis1 = currDis1;
                    } else {
                        fail1 = true;
                    }
                    // cout << " tempObjB == NULL " << endl;
                } else {
                    if (ram.at(pos).beginMem - tempObjB -> endMem > memV) {
                        currDis1 = ram.at(pos).beginMem - tempObjB -> endMem; //pos-1
                    } else {
                        fail1 = true;
                    }
                }
                if (tempObjE == NULL) {
                    //cout << " tempObjE == NULL) " << endl;
                    currDis2 = ram.at(pos).endMem;
                    //cout << "Reeee???" << endl;
                    if (currDis2 + memV <= memoryMax) {
                        currDis2 = memoryMax - currDis2;
                    } else {
                        fail2 = true;
                    }
                } else {
                    //cout << " Not NULL " << endl;
                    // cout << (*tempObjB).beginMem << endl;
                    //cout << tempObjE->beginMem << "\t" << ram.at(pos).endMem << endl;
                    if (tempObjE -> beginMem - ram.at(pos).endMem > memV) {

                        currDis2 = tempObjE -> beginMem - ram.at(pos).endMem;
                    } else {
                        fail2 = true;
                    }
                }
                //cout << "currSpace" << currSpace << "\tfail1: " << fail1 << " \t and fail2: " << fail2 <<"\t " << currDis1 << " and \t "<< currDis2 <<  endl;
                if (fail1 == true && fail2 == true) {
                    continue;
                } else if (fail1 == true && fail2 == false) {
                    // cout << currSpace << " ---.--- " <<  currDis2 << endl;
                    if (currSpace >= currDis2) {
                        currSpace = currDis2;
                        loc = pos + 1;
                        currSide = right;
                    }
                } else if (fail1 == false && fail2 == true) {
                    //cout << " Why no 5 " << endl;
                    if (currSpace >= currDis1) {
                        currSpace = currDis1;

                        loc = pos - 1;
                        currSide = left;
                    }
                } else {
                    side tempSide = left;
                    int better;
                    currDis1 <= currDis2 ? better = currDis1, tempSide = left : better = currDis2, tempSide = right;
                    if (currSpace >= better) {
                        currSpace = better;
                        tempSide == left ? loc = pos - 1 : loc = pos + 1;
                        currSide = tempSide;
                    }
                }

            }
            //cout << "Side" << currSide << "\t currSpace " << currSpace << "\tloc :" << loc << endl; 
            if (loc == -1) {
                memoryObj newAdd(pid, 0, memV - 1);

                ram.insert(ram.begin(), newAdd);
                return true;
            } else if (currSide == right) {
                //cout << "currSide right boi " << "\t" << loc << endl;
                //if(ram.at(loc-1).endMem + memV < memoryMax){
                memoryObj newAdd(pid, ram.at(loc - 1).endMem + 1, ram.at(loc - 1).endMem + memV);
                // cout << "Nani" << endl;
                ram.insert(ram.begin() + (loc), newAdd);
                return true;

            } else if (currSide == left) {
                //cout << "currSide left boi " << "\t" << loc << endl;
                memoryObj newAdd(pid, ram.at(loc).endMem + 1, ram.at(loc).endMem + memV);
                ram.insert(ram.begin() + (loc + 1), newAdd);
                return true;
            }
            return false;
            //End else
        }

    }
    struct memoryObj {
        int PID;
        longInt beginMem;
        longInt endMem;
        memoryObj() =
            default;
        memoryObj(int ID, longInt bM, longInt eM): PID(ID), beginMem(bM), endMem(eM) {

        }
    };
    private:
        long int ramSize;
    short int hardDisks;
    priority_queue < pair < int, int > , vector < pair < int, int > > , CompareDist > readyQueue;
    vector < hardDisk > hardDrives;
    CPU cpu;
    map < int, ProcessCB > processTable;
    vector < memoryObj > ram;
    list < memoryObj > memoryList;
    unsigned long int memoryMax = 1;

};
   


#endif
