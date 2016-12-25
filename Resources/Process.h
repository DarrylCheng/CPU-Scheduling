#ifndef PROCESS_H
#define PROCESS_H
#include <vector>
#include <stdio.h>
#include <iostream>
using namespace std;

class Process{
	int arrivalTime;
	int burstTime;
	int timeEnded;
	int timesExecuted; //Record how many times the process has been executed
	int processID;
	int priority;
	int turnAroundTime;
	int waitingTime;
	static int count;
public:
	Process(int arrivalTime, int burstTime)
	:arrivalTime(arrivalTime),burstTime(burstTime){
		processID = count++;
		timesExecuted = 0;
	}

	Process(int arrivalTime, int burstTime,int priority)
	:arrivalTime(arrivalTime),burstTime(burstTime),priority(priority){
		processID = count++;
		timesExecuted = 0;
	}

	void executeProcess(){ timesExecuted++; }
	int getPriority(){ return priority; }
	int getArrivalTime(){ return arrivalTime; }
	int getBurstTime(){ return burstTime; }
	int getProcessID(){ return processID; }
	int getTimesExecuted(){ return timesExecuted; }
	int getTimeEnded(){ return timeEnded; }
	int getTurnAroundTime(){ return turnAroundTime; }
	int getWaitingTime(){ return waitingTime; }
	void setArrivalTime(int arrivalTime){ this->arrivalTime = arrivalTime;}
	void setTimeEnded(int timeEnded){
		this->timeEnded = timeEnded; 
		turnAroundTime = timeEnded-arrivalTime;
		waitingTime = turnAroundTime-burstTime;
	}
	
	static bool sortByPriority(const Process* p1, const Process* p2){
		return p1->priority < p2->priority;
	}
};

int Process::count = 1;

#endif