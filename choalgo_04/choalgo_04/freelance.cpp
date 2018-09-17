#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int start[101];
int finish[101];
int tempfinishtable[101];
int cost[101];
int day[101];
int checktable[101];
int table[101][2];

/*
bool checkoverlap(int beg, int fin, int n) {
	if (table[n][beg] == 1 || table[n][fin] == 1) {
		return true;
	}
	else {
		return false;
	}
}
*/
/*
void insert(int n) {
	for (int i = 0; i < n; i++) {
		//°ãÄ¥ ¶§
		if (checkoverlap(start[i], finish[i], i - 1) == true) {
			for (int j = start[i]; j <= finish[i]; j++) {
				table[i][j] = 1;
			}
			numofwork++;
			totalday[i] = (finish[i] - start[i] + 1);
			totalprice[i] = cost[i];
			for (int k = 0; k < i; k++) {
				if (checkoverlap(start[k], finish[k], i) == true) {

				}
				else {
					numofwork++;
					if (max(totalprice[k], totalprice[i]) == totalprice[k]) {
						totalprice[i] = max(totalprice[k], totalprice[i]);
						totalday[i] = totalday[k];
						for (int l = 0; l < 365; l++) {
							table[i][l] = table[i][l] + table[k][l];
						}
					}
				}
			}
			if (totalprice[i] < totalprice[i - 1]) {
				totalday[i] = totalday[i - 1];
				totalprice[i] = totalprice[i - 1];
				for (int m = 0; m < 365; m++) {
					table[i][m] = table[i - 1][m];
				}
			}
		}
		//°ãÄ¡Áö ¾ÊÀ»¶§´Â ±×³É ³ÖÀ½
		else {
			for (int j = 0; j < 365; j++) {

			}
			for (int j = start[i]; j <= finish[i]; j++) {
				table[i][j] = 1;
			}
			if (i == 0) {
				totalday[i] = (finish[i] - start[i] + 1);
				totalprice[i] = cost[i];
			}
			else {
				totalday[i] = totalday[i - 1] + (finish[i] - start[i] + 1);
				totalprice[i] = totalprice[i - 1] + cost[i];
				totalprice[i] = totalprice[i] - 10;
			}
		}
	}
}
*/
void sortinginput(int n) {
	int tempstart;
	int tempfinish;
	int tempcost;
	int tempday;
	for (int i = 0; i < n; i++) {
		if (finish[n] < finish[i]) {
			tempstart = start[n];
			start[n] = start[i];
			start[i] = tempstart;
			tempfinish = finish[n];
			finish[n] = finish[i];
			finish[i] = tempfinish;
			tempcost = cost[n];
			cost[n] = cost[i];
			cost[i] = tempcost;
			tempday = day[n];
			day[n] = day[i];
			day[i] = tempday;
		}
		else if (finish[n] == finish[i]) {
			if (start[n] < start[i]) {
				tempstart = start[n];
				start[n] = start[i];
				start[i] = tempstart;
				tempfinish = finish[n];
				finish[n] = finish[i];
				finish[i] = tempfinish;
				tempcost = cost[n];
				cost[n] = cost[i];
				cost[i] = tempcost;
				tempday = day[n];
				day[n] = day[i];
				day[i] = tempday;
			}
		}
	}
}

void makechecktable(int count) {
	int check;
	int dpcheck;
	for (int i = count; i > 0; i--) {
		check = start[i];
		dpcheck = i;
		for (int j = i - 1; j > 0; j--) {
			if (check <= finish[j])
				dpcheck = j;
			else break;
		}
		checktable[i] = dpcheck;
	}
}

int main() {
	int count;
	int resultcost;
	int resultday;
	ifstream fileopen;
	fileopen.open("freelance.inp");
	fileopen >> count;
	start[0] = -1;
	finish[0] = -1;
	cost[0] = 10;
	for (int i = 1; i <= count; i++) {
		fileopen >> start[i] >> finish[i] >> cost[i];
		tempfinishtable[i] = finish[i];
		day[i] = finish[i] - start[i] + 1;
		sortinginput(i);
	}
	fileopen.close();
	makechecktable(count);
	table[0][0] = 10;
	table[0][1] = 0;
	for (int i = 1; i <= count; i++) {
		resultcost = table[checktable[i] - 1][0] - 10 + cost[i];
		resultday = table[checktable[i] - 1][1] + day[i];
		if (resultcost < table[i - 1][0]) {
			table[i][0] = table[i - 1][0];
			table[i][1] = table[i - 1][1];
		}
		else if (resultcost == table[i - 1][0]) {
			if (resultday < table[i - 1][1]) {
				table[i][0] = resultcost;
				table[i][1] = resultday;
			}
			else {
				table[i][0] = table[i - 1][0];
				table[i][1] = table[i - 1][1];
			}
		}
		else {
			table[i][0] = resultcost;
			table[i][1] = resultday;
		}
	}
	ofstream filewrite;
	filewrite.open("freelance.out");
	filewrite << table[count][0]<< " " << table[count][1] << "\n";
	filewrite.close();
	return 0;
}