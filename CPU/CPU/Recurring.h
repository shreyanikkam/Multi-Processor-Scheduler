#pragma once
#ifndef  RECURRING_H
#define RECURRING_H
#include "PCB.h"

class Recurring :public PCB {
protected:
	int ST;
	vector<int> info[5]; //To store the AT,BT,WT,ET,TT for each recurring
public:
	Recurring() {}
	Recurring(string s, int a, int b, int c) :PCB(s, a, b) {
		//	cout << "Constructor of 2nd level class: Recurring\n";
		ST = c;

	}
	void calculationOnCompletion() {}
};

#endif // ! RECURRING_H