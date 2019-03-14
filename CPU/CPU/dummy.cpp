#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
void dummy() {
	int PCB_P, location, r, c, comma;
	string s, temp;
	vector<string> Type;
	vector<int> dummy;
	vector<int> PCBS;
	vector<vector<int>> values;
	ifstream fin("Input.txt");
	getline(fin, s);
	cout << "s" << s << endl;
	location = s.rfind("$");
	cout << "location" << location << endl;
	temp = s.substr(location + 1, s.length() - 1);
	cout << "Temp" << temp << endl;
	PCB_P = stoi(temp);
	cout << "PCB_P" << PCB_P << endl;
	getline(fin, s);
	cout << "Heading" << s << endl;
	getline(fin, s);
	cout << "1st do while loop" << s << endl;
	r = 0; c = 0;
	do {
		location = s.find("$");
		temp = s.substr(0, location);
		cout << "Temp" << temp << endl;
		s.erase(0, location + 1);
		Type.push_back(temp);
		cout << "Type Pushed" << endl;
			location = s.find("$");
			temp = s.substr(0, location);
			cout << "String " << s << endl;
			cout << "Temp" << temp << endl;
			PCBS.push_back(stoi(temp));
			cout << "Inside while string " << s << "lenght" << s.length() << endl;
		getline(fin, s);
	} while (s != "*");
	cout << "Size of PCBS vector" << PCBS.size() << endl;
	for (int i = 0; i < Type.size(); i++) {
		cout << Type[i] << "\t";
			cout << PCBS[i] << "\t";
		cout << endl;
	}
	getline(fin, s);
	getline(fin, s);
	do {
		for (int i = 0; i < 2; i++) {
			location = s.find("$");
			temp = s.substr(0, location);
			cout << "String " << s << endl;
			cout << "Temp" << temp << endl;
			s.erase(0, location + 1);
			dummy.push_back(stoi(temp));
		}
		for (int i = 0; i < 3; i++) {
			location = s.find("$");
			comma = s.find(",");
			temp = s.substr(1, comma - 1);
			cout << "String " << s << endl;
			cout << "Temp" << temp << endl;
			dummy.push_back(stoi(temp));
			temp = s.substr(comma + 1, location - 3);
			cout << "String " << s << endl;
			cout << "Temp" << temp << endl;
			dummy.push_back(stoi(temp));
			s.erase(0, location + 1);
			cout << "Inside while string " << s << "lenght" << s.length() << endl;
		}
		values.push_back(dummy);
		dummy.clear();
		getline(fin, s);
	} while (s != "**");
	for (int i = 0; i < 3; i++)
		cout << values[i].size() << endl;
	cout << "Size of PCBS vector" << PCBS.size() << endl;
	for (int i = 0; i < Type.size(); i++) {
		cout << Type[i] << "\t";
		for (int j = 0; j < values[i].size(); j++) {
			cout << values[i][j] << "\t";
		}
		cout << endl;
	}

	cin >> location;
}