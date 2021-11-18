#include "pch.h"
#include "Calculate.h"
#include <math.h>
float Calculate::D(float**& X, float**& C, int i, int k, int d) {
	float length = 0;
	for (int j = 1; j <= d; j++) {
		length += (double)pow((double)X[i][j] - C[k][j], (double)2);
	}
	length = pow(length, (float)1 / 2);
	return length;
}
float Calculate::update_JUC(float**& U, float**& X, float**& C, int n, int c, int d, int m) {
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
void Calculate::update_CK(float**& U, float**& X, float**& C, int d, int m, int n, int k) {
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
void Calculate::update_UIK(float**& U, float**& X, float**& C, int d, int m, int c, int i, int k) {
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
float Calculate::Dcluster(float**& X, float**& C, int i, int k, int d) {
	float length = 0;
	for (int j = 1; j <= d; j++) {
		length += (double)pow((double)C[i][j] - C[k][j], (double)2);
	}
	length = pow(length, (float)1 / 2);
	return length;
}
