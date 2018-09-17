#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
using namespace std;

int weightA, weightG, weightT, weightC;
char firstDNA[1002], secondDNA[1002];
int weighttable[1002][1002];
string result[1002][1002];
char fin[1002];

int returnweight(char a) {
	if (a == 'A') {
		return weightA;
	}
	else if (a == 'G') {
		return weightG;
	}
	else if (a == 'T') {
		return weightT;
	}
	else if (a == 'C') {
		return weightC;
	}
	else {
		return 0;
	}
}

int main() {
	ifstream fileopen;
	fileopen.open("gene.inp");
	fileopen.getline(firstDNA, sizeof(firstDNA));
	fileopen.getline(secondDNA, sizeof(secondDNA));
	fileopen >> weightA >> weightG >> weightT >> weightC;
	fileopen.close();
	for (int a = 0; a < strlen(firstDNA); a++) {
		for (int b = 0; b < strlen(secondDNA); b++) {
			int left = 0, up = 0, leftup = -1, max;
			if (a == 0) {
				if (b == 0) {
					left = 0;
				}
				else {
					left = weighttable[a][b - 1];
				}
				up = 0;
				leftup = 0;
			}
			else {
				up = weighttable[a - 1][b];
				if (b == 0) {
					left = 0;
					leftup = 0;
				}
				else {
					left = weighttable[a][b - 1];
					leftup = weighttable[a - 1][b - 1];
				}
			}
			if (up == left) {
				if (result[a + 1][b].compare(result[a][b + 1]) < 0) {
					result[a + 1][b + 1] = result[a + 1][b];
				}
				else {
					result[a + 1][b + 1] = result[a][b + 1];
				}
				max = up;
			}
			else if (up > left) {
				result[a + 1][b + 1] = result[a][b + 1];
				max = up;
			}
			else if (up < left) {
				result[a + 1][b + 1] = result[a + 1][b];
				max = left;
			}
			if (firstDNA[a] == secondDNA[b]) {
				leftup = leftup + returnweight(firstDNA[a]);
				if (leftup > max) {
					max = leftup;
					result[a + 1][b + 1] = result[a][b] + firstDNA[a];
				}
				else if (leftup == max) {
					if (result[a + 1][b + 1].compare(result[a][b] + firstDNA[a]) < 0) {
						result[a + 1][b + 1] = result[a][b];
					}
					else {
						result[a + 1][b + 1] = result[a][b] + firstDNA[a];
					}
				}
			}
			weighttable[a][b] = max;
		}
	}
	for (int i = 0; i < result[strlen(firstDNA)][strlen(secondDNA)].size(); i++) {
		fin[i] = result[strlen(firstDNA)][strlen(secondDNA)][i];
	}
	ofstream filewrite;
	filewrite.open("gene.out");
	filewrite << fin;
	filewrite.close();
	return 0;
}