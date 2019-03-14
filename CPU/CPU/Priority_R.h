#pragma once
#ifndef Priority_R_H
#define Priority_R_H
#include "Recurring.h"

class Priority_R :public Recurring {
protected:
	int pri;
public:
	Priority_R(string s, int a, int b, int c, int d) :Recurring(s, a, b, c) {
		cout << "Creating Rucurring Priority PCB\n";
		pri = d;
		this->display();
	}
	Priority_R(PCB* &obj) {
		Priority_R* p = dynamic_cast<Priority_R*>(obj);
		ID = p->ID;
		AT = p->AT;
		BT = p->AT;
		pri = p->pri;
		ST = p->ST;
	}
	int getpri() {
		return pri;
	}
	virtual void display() {
		cout << "ID:" << ID << "\tAT:" << AT << "\tBT:" << BT << "\tPri:" << pri << "\tSleepTime:" << ST << endl;
	}
};

#endif