#pragma once

#include "Matrix.h"
#include "Solution.h"
#include <math.h>

const double e = 2.718281828459;

class SimAnnealing
{
public:
		
	Matrix cities;
	int n;
	double start_temperature, end_temperature;
	
	
	SimAnnealing(Matrix m);
	~SimAnnealing();
	int Value(Solution s);
	void Initialize();
	double getProbability(int difference, double temperature);
	int Algorithm(double cooling_rate, double s);
	

	
};

