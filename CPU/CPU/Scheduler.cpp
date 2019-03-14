#include "Scheduler.h"
#include "AllQueueHeader.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <time.h>
#include <queue>
#include<Windows.h>
INPUT_VALUES store;

struct poolDisplay { //to display the ID
	void operator()(PCB* &a) const {
		//cout << typeid(*a).name() << endl;
		a->display();
	}
};

struct prioritySort {
	bool operator()(PCB* &a, PCB* &b) const {
		return a->getpri() < b->getpri();
	}
};

struct SJFSort {
	bool operator()(PCB* &a, PCB* &b) const {
		return a->getBT() < b->getBT();
	}
};

struct FCFSSort {
	bool operator()(PCB* &a, PCB* &b) const {
		return a->getAT() < b->getAT();
	}
};

void Scheduler::jobPoolCreation() {
	//	cout << "Entering the loop store.jobPool:" << store.jobPool << endl;
	cout << "\n\n*******Job pool initializtion started******\n";
	for (int i = 0; i < store.jobPool;) {
		i = creation(0,store.jobPool);
		//cout << "Inside job pool creationn i: " << i << endl;
	}
	cout << "\n\n********Job pool intializition is over*******\n";
	for_each(jobQueue.begin(), jobQueue.end(), poolDisplay());
}

int typeDecision() {
	//cout << "Inside typeDecision" << endl;
	int randomValue, init = 0;
	srand(time(NULL));
	randomValue = rand() % 100 + 1;
	for (int i = 0; i < store.Type.size(); i++) {

		init += store.values[i][0];
		//cout << "random value:" << randomValue << "store.valure[i][o]" << store.values[i][0] << "init:" << init << endl;
		if (randomValue <= init) {	
		//	cout << "Exiting type decision:" << i << endl;
			return i;
		}
	}
}
bool IsRecurring(int type) {
	//cout << "Inside IsRecurring" << endl;
	int randomValue;
	srand(time(NULL));
	randomValue = rand() % store.values[type][1] + 1;
	if (randomValue <= store.values[type][1]) {
		//cout << "Exiting IsRecurring true" << endl;
		return true;
	}
	//cout << "Exiting IsRecurring false" << endl;
	return false;
}
int BTDecision(int type) {
	//cout << "Inside BTDecision" << endl;
	//cout << store.values[type][4] << endl << store.values[type][3] << endl;
	//cout << (store.values[type][4] - store.values[type][3]) << endl;
	srand(time(NULL));
	return ((rand() % (store.values[type][4] - store.values[type][3])) + store.values[type][3]);
}
int priDecision() {
	//cout << "Inside priDecision" << endl;
	srand(time(NULL));
	return rand() % store.priorityLevel + 1;
}
int starvationDecision(int type) {
	//cout << "Inside starvation decision" << endl;
	//cout << store.values[type][8] << endl << store.values[type][7] << endl;
	//cout << (store.values[type][8] - store.values[type][7]) << endl;
	srand(time(NULL));	
	if ((store.values[type][8] ==0 )&& (store.values[type][7] == 0)) {
	//	cout << "\n\nreturn 0 for pri starvatio\n" << endl;
		return 0;
	}
	return ((rand() % (store.values[type][8] - store.values[type][7])) + store.values[type][7]);
}
int STDecision(int type) {
	//cout << "Inside STDecision" << endl;
	//cout << store.values[type][5] << endl << store.values[type][4] << endl;
	//cout << (store.values[type][5] - store.values[type][4]);
	srand(time(NULL));

	return ((rand() % (store.values[type][5] - store.values[type][4])) + store.values[type][4]);
}
int ATDecision(int min,int max) {
	srand(time(NULL));
	if (min == max)
		return min;
	return ((rand() % (max - min)) + min);
}
void split(string &s, int splitted[2]) {
	int comma;
	comma = s.find(",");
	splitted[0] = stoi(s.substr(1, comma - 1));
	splitted[1] = stoi(s.substr(comma + 1, s.length() - 2));
}
vector<int> pars(stringstream &ss) {
	vector<int> input; int temp, splitted[2]; string s;
	for (int i = 0; i < 3; i++) {
		ss >> temp;
		input.push_back(temp);
	}
	for (int i = 0; i<3; i++) {
		ss >> s;
		split(s, splitted);
		input.push_back(splitted[0]);
		input.push_back(splitted[1]);
	}
	return input;
}
void Scheduler::ReadTheValuesFromUser()
{
	int  location;
	string s, temp, FN;
	stringstream ss;
	vector<int> dummy;
	cout << "Enter the probability of PCB generation";
	std::cin >> store.PCB_P;
	cout << "Enter the Input File Name";
	std::cin >> FN;
	cout << "Enter the no:of priority levels";
	cin >> store.priorityLevel;
	cout << "Enter the job pool size";
	cin >> store.jobPool;
	cout << "Enter the simulation value";
	cin >> store.simulation;
	cout << "Enter the CPU count";
	cin >> store.CPUCount;
//	CPU.resize(store.CPUCount);
	ifstream fin(FN.c_str());
	getline(fin, s);
do {
	ss << s;
	s.clear();
	ss >> s;
	store.Type.push_back(s);
	dummy = pars(ss);
	store.values.push_back(dummy);
	ss.clear();
	s.clear();
	getline(fin, s);
} while (s != "*");
PCBQueues.resize(store.Type.size());
}
void Scheduler::displayInputValues() {
	//cout << "Size of Type:" << store.Type.size() << endl;
	for (int i = 0; i < store.Type.size(); i++) {
		cout << store.Type[i] << "\t";
	//	cout << "size of values:" << store.values[i].size() << endl;
		for (int j = 0; j < store.values[i].size(); j++) {
			cout << store.values[i][j] << "\t";
		}
		cout << endl;
	}
}
struct sortJobPool {
	bool operator()(PCB* &a, PCB* &b) const {
		return a->getAT() < b->getAT();
	}

};
int Scheduler::creation(int min,int max) {
	int randomValue, type, AT, BT, starvation, pri, ST;
	PCB* bp = new PCB();
	string idString;
	Sleep(1500);
	//	cout << "Running loop:i:id" << i << id << endl;
	srand(time(NULL));
	randomValue = rand() % 100 + 1;
	cout << "\nPCB creation probability:" << randomValue << endl;
	idString = "#" + to_string(id);
	//	cout << "idString:" << idString << endl;
	if (randomValue <= store.PCB_P)
	{
		id++;
		type = typeDecision();
		AT = ATDecision(min,max);
		BT = BTDecision(type);
		//	cout << "BT value is :" << BT << endl;
		if (IsRecurring(type)) {
			//		cout << "Inside Recurring if condition" << endl;
			starvation = starvationDecision(type);
			//		cout << "Starvation:" << starvation << endl;
			switch (type) {
			case 0:

				//					cout << "calling priDecision()" << endl;
				pri = priDecision();
				//				cout << "Priority:" << pri << endl;
				bp = new Priority(idString, AT, BT, pri);

				break;
			case 1:
				bp = new SJF(idString, AT, BT, starvation);
				break;
			case 2:
				bp = new FCFS(idString, AT, BT, starvation);
			}
		}
		else {
			ST = STDecision(type);
			switch (type) {
			case 0:
				//			cout << "calling priDecision()" << endl;
				pri = priDecision();
				//		cout << "Priority:" << pri << endl;
				bp = new Priority_R(idString, AT, BT, pri, ST);
				break;
			case 1:
				starvation = starvationDecision(type);
				bp = new SJF_R(idString, AT, BT, starvation, ST);
				break;
			case 2:
				starvation = starvationDecision(type);
				bp = new FCFS_R(idString, AT, BT, starvation, ST);
			}

		}
		//	cout << "Pinter type: " << typeid(*bp).name() << endl;
		//	bp->display();
		jobQueue.push_back(bp);
		//cout << "Pushed bp:" << endl;
		bp = NULL;
	}
	sort(jobQueue.begin(), jobQueue.end(), sortJobPool());
	return id;
}

/*void Scheduler::loadSJF(PCB* &object,int type,bool isRecurring) {
		PCBQueues.push_back[type](object);
}*/

void Scheduler::loadJobQueue(int i) {
	if (!jobQueue.empty()) {
		while (jobQueue.front()->getAT() <= i) {
			//cout << "Inside while loop" << endl;
			//cout << "Size of Job pool:" << jobQueue.empty() << endl;
			//cout << typeid(*jobQueue.front()).name() << endl;
			if ((string)typeid(*jobQueue.front()).name() == "class Priority") {
				PCBQueues[0].push_back(new Priority(jobQueue.front()));
				jobQueue.pop_front();
		//		cout << "1" << endl;
				sort(PCBQueues[0].begin(), PCBQueues[0].end(), prioritySort());
			//	cout << "Its priority\n";
			}
			else if ((string)typeid(*jobQueue.front()).name() == "class Priority_R") {
				//cout << "1" << endl;
				PCBQueues[0].push_back(new Priority_R(jobQueue.front()));
				//cout << "1" << endl;
				jobQueue.pop_front();
				//cout << "1" << endl;
				sort(PCBQueues[0].begin(), PCBQueues[0].end(), prioritySort());
				//cout << "Its priority recurring\n";
			}
			else if ((string)typeid(*jobQueue.front()).name() == "class SJF") {
				//cout << "1" << endl;
				PCBQueues[1].push_back(new SJF(jobQueue.front()));
				//cout << "1" << endl;
				jobQueue.pop_front();
				//cout << "1" << endl;
				sort(PCBQueues[1].begin(), PCBQueues[1].end(), SJFSort());
				//cout << "Its SJF\n";
			}
			else if ((string)typeid(*jobQueue.front()).name() == "class SJF_R") {
				//cout << "1" << endl;
				PCBQueues[1].push_back(new SJF_R(jobQueue.front()));
				//cout << "1" << endl;
				jobQueue.pop_front();
				//cout << "1" << endl;
				sort(PCBQueues[1].begin(), PCBQueues[1].end(), SJFSort());
				//cout << "Its SJF recurring\n";
			}

			else if ((string)typeid(*jobQueue.front()).name() == "class FCFS") {
				//cout << "1" << endl;
				PCBQueues[2].push_back(new FCFS(jobQueue.front()));
				//cout << "1" << endl;
				jobQueue.pop_front();
				//cout << "1" << endl;
				sort(PCBQueues[2].begin(), PCBQueues[2].end(), FCFSSort());
				//cout << "Its FCFS\n";
			}
			else if ((string)typeid(*jobQueue.front()).name() == "class FCFS_R") {
				//cout << "1" << endl;
				PCBQueues[2].push_back(new FCFS_R(jobQueue.front()));
			//	cout << "1" << endl;
				jobQueue.pop_front();
				//cout << "1" << endl;
				sort(PCBQueues[2].begin(), PCBQueues[2].end(), FCFSSort());
				//out << "Its FCFS_R\n";
			}
			if (jobQueue.empty()) {
				cout << "Job Queue is empty\n";
				break;
			}
		}
	}
	else {
		cout << "Job Queue is empty\n";
	}
}
/*void Scheduler::setCPUtoNULL() {
	//deque<PCB*>::iterator it = CPU.begin();
	cout << "CPU size:" << CPU.size() << endl;
	for (int i = 0; i < store.CPUCount; i++) {
		cout << "SET CPU NULL:" << i << endl;
		CPU.push_back(NULL);
	}
}*/
void Scheduler::startSimulation() {
	loadJobQueue(0);
	cout << "\n\n****Simulation started****" << endl;
	//setCPUtoNULL();
	//assignToCPU();
	for (clock = 1; clock <= store.simulation; clock++) {
		
		cout << "\nAT CLOCK: " << clock << endl;

		creation(clock,store.simulation);
		//promote();
		loadJobQueue(clock);
		cout << "*******Displaying PCB Queues********" << endl;
		for (int i = 0; i < PCBQueues.size(); i++) {
			cout << store.Type[i] << endl;
			for_each(PCBQueues[i].begin(), PCBQueues[i].end(), poolDisplay());
		}
		cout << "\n\n********Job pool*******\n";
		for_each(jobQueue.begin(), jobQueue.end(), poolDisplay());
	}
	cout << "\n\n****Simulation is over****" << endl;
	cout << "*******Displaying PCB Queues********" << endl;
	for (int i = 0; i < PCBQueues.size(); i++) {
		cout << store.Type[i] << endl;
		for_each(PCBQueues[i].begin(), PCBQueues[i].end(), poolDisplay());
	}
}
/*void Scheduler::assignToCPU() {
	deque<PCB*>::iterator it = CPU.begin();
	for (int i = 0; i < CPU.size(); i++) {
		cout << "For CPU:" << i << endl;
		if (CPU[i]==NULL) {
			cout << "Before fill CPU" << endl;
			fillCPU(i,it);
			++it;
			cout << "incremented\n";
		}
	}
}*/
/*void Scheduler::fillCPU(int i,deque<PCB*>::iterator it) {
	cout << "Inside Fill CPU\n";
	string s;
	if (!PCBQueues[0].empty()) {
		if ((string)typeid(*PCBQueues[0].front()).name() == "class Priority") {
			CPU.insert(it, new Priority(PCBQueues[0].front()));
			PCBQueues[0].push_back(new Priority(jobQueue.front()));
			PCBQueues.pop_front();
			//	cout << "Its priority\n";
		}
		else if ((string)typeid(*PCBQueues[0].front()).name() == "class Priority_R") {
			CPU.insert(it, new Priority_R(PCBQueues[0].front()));
			PCBQueues.pop_front();
			//cout << "Its priority recurring\n";
		}
	}
	else if (!PCBQueues[1].empty()) {
		if ((string)typeid(*PCBQueues[1].front()).name() == "class SJF") {
			CPU.insert(it, new SJF(PCBQueues[1].front()));
			PCBQueues[1].pop_front();
			//cout << "Its SJF\n";
		}
		else if ((string)typeid(*PCBQueues[1].front()).name() == "class SJF_R") {
			CPU.insert(it, new SJF_R(PCBQueues[1].front()));
			PCBQueues[1].pop_front();
			//cout << "Its SJF recurring\n";
		}
	}
	else if (!PCBQueues[2].empty()) {
		if ((string)typeid(*PCBQueues[2].front()).name() == "class FCFS") {
			CPU.insert(it, new FCFS(PCBQueues[2].front()));
			PCBQueues[2].pop_front();
			//cout << "Its FCFS\n";
		}
		else if ((string)typeid(*PCBQueues[2].front()).name() == "class FCFS_R") {
			CPU.insert(it, new FCFS_R(PCBQueues[2].front()));
			PCBQueues[2].pop_front();
		}
	}
	cout << "Exited \n";
}*/