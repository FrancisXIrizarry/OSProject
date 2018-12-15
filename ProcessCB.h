#ifndef _ProcessCB_h_
#define _ProcessCB_h_
#pragma once
#include <iostream>

using namespace std;
class ProcessCB {
    public:
        ProcessCB() {

        }
    ProcessCB(short int procID, short int priority): processID(procID), processPriority(priority) {}
    int get_ValID() const {
        return processID;
    }
    int get_Priority() const {
        return processPriority;
    }

    private:
        short int processID;
    short int processPriority;
};

#endif