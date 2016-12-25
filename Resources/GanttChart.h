#ifndef GANTTCHART_H
#define GANTTCHART_H
#include "CPUScheduler.h"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

class GanttChart{
	vector<Process> processes;
	int* processTimeline;
	int timeElapsed;
	double averageTA, averageWT;
public:
	GanttChart(CPUScheduler * scheduler){
		processTimeline = scheduler->getProcessTimeline();
		processes = scheduler->getProcess();
		timeElapsed = scheduler->getTimeElapsed();
		averageTA = scheduler->getAvgTA();
		averageWT = scheduler->getAvgWT();
	}

	void drawGanttChart(){
		ofstream file;
		file.open ("record.txt",ios::app);
		double totalTA = 0, totalWT = 0;
		cout << " ProcessID\tTurnAroundTime\tWaitingTime\n";
		file << " ProcessID\t" << "TurnAroundTime\t" << "WaitingTime\n";
		for(vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
			cout << "\t" << (*it).getProcessID()
				<< "\t\t" << (*it).getTurnAroundTime() 
				<< "\t\t" << (*it).getWaitingTime() << endl;
			file << "\t" << (*it).getProcessID()
				<< "\t\t" << (*it).getTurnAroundTime() 
				<< "\t\t" << (*it).getWaitingTime() << endl;
			totalTA += (*it).getTurnAroundTime();
			totalWT += (*it).getWaitingTime();
		}

		cout << "\nGantt Chart: \n   ";
		file << "\nGantt Chart: \n   ";


		//Calculating stuffs for gantt chart
		vector<int> spaces;
		vector<int> processID;
		int num;
		if(timeElapsed>0){
			num = processTimeline[0];
		}
		for(int i=0;i<timeElapsed;i++){
			if(num != processTimeline[i]){
				spaces.push_back(i);
				processID.push_back(processTimeline[i-1]);
				num = processTimeline[i];
			}
		}
		spaces.push_back(timeElapsed);
		processID.push_back(processTimeline[timeElapsed-1]);

		//Displaying the Gantt Chart
		for(int i=0;i<spaces.size();i++){
			cout << setfill('-') << setw(spaces[i]) << "-";
			file << setfill('-') << setw(spaces[i]) << "-";
		}
		for(int i=0;i<processID.size()-1;i++){
			cout << "-";
			file<< "-";
		}
		cout << setfill(' ') << endl << "   ";
		file << setfill(' ') << endl << "   ";
		for(int i=0;i<processID.size();i++){
			cout << "|" << setw(spaces[i]/2) << processID[i] << setw(spaces[i]/2) <<" " << setw(0);
			file<< "|" << setw(spaces[i]/2) << processID[i] << setw(spaces[i]/2) <<" " << setw(0);
		}
		cout << "|\n   ";
		file << "|\n   ";
		for(int i=0;i<spaces.size();i++){
			cout << setfill('-') << setw(spaces[i]) << "-";
			file << setfill('-') << setw(spaces[i]) << "-";
		}
		for(int i=0;i<processID.size()-1;i++){
			cout << "-";
			file << "-";
		}
		cout << setfill(' ') << endl;
		file << setfill(' ') << endl;

		cout << "   0 ";
		file << "   0 ";
		for(int i=0;i<spaces.size();i++){
			int size = spaces[i];
			if(size>10){
				if(size%2 == 0){
					cout << " ";
					file << " ";
				}
			}
			cout << setw(size) << spaces[i] << setw(0);
			file << setw(size) << spaces[i] << setw(0);

		}



		cout << endl << endl;
		cout.precision(3);
		cout << "Average Turn Around Time : " << averageTA << endl;
		cout << "Average Waiting Time : " << averageWT << endl;
		cout << endl;
		file << endl << endl;
		file.precision(3);
		file << "Average Turn Around Time : " << averageTA << endl;
		file << "Average Waiting Time : " << averageWT << endl;
		file << endl;
		file.close();
	}
};

#endif