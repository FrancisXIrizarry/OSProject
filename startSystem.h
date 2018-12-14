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


typedef unsigned long int longInt;


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
  bool isDigit( char c ) 
  {
   return ( '0' <= c && c <= '9' );
  }
  void displayReadyQ(priority_queue<pair<int,int>,vector<pair<int,int>>,CompareDist> );
  void funcSR();
  void funcSI();
  void funcSM();
  bool addProcessToMemory(int pid, longInt memV){
     if(memV > memoryMax && memV != 0){
        cerr << "Too high/equal to 0. Cannot be in ram" << endl;
	return false;
     }
     
     if(ram.empty()){
       memoryObj newObj(pid, 0, memV-1);
       ram.push_back(newObj);
     }
     else{
     
     
     enum side { left, right};
     longInt bMem = 0;
     longInt eMem = 0;
     int loc = 0;
     longInt currSpace = 0;
     longInt permSpace = 0;
     side currSide = left;
     for(int pos = 0; pos <= ram.size(); pos++){
        memoryObj *tempObjB = nullptr;
	memoryObj *tempObjE = nullptr;
	try{
	    tempObjB = &ram.at(pos-1);
	} catch (std::out_of_range& err) {
	  // oh dear god
	}
	try{
	    tempObjE = &ram.at(pos+1);
	} catch (std::out_of_range& err) {
	  // oh dear god
	}
	longInt currDis1 = 0;
	longInt currDis2 = 0;
	bool fail1 = false;
	bool fail2 = false;
	if(tempObjB == nullptr){
	  currDis1 = ram.at(pos).beginMem;
	  if(currDis1 >= memV){
	      currDis1 = currDis1;
	  }
	  else{
	      fail1 = true;
	  }
	}
	else{
	    if(ram.at(pos).beginMem - tempObjB->endMem >= memV){
	        currDis1 = ram.at(pos).beginMem - tempObjB->endMem; //pos-1
	    }
	    else{
	      fail1 = true;
	    }
	}
	if(tempObjE == nullptr){
	  currDis2 = ram.at(pos).endMem;
	  if(currDis2 + memV <= memoryMax){
	      currDis2 = memoryMax-currDis2;
	  }
	  else{
	      fail2 = true;
	  }
	}
	else{
	    if(tempObjB->beginMem - ram.at(pos).endMem >= memV){
	        currDis2 = tempObjB->beginMem - ram.at(pos).endMem;
	    }
	    else{
	      fail2 = true;
	    }
	}
	if(fail1 == true && fail2 == true){
	    continue;
	}
	else if(fail1 == true && fail2 == false){
	    if(currSpace >= currDis2){
	      currSpace = currDis2; 
	      loc = pos;
	      currSide = right;
	    }
	}
	else if(fail1 = false && fail2 == true){
	   if(currSpace >= currDis1){
	      currSpace = currDis1;
	      loc = pos;
	      currSide = left;
	   }
	}
	else{
	   side tempSide = left;
	   int better;
	   currDis1 <= currDis2 ? better = currDis1,tempSide = left: better = currDis2,tempSide = right;
	   if(currSpace >= better){
	      currSpace = better;
	      loc = pos;
	      currSide = tempSide;
	   } 
	}
	
	
	
	
	
	
      }
      //End else
     }
     
  }
  struct memoryObj{
      int PID;
      longInt beginMem;
      longInt endMem;
      memoryObj() = default;
      memoryObj(int ID, longInt bM, longInt eM) : PID(ID), beginMem(bM), endMem(eM){
	
      }
  };
private:
  long int ramSize;
  short int hardDisks;
  priority_queue<pair<int,int>,vector<pair<int,int>>,CompareDist> readyQueue;
  vector<hardDisk> hardDrives;
  CPU cpu;
  map<int, ProcessCB> processTable;
  vector<memoryObj> ram;
  list<memoryObj> memoryList;
  unsigned long int memoryMax = 4000000000; //memoryMax - memV then memoryMax + memV;
  //InputOutput hardDriveAccess;
};

    /*int endCheck = (memoryMax-memoryList.it.endMem);
	    int frontCheck = memoryList.it
	    .beginMem;
	    if(it->beginMem - memV > 0){//50000 - 0, 30000 -> 50000[30000] - 0 -> 20000
		
	    }
	    else if(memV - it->beginMem > 0){ //[40000]20000[1000] -- 30000
	      
	    }
	   // cout << it->PID << "\t" << it->beginMem << "\t" << it->endMem << endl; Ignore this for now*/


#endif