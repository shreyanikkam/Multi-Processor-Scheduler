#pragma once
#ifndef SJF_H
#define SJF_H
#include "NonRecurring.h"

class SJF :public NonRecurring {
private:
	int starvation, currentStarvation;
public:
	SJF(string s, int a, int b, int c) :NonRecurring(s, a, b) {
		cout << "Creating NonRecurring SJF PCB\n";
		currentStarvation = 0;
		starvation = c;
		this->display();
	}
	SJF(PCB* &obj) {
		SJF* s = dynamic_cast<SJF*>(obj);
		ID = s->ID;
		AT = s->AT;
		BT = s->AT;
		starvation = s->starvation;
	}
	virtual void display() {
		cout << "ID:" << ID << "\tAT:" << AT << "\tBT:" << BT << "\tstarvation:" << starvation << endl;
	}
	void Starved() {}
};
#endif