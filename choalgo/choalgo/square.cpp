#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;
long long square[1000];
long long temp[1000];
long long result[1000000];

int main() {
	int n;
	int i, j, k, l;
	long long sumsquare;
	int resultnum = 0;
	ifstream fileopen;
	fileopen.open("square.inp");
	fileopen >> n;
	for (i = 0; i < n; i++) {
		fileopen >> square[i];
		temp[i] = square[i];
	}
	fileopen.close();
	sort(square, square + n);
	sort(temp, temp + n);
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			sumsquare = pow(square[i], 2) + pow(square[j], 2);
			for (k = j + 1; k < n; k++) {
				if (temp[k] == sumsquare) {
					result[resultnum] = temp[k];
					temp[k] = 0;
					resultnum++;
				}
			}
		}
	}

	sort(result, result + resultnum);

	ofstream filewrite;
	filewrite.open("square.out");
	if (resultnum == 0) {
		filewrite << 0;
	}
	else {
		for (i = 0; i < resultnum; i++) {
			filewrite << result[i] << " ";
		}
	}
	filewrite.close();
	for (i = 0; i < resultnum; i++) {
		cout << result[i] << " ";
	}
	return 0;
}