#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_H
#include "Process.h"
#include <iostream>
#include <vector>
using namespace std; 

class CPUScheduler{
protected:
	vector<Process> processes;
	int executionTimeNeeded;
	int * processTimeline; 
	string schedulerType;
	double averageTurnAroundTime;
	double averageWaitingTime;
public:
	CPUScheduler(vector<Process> process):processes(process){
		schedulerType = "";
		executionTimeNeeded = 0;
		for(vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
			executionTimeNeeded += (*it).getBurstTime();
		}
		processTimeline = new int[executionTimeNeeded];
		arrivalTimeCorrecter(); //At least one process must start at 0.
	}

	void computeAverageTAandWT(){
		double totalTA = 0, totalWT = 0;
		for(vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
			totalTA += (*it).getTurnAroundTime();
			totalWT += (*it).getWaitingTime();
		}
		averageTurnAroundTime = totalTA/processes.size();
		averageWaitingTime = totalWT/processes.size();
	}

	void arrivalTimeCorrecter(){
		bool arrivalStartsAtZero = false;
		while(!arrivalStartsAtZero){
			for(vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
				if((*it).getArrivalTime() == 0){
					arrivalStartsAtZero = true;
				}
			}
			if(!arrivalStartsAtZero){
				for(vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
					(*it).setArrivalTime((*it).getArrivalTime()-1);
				}
			}
		}
	}

	bool removeFinishedProcesses(vector<Process*>& queue){
		bool processRemoved = false;
		for(vector<Process*>::iterator it = queue.begin(); it != queue.end(); ){
			if((*it)->getTimesExecuted() == (*it)->getBurstTime()){
				it = queue.erase(it);
				processRemoved = true;
			} else {
				++it;
			}
		}
		return processRemoved;
	}


	friend ostream& operator<<(ostream&os, CPUScheduler& scheduler){ return os<<scheduler.schedulerType; }
	virtual void compute() = 0;
	int getTimeElapsed(){ return executionTimeNeeded; }
	double getAvgTA(){ return averageTurnAroundTime; }
	double getAvgWT(){ return averageWaitingTime; }
	int* getProcessTimeline(){ return processTimeline; }
	vector<Process> getProcess(){ return processes; }
};

#endif