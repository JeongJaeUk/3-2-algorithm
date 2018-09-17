#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;
int N;
int h[12], w[12], posx[12], posy[12];
int result[12], resultw[12], resultx[12], resulty[12];
int visited[12];
int resultmin, greedtemp;
int startx, starty;
int totalweight;
int task, dep, tempstartx, tempstarty, tempweight;
int greeddep, greedstartx, greedstarty, greedweight;

void obtainMin(int count) {
	task = 0;
	tempstartx = startx;
	tempstarty = starty;
	tempweight = totalweight;
	for (int i = 0; i < count; i++) {
		dep = (abs(resultx[i] - tempstartx) + abs(resulty[i] - tempstarty));
		task += (tempweight * dep);
		if (task > resultmin) {
			return;
		}
		tempweight -= resultw[i];
		tempstartx = resultx[i];
		tempstarty = resulty[i];
	}
	task += (abs(startx - tempstartx) + abs(starty - tempstarty));
	if (task > resultmin) {
		return;
	}
	resultmin = task;
}

//모든 경우의 수 구하기
void combination(int idx, int count) {
	if (idx >= count) {
		obtainMin(count);
		return;
	}
	for (int i = 0; i < count; i++) {
		if (!visited[i]) {
			result[idx] = h[i];
			resultx[idx] = posx[i];
			resulty[idx] = posy[i];
			resultw[idx] = w[i];
			visited[i] = true;
			combination(idx + 1, count);
			visited[i] = false;
		}
	}
}

int main() {
	ifstream fileopen;
	fileopen.open("drone.inp");
	fileopen >> N;
	for (int i = 0; i < N; i++) {
		fileopen >> h[i] >> w[i] >> posx[i] >> posy[i];
		totalweight += w[i];
		// 시작점(마지막지점) 따로 빼놓기
		if (h[i] == 1) {
			startx = posx[i];
			starty = posy[i];
			i--;
			N--;
		}
	}
	totalweight++;

	//upper bound
	greedstartx = startx;
	greedstarty = starty;
	greedweight = totalweight;
	for (int i = 0; i < N; i++) {
		greeddep = (abs(posx[i] - greedstartx) + abs(posy[i] - greedstarty));
		resultmin += (greedweight*greeddep);
		greedweight -= w[i];
	}

	fileopen.close();
	combination(0, N);
	ofstream filewrite;
	filewrite.open("drone.out");
	filewrite << resultmin;
	filewrite.close();

	return 0;
}