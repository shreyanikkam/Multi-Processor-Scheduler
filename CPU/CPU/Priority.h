#pragma once
#ifndef Priority_H
#define Priority_H
#include "NonRecurring.h"

class Priority :public NonRecurring {
private:
	int pri;
public:
	Priority(string s, int a, int b, int c) :NonRecurring(s, a, b) {
		cout << "Creating NonRecurring Priority PCB\n";
		pri = c;
		this->display();
	}
	Priority(PCB* &obj) {
		Priority* p = dynamic_cast<Priority*>(obj);
		ID = p->ID;
		AT = p->AT;
		BT = p->AT;
		pri = p->pri;
	}
	int getpri() {
		return pri;
	}
	virtual void display() {
		cout << "ID:" << ID << "\tAT:" << AT << "\tBT:" << BT << "\tPRI:" << pri << endl;
	}
};
#endif // !Priority_H
