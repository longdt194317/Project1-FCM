#pragma once
class Memory
{
public:
	void allocate(float**& array, int row, int col);
	void free(float**& array, int row, int col);
	void read(float**& X, int row, int col);
};

