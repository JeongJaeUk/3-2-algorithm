#include <vector>
#include <algorithm>
#include <fstream>
#define changeCost 10
using namespace std;
int dp[101][2];
bool cmp(vector<int> a, vector<int> b) {
	bool result = false;
	if (a[1] < b[1])
		result = true;
	else if (a[1] == b[1]) {
		if (a[0] < b[0])
			result = true;
	}
	return result;
}
int main() {
	vector<vector<int> > work; // 0-b 1-e 2-c 3-d 4-
	int N, b, e, c, db, tempC, tempT;
	ifstream fin("1.inp");
	ofstream fout("freelance.out");
	fin >> N;
	for (int i = 0; i <= N; i++) {
		vector<int> tempVec;
		if (i != 0)
			fin >> b >> e >> c;
		else
			b = -1, e = -1, c = changeCost;
		tempVec.push_back(b);
		tempVec.push_back(e);
		tempVec.push_back(c);
		work.push_back(tempVec);
	}
	sort(work.begin(), work.end(), cmp);
	for (int i = N; i > 0; i--) {
		b = work[i][0], db = i;
		work[i].push_back(work[i][1] - work[i][0] + 1);
		for (int j = i - 1; j > 0; j--) {
			if (b <= work[j][1])
				db = j;
			else break;
		}
		work[i].push_back(db);
	}
	dp[0][0] = work[0][2];
	dp[0][1] = 0;
	for (int i = 1; i <= N; i++) {
		tempC = dp[work[i][4] - 1][0] - changeCost + work[i][2];
		tempT = dp[work[i][4] - 1][1] + work[i][3];
		if (tempC < dp[i - 1][0]) {
			dp[i][0] = dp[i - 1][0];
			dp[i][1] = dp[i - 1][1];
		}
		else if (tempC == dp[i - 1][0]) {
			if (tempT < dp[i - 1][1]) {
				dp[i][0] = tempC;
				dp[i][1] = tempT;
			}
			else {
				dp[i][0] = dp[i - 1][0];
				dp[i][1] = dp[i - 1][1];
			}
		}
		else {
			dp[i][0] = tempC;
			dp[i][1] = tempT;
		}
	}
	fout << dp[N][0] << " " << dp[N][1] << "\n";
	fin.close();
	fout.close();
	return 0;
}