#include "PCB.h"
#include "Scheduler.h"
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
	Scheduler s;
	int location;
	s.ReadTheValuesFromUser();
	s.displayInputValues();
	s.jobPoolCreation();
	s.startSimulation();
cin >> location;

}
