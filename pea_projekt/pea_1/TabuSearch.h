#pragma once
#include "Matrix.h"
#include "Solution.h"
#include "Move.h"
#include <queue>
#include "TabuList.h"

#define TABU_SIZE 10
#define NUM_INTERATIONS 1000
#define DIVERSIFY 1


class TabuSearch
{
public:
	Matrix cities;
	int n;

	TabuSearch();
	TabuSearch(Matrix m);
	~TabuSearch();
	int Value(Solution s);
	int Algorithm(int neighbourhood_size, int tabu_size);
};

