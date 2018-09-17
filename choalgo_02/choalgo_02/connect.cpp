#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
float Xx, Xy, Xz;
float Yx, Yy, Yz;
float Px, Py, Pz;

int distance(float Ax, float Ay, float Az, float Bx, float By, float Bz) {
	float ux, uy, uz;
	float PAx, PAy, PAz;
	float tempx, tempy, tempz;
	float result;
	ux = Bx - Ax;
	uy = By - Ay;
	uz = Bz - Az;
	PAx = Px - Ax;
	PAy = Py - Ay;
	PAz = Pz - Az;
	tempx = uy * PAz - uz * PAy;
	tempy = uz * PAx - ux * PAz;
	tempz = ux * PAy - uy * PAx;
	result = sqrt(pow(tempx, 2) + pow(tempy, 2) + pow(tempz, 2)) / sqrt(pow(ux, 2) + pow(uy, 2) + pow(uz, 2));
	return ceil(result);
}

int main() {
	int last;
	ifstream fin("connect.inp");
	fin >> Xx >> Xy >> Xz;
	fin >> Yx >> Yy >> Yz;
	fin >> Px >> Py >> Pz;
	fin.close();
	last = distance(Xx, Xy, Xz, Yx, Yy, Yz);
	ofstream fout("connect.out");
	fout << last;
	fout.close();
	return 0;
}