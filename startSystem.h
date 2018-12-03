#ifndef _startSystem_h_
#define _startSystem_h_
#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <queue> 
#include <vector>
#include <limits>
#include "ProcessCB.h"
#include "hardDisk.h"
#include <map>
using namespace std;

vector<string> splitInput(string inputStr);

class CompareDist
{
public:
    bool operator()(pair<int,int> n1,pair<int,int> n2) {
        
        return n1.second < n2.second;
    }
};

class CPU{
public:
  CPU(){
  }
  void terminateP(){
       onlyProc.clear();
  }
  void terminateP(ProcessCB p){
       onlyProc.clear();
       setProcess(p);
  }
  void setProcess(ProcessCB p){
      if(emptyCPU()){
        onlyProc.push_back(p);
      }
      else{
        onlyProc.at(0) = p;
      }
  }

  ProcessCB getProcess(){
      return onlyProc.at(0);
  }
  bool emptyCPU(){
      return onlyProc.empty();
  }

private:
  vector<ProcessCB> onlyProc;
  //ProcessCB currentP;
  //bool NoProcess;
};

class startSystem{
public:
  startSystem(){
  }
  void preemptiveCheck();
  void startOS();
  void checkInput(string inputStr, priority_queue<pair<int,int>,vector<pair<int,int>>,CompareDist> & readyQ );
  void addToCPU(ProcessCB cpuP){
    cpu.setProcess(cpuP);
  }
  ProcessCB getCPUP(){
      return cpu.getProcess();
  }
  void displayReadyQ(priority_queue<pair<int,int>,vector<pair<int,int>>,CompareDist> );
  void funcSR();
  void funcSI();
  void funcSM();
private:
  long int ramSize;
  short int hardDisks;
  priority_queue<pair<int,int>,vector<pair<int,int>>,CompareDist> readyQueue;
  vector<hardDisk> hardDrives;
  CPU cpu;
  map<int, ProcessCB> processTable;
  //InputOutput hardDriveAccess;
};




#endif