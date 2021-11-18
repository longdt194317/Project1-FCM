#pragma once
class Calculate
{
public:
	float D(float**& X, float**& C, int i, int k, int d);
	float update_JUC(float**& U, float**& X, float**& C, int n, int c, int d, int m);
	void update_CK(float**& U, float**& X, float**& C, int d, int m, int n, int k);
	void update_UIK(float**& U, float**& X, float**& C, int d, int m, int c, int i, int k);
	float Dcluster(float**& X, float**& C, int i, int k, int d);
};

