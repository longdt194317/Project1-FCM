#include <iostream> 
#include <math.h>
#include <vector>
#include <fstream>
using namespace std;
void allocate(float**& array, int row, int col) {
	array = new float* [row];
	for (int i = 0; i < row; i++)
		array[i] = new float[col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			array[i][j] = 0;
}
void free(float**& array, int row, int col) {
	for (int i = 0; i < row; i++)
		delete[] array[i];
	delete array;
}
void read(float**& X, int row, int col) {
	ifstream file("C:\\Users\\abc\\Downloads\\iris.data");
	for(int i =1 ; i<=row; i++){
		for(int j=1;j<=col;j++){
			file >> X[i][j];
			char trash;
			file >> trash;
		}
		string trashstr;
		file >> trashstr;
	}
}
float D(float**& X, float**& C, int i, int k, int d) {
	float length = 0;
	for (int j = 1; j <= d; j++) {
		length += pow(X[i][j] - C[k][j], 2);
	}
	length = pow(length, (float)1 / 2);
	return length;
}
float update_JUC(float**& U, float**& X, float**& C, int n, int c, int d, int m) {
	float JUC = 0;
	for (int i = 1; i <= n; i++) {
		float series1 = 0;
		for (int k = 1; k <= c; k++) {
			series1 += pow(U[i][k], m) * D(X, C, i, k, d);
		}
		JUC += series1;
	}
	return JUC;
}
void update_CK(float**& U, float**& X, float**& C, int d, int m, int n, int k) {
	for (int p = 1; p <= d; p++) {
		float A = 0;
		float B = 0;
		for (int i = 1; i <= n; i++) {
			A += pow(U[i][k], m) * X[i][p];
			B += pow(U[i][k], m);
		}
		C[k][p] = A / B;
	}
}
void update_UIK(float**& U, float**& X, float**& C, int d, int m, int c, int i, int k) {
	float UIK;
	float sum = 0;
	float DIK = 0;
	//tin Dik
	DIK = D(X, C, i, k, d);

	for (int j = 1; j <= c; j++)
	{
		float DIJ = 0;
		DIJ = D(X, C, i, j, d);
		float Dp = DIK / DIJ;
		Dp = pow(Dp, (float)2 / (m - 1));
		sum += Dp;
	}
	UIK = 1 / sum;
	U[i][k] = UIK;
}
float Dcluster(float**& X, float**& C, int i, int k, int d) {
	float length = 0;
	for (int j = 1; j <= d; j++) {
		length += pow(C[i][j] - C[k][j], 2);
	}
	length = pow(length, (float)1 / 2);
	return length;
}
int main() {
	// d la so chieu
	// n la so diem cua X
	// m la trong so mu
	// c la so cum
	int n, d, m, c;
	n = 150;
	d = 4;
	m = 2;
	c = 20;
	//	cout << "nhap tham so m";
	//	cin >>m;

	//	cout << "nhap so cum";
	//	cin >>c;

	// tap cac ma tran x
	float** X;
	allocate(X, n + 1, d + 1);
	read(X, n, d);

	// ma tran U
	float** U;
	allocate(U, n+1, c+1);

	// tap cac vector cum C 
	float** C;
	allocate(C, c+1, d+1);


	//khoi tao ma tran U
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= c; j++)
			U[i][j] = (float)1/(i+j);

	//khoi tao cac tam C
	for (int i = 1; i <= c; i++)
		for (int j = 1; j <= d; j++)
			C[i][j] = 1;

	// thuat toan fcm
	float JUC = 0;
	float JUCnew = 0;
	do {
		JUC = JUCnew;
		for (int k = 1; k <= c; k++)
			update_CK(U, X, C, d, m, n, k);

		for (int i = 1; i <= n; i++)
			for (int k = 1; k <= c; k++)
				update_UIK(U, X, C, d, m, c, i, k);

		JUCnew = update_JUC(U, X, C, n, c, d, m);

	} while (abs(JUC - JUCnew) > 0);

	float delta_min = 999;
	float delta_max = 0;
	float E1 = 0,EK=0,DK=0;

	//ban kinh cac tam cum(thuat toan dunn)
	float *radius;
	radius = new float[c + 1];
	for (int i = 1; i <= c; i++)
		radius[i] = 0;

	//tong khoang cach cac phan tu của cụm đến cụm đó
	float *E;
	E = new float[c + 1];
	for (int i = 1; i <= c; i++)
		E[i] = 0;
	
	//do DB
	float DB = 0;
	for (int i = 1; i <= c; i++) {
		float ps[100];
		for (int j = 2; j <= c; j++) {
			if (i = !j) {
				float tu[100];
				float mau[100];
				tu[j] = 1 / n*(E[i] + E[j]);
				mau[j]= Dcluster(X, C, i, j, d);
				
				ps[j] = tu[j] / mau[j];
			}
		}
		int max = ps[2];
		for (int j = 2; j <= c; j++) {
			if (i = !j) {
				if (max < ps[j]) {
					max = ps[j];
				}
			}
		}
		DB += max;
	}
	DB = DB / n;

	//tinh ban kinh cac tam cum
	for (int i = 1; i <= n; i++) {
		float clus = 0;
		int ter = 0;
		for (int j = 1; j <= c; j++) {
			if (U[i][j] > clus) {
				clus = U[i][j];
				ter = j;
			}
		}
		// thuat toan dunn
		float radius_ter = D(X, C, i, ter, d);
		if (radius_ter > radius[ter])
			radius[ter] = radius_ter;

		// thuat toan PBM
		E[ter] += radius_ter;
	}
	
	//tinh EK
	for (int i = 1; i <= c; i++){
		EK +=E[i];
	}
	
	//tinh E1
	E1 = E[1];

	//tim ban kinh lon nhat
	for (int i = 1; i <= c; i++) {
		if (delta_max < radius[i])
			delta_max = radius[i];
	}

	//tim khoang cach nho nhat giua 2 tam cum
	for (int i = 1; i < c; i++)
		for (int j = i + 1; j <= c; j++){
			if (delta_min > Dcluster(X, C, i, j, d))
				delta_min = Dcluster(X, C, i, j, d);
			if (DK < Dcluster(X, C, i, j, d))
				DK = Dcluster(X, C, i, j, d);
			}
	float dunn = delta_min / delta_max;
	float PBM = (float)(E1 * DK)/EK;
	PBM = (float)PBM/c;
	PBM = pow(PBM,2);
/*	for (int i = 1; i <= c; i++) {
		for (int j = 1; j <= d; j++)
			cout << C[i][j] << " ";
		cout << endl;
	}
*/
	for (int i = 1; i <= c; i++)
		cout << E[i]<< endl;
	
	//giai phong bo nho cua cac ma tran
	free(X, n, d);
	free(U, n, c);
	free(C, c, d);
	return 0;
}


