#pragma once
#ifndef Scheduler_H
#define Scheduler_H
#include "PCB.h"
#include <vector>
#include <algorithm>
#include <list>
#include <deque>
using namespace std;
class Scheduler {
private:
	int clock,id=0,jobPool=10;
protected:
	deque<PCB*> jobQueue;
	//deque<deque<PCB*>> CPU;
	deque<deque<PCB*>> PCBQueues;
public:
	void ReadTheValuesFromUser();
	void displayInputValues();
	void jobPoolCreation();
	int creation(int,int);
	void startSimulation();
	void loadJobQueue(int);
	//void setCPUtoNULL();
	//void assignToCPU();
	//void fillCPU(int, deque<PCB*>::iterator);
	//void promote();
	 //Quad processor
};
using namespace std;
struct INPUT_VALUES {
	int PCB_P, priorityLevel, jobPool, simulation,CPUCount;
	vector<string> Type;
	vector<vector<int>> values;
};

#endif // !Scheduler_H
