#pragma once
#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PCB {
protected:
	string ID; //ID of the process
	int AT, BT, WT, TT, ET;
	bool isAlive;
public:
	PCB(){}
	PCB(string s, int a, int b) {
		ID = s;
		AT = a;
		BT = b;
		isAlive = 1;
	//	cout << "Constructor of base class: PCB\n";
	}
	int getAT() {
		return AT;
	}
	int getBT() {
		return BT;
	}
	virtual int getpri() { return 0; }
	virtual void display() {
		cout << "Display of base class display\n";
	}
	
};

#endif // !CPU_H