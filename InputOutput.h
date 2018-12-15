#ifndef _InputOutput_h_
#define  _InputOutput_h_
#pragma once
#include <iostream>
#include <queue>

class ProcessCB;

using namespace std;

class InputOutput {
    public:
        InputOutput() {

        }
    void addProcess(ProcessCB newP) {
        InputOutput_Q.push(newP);
    }
    ProcessCB getProcess() {
        return InputOutput_Q.front();
    }
    private:
        queue < ProcessCB > InputOutput_Q;
};
#endif