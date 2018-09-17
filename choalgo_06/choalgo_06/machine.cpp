#include <iostream>
#include <algorithm>
#include <fstream>
#define MAX_NUM 9999999;

using namespace std;

int N, T, k, m;
int maximal, secondmaximal, tempsecond;
int task[101];
int day[101];
int table[5][10];
int check[10];
int checkingsecond;

void sortingtask(int n) {
	int temptask;
	int tempday;
	for (int i = 0; i < n; i++) {
		if (task[n] < task[i]) {
			temptask = task[n];
			task[n] = task[i];
			task[i] = temptask;
			tempday = day[n];
			day[n] = day[i];
			day[i] = tempday;
		}
		else if (task[n] == task[i]) {
			if (day[n] > day[i]) {
				temptask = task[n];
				task[n] = task[i];
				task[i] = temptask;
				tempday = day[n];
				day[n] = day[i];
				day[i] = tempday;
			}
		}
	}
}


int main() {
	int diff = MAX_NUM;
	int diff2 = MAX_NUM;
	bool checkingelement[101];
	ifstream fileopen;
	fileopen.open("machine.inp");
	fileopen >> N >> T >> k;
	for (int i = 0; i < N; i++) {
		fileopen >> task[i] >> day[i];
		day[i]--;
		sortingtask(i);
	}
	fileopen.close();
	for (int i = N - 1; i >= 0; i--) {
		checkingelement[i] = false;
		for (int j = day[i]; j >= 0; j--) {
			if (check[j] < k) {
				table[check[j]][j] = task[i];
				check[j]++;
				maximal += task[i];
				checkingelement[i] = true;
				break;
			}
		}
	}

	for (int i = N - 1; i >= 0; i--) {
		if (checkingelement[i])
			continue;
		for (int j = day[i]; j >= 0; j--) {
			if (check[j] == 0)
				continue;
			if (table[k - 1][j] - task[i] != 0 && diff > table[k - 1][j] - task[i]) {
				diff = table[k - 1][j] - task[i];
			}
		}
	}
	
	if (diff == 9999999) {
		for (int i = 0; i < T; i++) {
			if (check[i] == 0)
				continue;
			if (diff2 > table[k - 1][i]) {
				diff2 = table[k - 1][i];
			}
		}
		secondmaximal = maximal - diff2;
	}
	else {
		secondmaximal = maximal - diff;
	}

	ofstream filewrite;
 	filewrite.open("machine.out");
	filewrite << maximal << " " << secondmaximal;
	filewrite.close();

	return 0;
}