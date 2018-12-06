#include "startSystem.h"
//Definitions here of functions that cannot exist in header. (non-class functions)
 int PID_Auto = 1;
vector<string> splitInput(string inputStr){
	vector<string> result;
	istringstream iss(inputStr);
	for(string s; iss >> s;){
	    //cout << s << endl;
	    result.push_back(s);
	}
	return result;
}

void startSystem::preemptiveCheck()
{
    if(cpu.emptyCPU()){
	cpu.setProcess(processTable.find((readyQueue.top().first))->second);
	readyQueue.pop();
    }
    else if(cpu.getProcess().get_Priority() < (readyQueue.top().second)){
        ProcessCB tempPCB = cpu.getProcess();
      	cpu.terminateP(processTable.find((readyQueue.top().first))->second);
	//processTable.erase(readyQueue.top().first);
	readyQueue.pop();
        readyQueue.push(make_pair<int, int>(tempPCB.get_ValID(), tempPCB.get_Priority()));
	processTable.insert(pair<int, ProcessCB>(tempPCB.get_ValID(), tempPCB));
    }
}



void startSystem::funcSR()
{
  if(!cpu.emptyCPU()){  
  cout << "* ID:" <<  cpu.getProcess().get_ValID() << " P:" << cpu.getProcess().get_Priority() << endl;
  displayReadyQ(readyQueue);
  }
  
}

void startSystem::funcSI()
{
  for(int loc = 0; loc < hardDrives.size(); loc++){
    cout << "HDD: " << loc << "-----\n";
    hardDrives.at(loc).getIOQ();
  }
}


void startSystem::funcSM()
{
  
}


void startSystem::startOS()
{
   cout << "How much ram memory is on the computer?" << endl;
   cin >> ramSize;
   cout << "How many hard disks does the simulated computer have? " << endl;
   cin >> hardDisks;
   for(int x = 0; x < hardDisks; x++){
      hardDisk newDisk;
      hardDrives.push_back(newDisk);
   }
   cout << endl;
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   while(true){
     string input;
     cout << "> ";
     getline(cin, input);
     if(input.empty()){ cerr << "provide good input" << endl;}
     else{
     checkInput(input, readyQueue);
     if(readyQueue.empty()){}
     else{
      preemptiveCheck(); 
      }
     }
   }
}

void startSystem::checkInput(string inputStr, priority_queue<pair<int,int>,vector<pair<int,int>>,CompareDist> & readyQ ) //fix
{
  
    if(inputStr.at(0) == 'A'){
	int priorityV;
	long int memory_size;
	vector<string> result = splitInput(inputStr);
	if(result.size() == 3){
	stringstream priV(result.at(1));
	stringstream memV(result.at(2));
	priV >> priorityV;
	memV >> memory_size;
	
	//if memory can fit, then add (todo)
	ProcessCB newProcess(PID_Auto, priorityV);
	processTable.insert(pair<int, ProcessCB>(PID_Auto, newProcess));
	readyQ.push(make_pair<int, int>(int(PID_Auto), newProcess.get_Priority()));
	if(cpu.emptyCPU()){
	    cpu.setProcess(processTable.find((readyQ.top()).first)->second);
	    //processTable.erase(readyQ.top().first); -----------------
	    readyQ.pop();

	}
	PID_Auto++;
	
	}
	else{
	    cerr << "Too little or too many paramters" << endl;
	}  
    }
    else if(inputStr.at(0) == 't'){
	//readyQ.pop();
        if(inputStr.size() != 1){
	  cerr << "Too little or too many paramters" << endl;
	}
	else if(cpu.emptyCPU()){
	    cerr << "No process to terminate from cpu " << endl;
	}
	else{
	  if(readyQ.empty()){ processTable.erase(cpu.getProcess().get_ValID()); cpu.terminateP();  cerr << "No process to terminate from ready queue, only cpu" << endl; }
	  else{
	    processTable.erase(cpu.getProcess().get_ValID());
	    cpu.terminateP(processTable.find(readyQ.top().first)->second);
	    readyQ.pop();
	  }	
	}
    }
    else if(inputStr.at(0) == 'd'){
	int hardDriveV;
	string fileName;
	vector<string> result = splitInput(inputStr);
	if(result.size() == 3){
	stringstream hardDriveVSS(result.at(1));
	stringstream fileNameSS(result.at(2));
	hardDriveVSS >> hardDriveV;
	fileNameSS >> fileName;
	if(hardDriveV < 0 || hardDriveV >= hardDrives.size()){
	  cerr << "That hard disk drive does not exist. Reissue the command with an existing HDD" << endl;
	}
	else if(readyQ.empty() && cpu.emptyCPU()){
	  cerr << "No process to add " << endl;
	}
	else{
	    hardDrives.at(hardDriveV).addProcess(cpu.getProcess(), fileName);
	    if(readyQ.empty()){
	      cpu.terminateP();
	    }
	    else{
	    cpu.terminateP(processTable.find(readyQ.top().first)->second);
	    //processTable.erase(readyQ.top().first); -------------------
	    readyQ.pop();	
	    }	
	}
	}
	else{
	    cerr << "Too little or too many paramters" << endl;
	}
    }
    else if(inputStr.at(0) == 'D'){
	int hardDriveV;
	vector<string> result = splitInput(inputStr);
	stringstream hardDriveVSS(result.at(1));
	hardDriveVSS >> hardDriveV;
	if(hardDrives.at(hardDriveV).isHDDEmpty()){
	 cerr << "No process to terminate in I/O" << endl; 
	}
	else{
	ProcessCB temp = hardDrives.at(hardDriveV).finishP();
	readyQ.push(make_pair<int, int>(temp.get_ValID(), temp.get_Priority()));
	cout << "ReadyQ em " << readyQ.empty() << " \t " << readyQ.top().first << endl;
	processTable.insert(pair<int, ProcessCB>(temp.get_ValID(), temp));	
	}
    }
    else if(inputStr.at(0) == 'H'){
      for(int x = 0; x < hardDrives.size(); x++){
	hardDrives.at(x).getIOQ();
      }
    }
    else if(inputStr.at(0) == 'S'){
      vector<string> result = splitInput(inputStr);
      if(result.at(1) == "r"){
	if(readyQ.empty() && cpu.emptyCPU()){
	    cerr << "Nothing to display, queue and cpu empty" << endl;
	}
	else{
	funcSR();
	}
      }
      else if(result.at(1) == "i"){
	funcSI();
      }
      else if(result.at(1) == "m"){
	//funcSM();
      }
    }
    else if(inputStr.at(0) == 'T'){
      map<int, ProcessCB>::iterator it;

      for ( it = processTable.begin(); it != processTable.end(); it++ )
      {
		std::cout << it->first  // string (key)
		<< ':'
		<< it->second.get_ValID() << "\t"   // string's value 
		<< it->second.get_Priority() 
		<< std::endl ;
      }
    }
    else{
	cerr << "You gave invalid input, try again " << endl;
	return;
    }
}

void startSystem::displayReadyQ(priority_queue<pair<int,int>,vector<pair<int,int>>,CompareDist> readyQCopy)
{
      while(!readyQCopy.empty()){
      //cout << readyQCopy.top().first << " Nani " << endl;
      cout << "ID:" << readyQCopy.top().first << " P:" <<  readyQCopy.top().second << endl;
      readyQCopy.pop(); //processTable.erase(key)
      }
}