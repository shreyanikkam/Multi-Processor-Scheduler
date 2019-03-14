#pragma once
#ifndef FCFS_H
#define FCFS_H
#include "NonRecurring.h"
class FCFS :public NonRecurring {
private:
	int starvation, currentStarvation;
public:
	FCFS(string s, int a, int b, int c) :NonRecurring(s, a, b) {
		cout << "Creating NonRecurring FCFS PCB\n";
		currentStarvation = 0;
		starvation = c;
		this->display();
	}
	FCFS(PCB* &obj) {
		FCFS* f = dynamic_cast<FCFS*>(obj);
		ID = f->ID;
		AT = f->AT;
		BT = f->AT;
		starvation = f->starvation;
	}
	virtual void display() {
		cout << "ID:" << ID << "\tAT:" << AT << "\tBT:" << BT << "\tstarvation:" << starvation << endl;
	}
	void Starved() {}
};

#endif FCFS_H// 
