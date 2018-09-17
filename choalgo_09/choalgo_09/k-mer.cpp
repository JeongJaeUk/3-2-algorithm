#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <cstring>

using namespace std;
int N;
map <string, int> table;
char temp;
string rd, inmap, result;
char finresult[51];
int countNum, checkNum;

int main() {
	ifstream fileopen;
	fileopen.open("k-mer.inp");
	fileopen >> N;
	while (!fileopen.eof()) {
		fileopen >> temp;
		rd += temp;
	}
	fileopen.close();

	for (int i = 0; i < rd.length(); i++) {
		inmap = rd.substr(i, N);
		countNum = table[inmap];
		countNum++;
		table[inmap] = countNum;
		if (countNum > checkNum) {
			checkNum = countNum;
		}
	}

	map<string, int>::iterator Pos;
	for (Pos = table.begin(); Pos != table.end(); Pos++) {
		if (Pos->second == checkNum) {
			result = Pos->first;
			break;
		}
	}

	for (int i = 0; i < result.length(); i++) {
		finresult[i] = result[i];
	}
	
	ofstream filewrite;
	filewrite.open("k-mer.out");
	filewrite << finresult;
	filewrite.close();

	return 0;
}