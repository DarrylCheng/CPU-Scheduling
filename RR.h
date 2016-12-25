#ifndef RR_H
#define RR_H
#include "Resources/CPUScheduler.h"
#include "Resources/Process.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


class RR : public CPUScheduler{
	int quantumTime;
public:
	RR(vector<Process> process, int quantumTime):CPUScheduler(process),quantumTime(quantumTime){
		schedulerType = "Round Robin";
	}

	void compute(){
		int timeline = 0;
		int quantumCount = 0;
		vector<Process*> queue;
		vector<Process*> temp;
		Process * processToExecute;
		while(timeline < executionTimeNeeded){
			for(vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
				if(timeline == (*it).getArrivalTime()){
					temp.push_back(&(*it));
				}
			}
			sort(temp.begin(),temp.end(),Process::sortByPriority);
			for(int i=0;i<temp.size();i++){
				queue.push_back(temp[i]);
			}
			temp.clear();

			if(removeFinishedProcesses(queue))
				quantumCount = 0;

			if(quantumCount == quantumTime){
				Process * temp = queue[0];
				for(int i=0;i<queue.size()-1;i++){
					queue[i] = queue[i+1];
				}
				queue[queue.size()-1] = temp;
				processToExecute = queue[0];
				quantumCount = 1;
			} else {
				processToExecute = queue[0];
				quantumCount++;
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