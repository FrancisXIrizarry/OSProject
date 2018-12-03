#ifndef _hardDisk_h_
#define _hardDisk_h_
#pragma once
#include <iostream>
#include <queue>
#include <utility> 
using namespace std;
class ProcessCB;
class hardDisk{
public:
    hardDisk(){
	 processINHDD = false;
	 noCompetition = true;
    }
    void addProcess(ProcessCB newP, string fileN){
       if(processINHDD == false){
	  hardDriveP = newP;
	  processINHDD = true;
	  pFile = fileN;
	  noCompetition = false;
       }
       else{
	InputOutput_Q.push(make_pair(newP, fileN));
       }
       
    }
    bool isQEmpty(){
	return InputOutput_Q.empty();
    }
    bool isHDDEmpty(){
       return noCompetition;
    }
    ProcessCB getHDDP(){
	return hardDriveP;
    }
    string getFile(){
	return pFile;
    }
    void getIOQ(){
	queue<pair<ProcessCB, string>> copyOfQueue = InputOutput_Q;
	if((hardDriveP.get_ValID() == 0 && getFile() == "") || noCompetition){
	  cerr << "Nothing in hard disk drive nor in queue" << endl;
	}
	else{
	  cout << "HDP*: " << hardDriveP.get_ValID() << "\tpFile: " << getFile() << endl;
	  while(!copyOfQueue.empty()){
	    cout << "HDP: " << copyOfQueue.front().first.get_ValID() << "\tpFile: " << copyOfQueue.front().second << endl;
	    copyOfQueue.pop();
	  }
	}
    }
    void assignHDP(){
	hardDriveP = InputOutput_Q.front().first;
	pFile = InputOutput_Q.front().second;
	InputOutput_Q.pop();
	if(isQEmpty()){
	  lastP = true;
	}
	else{
	  noCompetition = false;
	}
    }
    ProcessCB finishP(){
        //cout << hardDriveP.get_ValID() << "wot" << endl;
        ProcessCB tempC = hardDriveP;
	if(!isQEmpty()){
	 assignHDP();
	 return tempC;
	}
	else if(lastP == false){
	 noCompetition = true;
	 lastP = true;
	 return tempC;
	}
	else{
	  ProcessCB nullObVj;
	  hardDriveP = nullObVj;
	  pFile = "";
	  cerr << "No processes on drive" << endl;
	  noCompetition = true;
	  processINHDD = false;
	  return tempC;
	}
	// cout << tempC.get_ValID() << "wot" << endl;
	
    }
private:
  bool noCompetition;
  string pFile;
  bool lastP = false;
  ProcessCB hardDriveP;
  bool processINHDD;
  queue<pair<ProcessCB, string>> InputOutput_Q;
};



#endif