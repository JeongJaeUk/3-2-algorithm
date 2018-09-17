#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int N;
typedef pair<double, double> point;
typedef pair<pair<int, double>, point> loc;
vector<loc> spot;
vector<loc> tempspot;
int containloc[32];
int top;
int visitedNum[32];
int visitedIDX;
int spotIDX;
int result[30];

int ccw(point a, point b, point c) {
	point atob;
	point btoc;
	double check;
	atob.first = b.first - a.first;
	atob.second = b.second - a.second;
	btoc.first = c.first - b.first;
	btoc.second = c.second - b.second;
	check = atob.first * btoc.second - atob.second * btoc.first;
	if (check < 0) {
		return 1;
	}
	else if (check == 0) {
		return 0;
	}
	else {
		return -1;
	}
}

bool settingDots(loc A, loc B) {
	int check = ccw(spot[0].second, A.second, B.second);
	if (check > 0) {
		return 1;
	}
	else if (check < 0) {
		return 0;
	}
	else if (A.first.second < B.first.second) { 
		return 1;
	}
	else {
		return 0;
	}
}

void setLean(const loc temp) {
	for (int i = 2; i < N + 2; i++) {
		spot[i].first.second = sqrt(pow(spot[i].second.first - temp.second.first, 2) + pow(spot[i].second.second - temp.second.second, 2));
	}
	sort(spot.begin() + 2, spot.end(), settingDots);
}

void checkVisited() {
	for (int i = 2; i < N + 2; i++) {
		while (top >= 2 && ccw(spot[containloc[top - 2]].second, spot[containloc[top - 1]].second, spot[i].second) < 0) {
			top--, visitedIDX--;
		}
		containloc[top++] = i;
		visitedNum[visitedIDX++] = spot[i].first.first;
	}
}

point findDot(int d) {
	for (int i = 2; i < N + 2; i++) {
		if (spot[i].first.first == d)
			return spot[i].second;
	}
	return make_pair(0, 0);
}

int main() {
	int resultnum = 0;
	double tempx, tempy;
	ifstream fin("spiral.inp");
	fin >> N;
	int tempMax = N;
	spot.resize(N + 2);
	tempspot.resize(N + 2);
	spot[0].first.first = -1;
	spot[0].second.first = 0.0;
	spot[0].second.second = 0.0;
	spot[1].first.first = 0;
	spot[1].second.first = 0.0;
	spot[1].second.second = 0.5;
	for (int i = 2; i < N + 2; i++) {
		fin >> tempx >> tempy;
		spot[i].first.first = i - 1;
		spot[i].second.first = tempy;
		spot[i].second.second = tempx;
	}
	fin.close();
	setLean(spot[1]);
	containloc[top++] = 0;
	containloc[top++] = 1;
	visitedNum[visitedIDX++] = 0;
	visitedNum[visitedIDX++] = 1;
	checkVisited();
	for (int i = 2; i < visitedIDX; i++) {
		result[resultnum++] = visitedNum[i];
	}
	point tempPoint;
	bool isFind;
	while (1) {
		if (resultnum == tempMax) {
			break;
		}
		tempspot.resize(N - top + 4);
		spotIDX = 2;
		tempPoint = findDot(result[resultnum - 2]);
		tempspot[0].first.first = result[resultnum - 2];
		tempspot[0].second.first = tempPoint.first;
		tempspot[0].second.second = tempPoint.second;

		tempPoint = findDot(result[resultnum - 1]);
		tempspot[1].first.first = result[resultnum - 1];
		tempspot[1].second.first = tempPoint.first;
		tempspot[1].second.second = tempPoint.second;

		for (int i = 2; i < N + 2; i++) {
			isFind = false;
			for (int j = 2; j < top; j++) {
				if (i == containloc[j]) {
					isFind = true;
				}
			}
			if (!isFind) {
				tempspot[spotIDX++] = spot[i];
			}
		}
		spot.swap(tempspot);
		N = N - top + 2;
		visitedIDX = 0;
		top = 0;
		containloc[top++] = 0;
		containloc[top++] = 1;
		visitedNum[visitedIDX++] = result[resultnum - 2];
		visitedNum[visitedIDX++] = result[resultnum - 1];
		setLean(spot[1]);
		checkVisited();
		for (int i = 2; i < visitedIDX; i++) {
			result[resultnum++] = visitedNum[i];
		}
	}
	ofstream fout("spiral.out");
	for (int i = 0; i < resultnum; i++) {
		fout << result[i] << " ";
	}
	fout.close();

	return 0;
}