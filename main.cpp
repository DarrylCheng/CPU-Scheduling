#include <iostream>
#include <vector>
#include "Resources/Process.h"
#include "Resources/GanttChart.h"
#include "Resources/CPUScheduler.h"
#include "FCFSP.h"
#include "RR.h"
#include "PreemptiveSJF.h"
#include "threeLevelQueue.h"
#include <fstream>
using namespace std;

void runScheduler(CPUScheduler * scheduler){
	ofstream file;
	file.open("record.txt",ios::app);
	cout << *scheduler << endl;
	file << *scheduler << endl;
	scheduler->compute();
	file.close();
	GanttChart * gc = new GanttChart(scheduler);
	gc->drawGanttChart();
	cout << endl;
}

int main(){
	ofstream file;
	file.open("record.txt");
	int numberOfProcesses, quantumTime;
	vector<Process> processes;

	cout << "Enter the number of processes (3-10)\n==> ";
	cin >> numberOfProcesses;
	if(!(numberOfProcesses >= 3 && numberOfProcesses <=10))
		return 0;
	else {
		int arrivalTime, burstTime, priority;
		cout << "Note: Priority must range from 1-6.\n";
		for(int i = 1; i<= numberOfProcesses;i++){
			cout << "\nProcess " << i << endl;
			cout << "Enter arrival time : ";
			cin >> arrivalTime; cin.sync();
			cout << "Enter burst time : ";
			cin >> burstTime; cin.sync();
			while(true){
				cout << "Enter priority : ";
				cin >> priority; cin.sync();
				if(priority >= 1 && priority <=6){ break; }
				else{ cout << "Priority must range from 1-6.\n";	}		
			}
			processes.push_back(Process(arrivalTime,burstTime,priority));
		}
		cout << "\nEnter quantum time: ";
		cin >> quantumTime;
	}

	cout << "===============================================================\n";
	file << "===============================================================\n";
	cout << " ProcessID\tArrivalTime\tBurstTime\tPriority\n";
	file << " ProcessID	" << "ArrivalTime	"<<"BurstTime	"<<"Priority\n";
	for(vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
		cout << "\t" << (*it).getProcessID()
			<< "\t\t" << (*it).getArrivalTime()
			<< "\t\t" << (*it).getBurstTime()
			<< "\t\t" << (*it).getPriority()
			<< endl;
		file << "	" << (*it).getProcessID() << "		" << (*it).getArrivalTime() << "		" << (*it).getBurstTime() << "		" << (*it).getPriority() << endl;
	}
	cout << " Quantum time = " << quantumTime;
	cout << "\n===============================================================\n\n";
	file << " Quantum time = " << quantumTime;
	file << "\n===============================================================\n\n";

	vector<CPUScheduler*> schedulers;
	schedulers.push_back(new FCFSP(processes));
	schedulers.push_back(new PreemptiveSJF(processes));
	schedulers.push_back(new RR(processes,quantumTime));
	schedulers.push_back(new threeLevelQueue(processes,quantumTime));
	file.close();
	for(int i=0;i<schedulers.size();i++){
		
		runScheduler(schedulers[i]);
		
	}
	file.open("record.txt",ios::app);
	cout << "\nStatistics:\n";
	file << "\nStatistics:\n";
	for(int i=0;i<schedulers.size();i++){
		cout << *schedulers[i] << endl;
		cout << "\tAverage Turn Around Time: " << schedulers[i]->getAvgTA() << endl;
		cout << "\tAverage Waiting Time: " << schedulers[i]->getAvgWT() << endl;
		file << *schedulers[i] << endl;
		file << "\tAverage Turn Around Time: " << schedulers[i]->getAvgTA() << endl;
		file << "\tAverage Waiting Time: " << schedulers[i]->getAvgWT() << endl;
	}
	file.close();

	return 0;
}

