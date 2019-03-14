#pragma once
#ifndef FCFS_R_H
#define FCFS_R_H
#include "Recurring.h"

class FCFS_R :public Recurring {
protected:
	int starvation, currentStarvation;
public:
	FCFS_R(string s, int a, int b, int c, int d) :Recurring(s, a, b, c) {
		cout << "Creating Recurring FCFS\n";
		currentStarvation = 0;
		starvation = d;
		this->display();
	}
	FCFS_R(PCB* &obj) {
		FCFS_R* f = dynamic_cast<FCFS_R*>(obj);
		ID = f->ID;
		AT = f->AT;
		BT = f->AT;
		starvation = f->starvation;
		ST = f->ST;
	}
	virtual void display() {
		cout << "ID:" << ID << "\tAT:" << AT << "\tBT:" << BT << "\tSleepTime:" << ST << "\tstarvation:" << starvation << endl;
	}
	void Starved() {}
};
#endif // !FCFS_R_H
