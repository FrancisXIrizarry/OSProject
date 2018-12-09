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
  bool isDigit( char c ) 
  {
   return ( '0' <= c && c <= '9' );
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
      else if(memoryList.size() == 1){

	  int endCheck = (memoryMax-memoryList.front().endMem);
	  int frontCheck = memoryList.front().beginMem;
	  endCheck >= memV ? 1 : endCheck = -1;
	  frontCheck >= memV ? 1 : frontCheck = -1;
	  if(endCheck >= frontCheck && frontCheck != -1){ 
	    memoryObj newObj;
	    newObj.PID = pid;//When t empty memory 
	    newObj.beginMem = 0;
	    newObj.endMem = memV;
	    memoryList.push_front(newObj);
	  }
	  else if(frontCheck > endCheck && endCheck != -1){
	      memoryObj newObj;
	      newObj.PID = pid;//When t empty memory 
	      newObj.beginMem = memoryList.front().endMem;
	      newObj.endMem = newObj.beginMem + memV;
	      memoryList.push_front(newObj);
	  }
	  else{
	    return false;
	  }
	  return true;
      }
      else{
	 int bestCurV = 0;
	 memoryObj copyOfObj;
	 for (std::list<memoryObj>::iterator it = memoryList.begin(); it != memoryList.end(); ++it){
	    /*f(copy1 == nullptr){
	        
		if(it->beginMem == 0){
		  list<memoryObj>::iterator copy = ++it;
		    int endV = it->endMem;
		    if(copy != nullptr){
		      if(endV + memV <= copy->beginMem){
			 copyOfObj = copy;
			 bestCurV = copy->beginMem - endV;
		      }
		      else{
			 if(endV + memV <= memoryMax){
			   memoryObj newObj;
			   newObj.PID = pid;//When t empty memory 
			   newObj.beginMem = memoryList.front().endMem;
			   newObj.endMem = newObj.beginMem + memV;
			   memoryList.push_front(newObj);
			 }
		      }
		    }
		}
		else{
		   list<memoryObj>::iterator copy = ++it;
		   int currPrevV = 0;
		   int currNextV = 0;
		  if(it->beginMem - memV >= 0){
		      currPrevV = it->beginMem;
		  }
		  if(it->endMem + memV <= copy->endMem){
		      currNextV = copy->endMem - it->endMem;//check values between
		  }
		  int tempBest;
		  currPrevV <= currNextV ? tempBest = currPrevV : tempBest = currNextV;
		    
		}

	    }
	    else{
	      
	    }*/
	    
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

    /*int endCheck = (memoryMax-memoryList.it.endMem);
	    int frontCheck = memoryList.it
	    .beginMem;
	    if(it->beginMem - memV > 0){//50000 - 0, 30000 -> 50000[30000] - 0 -> 20000
		
	    }
	    else if(memV - it->beginMem > 0){ //[40000]20000[1000] -- 30000
	      
	    }
	   // cout << it->PID << "\t" << it->beginMem << "\t" << it->endMem << endl; Ignore this for now*/


#endif