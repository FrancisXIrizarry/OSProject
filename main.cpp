/*******************************************************************************
  Title          : main.cpp
  Author         : Francis Irizarry
  Created on     : Dec 1, 2018
  Description    : Linker file, (Point access for other files, pulls the input of command line
  Purpose        : Handling nodes and keeping together similar to a linked list
  Usage          : Include this file with client code
  Build with     : make clean, make, ./DatabaseExe
  Modifications  : 
 
*******************************************************************************/
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue> 
#include <vector>
#include <limits>
#include "startSystem.h"
using namespace std;




int main(int argc, char* argv[]){
  startSystem newSystem;
  newSystem.startOS();
}








 //bool endOfFile = false;
   /*while(!fin.eof()){
      string inputStr;
      getline(fin, inputStr);
      if(fin.bad()  || fin.eof()){cout << "break" << endl; endOfFile = true;}
      else{
	istringstream inFileSS(inputStr);
	getline(inFileSS, inputStr, ',');
	string processName = inputStr;
	string priority;
	getline(inFileSS, priority, ',');
	stringstream intCopy(priority);
	int realPriority;
	intCopy >> realPriority;
	string memory;
	getline(inFileSS, memory, ',');
	stringstream intMemCopy(memory);
	int realMemory;
	intMemCopy >> realMemory;
	//if(inputStr.empty()) continue;
	ProcessCB newProcess(inputStr, realPriority);
	readyQueue.push(newProcess);
      }
   }?*/











//cout << "hello" << endl;
  //ifstream fin;
  /*if(argc > 2){
      cerr << "Too much input" << endl;
  }
  else if(argc < 2){
      cerr << "Not enough input" << endl;
  }
  else{
      fin.open(argv[1], ios::in);
      if ( !fin ) {
	cerr << "Could not open " << argv[1] << " for reading.\n";
	exit(1);
      }   
      startSystem(fin);
  }*/
