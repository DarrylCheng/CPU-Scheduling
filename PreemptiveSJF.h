#ifndef PREEMPTIVE_SJF_H
#define PREEMPTIVE_SJF_H
#include "Resources/CPUScheduler.h"
#include "Resources/Process.h"
#include <iostream>
#include <vector>
using namespace std;

class PreemptiveSJF : public CPUScheduler{
public:
	PreemptiveSJF(vector<Process> process):CPUScheduler(process){
		schedulerType = "Preemptive Shortest Job First";
	}

	void compute(){
		int timeline = 0;
		vector<Process*> queue;
		Process * processToExecute;
		while(timeline < executionTimeNeeded){
			for(vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
				if(timeline == (*it).getArrivalTime()){
					queue.push_back(&(*it));
				}
			}

			removeFinishedProcesses(queue);

			processToExecute = queue[0];
			for(vector<Process*>::iterator it = queue.begin(); it != queue.end(); it++){
				if((*processToExecute).getBurstTime() > (*it)->getBurstTime()){
					processToExecute = (*it);
				}
			}
			(*processToExecute).executeProcess();
			(*processToExecute).setTimeEnded(timeline+1);
			processTimeline[timeline] = (*processToExecute).getProcessID();
			timeline++;
		}
		computeAverageTAandWT();
		
	}
};

#endif