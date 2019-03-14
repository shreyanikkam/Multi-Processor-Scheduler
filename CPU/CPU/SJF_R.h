#pragma once
#ifndef SJF_R_H
#define SJF_R_H
#include "Recurring.h"
class SJF_R :public Recurring {
protected:
	int starvation, currentStarvation;
public:
	SJF_R(string s, int a, int b, int c, int d) :Recurring(s, a, b, c) {
		currentStarvation = 0;
		cout << "Creating Recurring SJF\n";
		starvation = d;
		this->display();
	}
	SJF_R(PCB* &obj) {
		SJF_R* s = dynamic_cast<SJF_R*>(obj);
		ID = s->ID;
		AT = s->AT;
		BT = s->AT;
		starvation = s->starvation;
		ST = s->ST;
	}
	virtual void display() {
		cout << "ID:" << ID << "\tAT:" << AT << "\tBT:" << BT << "\tSleepTime:" << ST << "\tstarvation:" << starvation << endl;
	}
	void Starved() {}
};
#endif SJF_R_H