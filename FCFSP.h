#ifndef FCFSP_H
#define FCFSP_H
#include "Resources/CPUScheduler.h"
#include "Resources/Process.h"
#include <iostream>
#include <vector>
using namespace std;

//First Come First Served-based pre-emptive Priority

class FCFSP : public CPUScheduler{
public:
	FCFSP(vector<Process> process):CPUScheduler(process){
		schedulerType = "First Come First Served-based pre-emptive Priority";
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
				if((*processToExecute).getPriority() > (*it)->getPriority()){
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