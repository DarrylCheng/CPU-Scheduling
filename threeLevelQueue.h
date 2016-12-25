#ifndef THREELEVELQUEUE_H
#define THREELEVELQUEUE_H
#include "Resources/CPUScheduler.h"
#include "Resources/Process.h"
#include <iostream>
#include <vector>
using namespace std;

class threeLevelQueue : public CPUScheduler{
	int quantumTime;
public:
	threeLevelQueue(vector<Process> process, int quantumTime):CPUScheduler(process),quantumTime(quantumTime){
		schedulerType = "Three Level Queue";
	}

	void compute(){
		int timeline = 0;
		int quantumCount = 0;
		vector<Process*> queue1; //Round Robin
		vector<Process*> queue2; //First come first serve
		vector<Process*> queue3; 
		vector<Process*> temp;
		while(timeline < executionTimeNeeded){
			//Add process to respective queue
			for(int i=0;i<processes.size();i++){
				if(timeline == processes[i].getArrivalTime()){
					if(processes[i].getPriority() <= 2)
						temp.push_back(&processes[i]);
					else if (processes[i].getPriority() <= 4)
						queue2.push_back(&processes[i]);
					else if (processes[i].getPriority() <= 6)
						queue3.push_back(&processes[i]);
				}
			}

			//Sort first queue by priority (for same arrival time)
			//Not sure if this is needed
			sort(temp.begin(),temp.end(),Process::sortByPriority);
			for(int i=0;i<temp.size();i++){
				queue1.push_back(temp[i]);
			}
			temp.clear();
			
			//Remove process from queue
			if(removeFinishedProcesses(queue1))
				quantumCount = 0;
			removeFinishedProcesses(queue2);
			removeFinishedProcesses(queue3);

			//If queue2 is empty, move everything from queue3 into queue2.
			if(queue2.empty() && !queue3.empty()){
				for(int i=0;i<queue3.size();i++){
					queue2.push_back(queue3[i]);
				}
				queue3.clear();
			}

			Process * processToExecute;
			//If queue1 has process, run RR.
			if(!queue1.empty()){
				if(quantumCount == quantumTime){
					Process * temp = queue1[0];
					for(int i=0;i<queue1.size()-1;i++){
						queue1[i] = queue1[i+1];
					}
					queue1[queue1.size()-1] = temp;
					processToExecute = queue1[0];
					quantumCount = 1;
				} else {
					processToExecute = queue1[0];
					quantumCount++;
				}
			} else {
				//Else just run FCFS.
				processToExecute = queue2[0];
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