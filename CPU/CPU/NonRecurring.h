#pragma once
#ifndef NONRECURRING_H
#define NONRECURRING_H
#include "PCB.h"

class NonRecurring :public PCB {
public:
	NonRecurring() {}
	NonRecurring(string s, int a, int b) :PCB(s, a, b) {
		//		cout << "Constructor of 2nd level class: NonRecurring\n";
	}
	void calculationOnCompletion() {}
};
#endif // !NONRECURRING_H
