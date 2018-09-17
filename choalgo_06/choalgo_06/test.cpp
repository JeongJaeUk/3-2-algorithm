#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#define INT_MAX 2147483647

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	if (a.first < b.first || (a.first == b.first && a.second > b.second))
		return true;
	return false;
}
int main() {
	int N, T, k, c, d, resultA = 0, resultB, min = INT_MAX, min2 = INT_MAX;
	ifstream fin("1.inp");
	ofstream fout("machine.out");
	fin >> N >> T >> k;

	vector<pair<int, int> > w;
	vector<bool> isSchedule(N);
	vector<vector<pair<int, int> > > schedule(T);

	for (int i = 0; i < N; i++) {
		fin >> c >> d;
		w.push_back(make_pair(c, d - 1));
	}
	sort(w.begin(), w.end(), cmp);

	for (int i = N - 1; i >= 0; i--) {
		isSchedule[i] = false;
		for (int j = w[i].second; j >= 0; j--) {
			if (schedule[j].size() < k) {
				schedule[j].push_back(w[i]);
				resultA += w[i].first;
				isSchedule[i] = true;
				
				break;
			}
		}
	}

	for (int i = N - 1; i >= 0; i--) {
		if (isSchedule[i])
			continue;
		for (int j = w[i].second; j >= 0; j--) {
			if (schedule[j].size() == 0)
				continue;
			if (schedule[j].back().first - w[i].first != 0 && min > schedule[j].back().first - w[i].first)
				min = schedule[j].back().first - w[i].first;
		}
	}

	if (min == INT_MAX) {
		for (int i = 0; i < T; i++) {
			if (schedule[i].size() == 0)
				continue;
			if (min2 > schedule[i].back().first)
				min2 = schedule[i].back().first;
		}
		resultB = resultA - min2;
	}
	else
		resultB = resultA - min;

	cout << resultA << " " << resultB;
	fout << resultA << " " << resultB;

	fin.close();
	fout.close();
	return 0;
}