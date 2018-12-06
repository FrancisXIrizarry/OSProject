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
#include "ProcessCB.h"
#include "hardDisk.h"

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
  int getCPUP(){
      return cpu.getProcess().get_ValID(); //return cpu.getProcess.get_validID(), change function to int
  }
  void displayReadyQ(priority_queue<pair<int,int>,vector<pair<int,int>>,CompareDist> );
  void funcSR();
  void funcSI();
  void funcSM();
  bool checkMemory(int pid, int memV){
      if(memoryList.empty()){
	  memoryObj newObj;
	  newObj.PID = pid;//When t empty memory 
	  newObj.beginMem = 0;
	  newObj.endMem = memV;
	  memoryList.push_back(newObj);
	  return true;
      }
      else{
	 for (std::list<memoryObj>::iterator it = memoryList.begin(); it != memoryList.end(); ++it){
	    if(it->beginMem - memV > 0){//50000 - 0, 30000 -> 50000[30000] - 0 -> 20000
		memoryObj newObj;
		newObj.PID = pid;//When t empty memory 
		newObj.beginMem = it->beginMem - memV;
		newObj.endMem = memV;
		memoryList.insert(it,newObj);
	    }
	    else if(memV - it->beginMem > 0){ //[40000]20000[1000] -- 30000
	      
	    }
	   // cout << it->PID << "\t" << it->beginMem << "\t" << it->endMem << endl; Ignore this for now
	  }
      }
  }
  struct memoryObj{
      int PID;
      unsigned long int beginMem;
      unsigned long int endMem;
  };
private:
  long int ramSize;
  short int hardDisks;
  priority_queue<pair<int,int>,vector<pair<int,int>>,CompareDist> readyQueue;
  vector<hardDisk> hardDrives;
  CPU cpu;
  map<int, ProcessCB> processTable;
  list<memoryObj> memoryList;
  unsigned long int memoryMax = 4000000000000; //memoryMax - memV then memoryMax + memV;
  //InputOutput hardDriveAccess;
};




#endif