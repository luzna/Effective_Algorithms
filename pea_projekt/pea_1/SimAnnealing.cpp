#include "stdafx.h"
#include "SimAnnealing.h"
#include "Matrix.h"

SimAnnealing::SimAnnealing(Matrix m)
{
	cities = m;
	this->n = cities.n;
	
}


SimAnnealing::~SimAnnealing()
{
}

int SimAnnealing::Value(Solution s)
{
	int sum = 0;
	for (int i = 0; i < n - 1; i++) {
		sum += cities.M[s.path[i]][s.path[i+1]];
	}
	sum += cities.M[s.path[0]][s.path[n - 1]];
	
	return sum;
}

void SimAnnealing::Initialize()
{
	int diff_max = 0;
	Solution trial(n);
	int *values = new int[n*n];
	trial.Random();

	for (int k = 0; k < n*n; k++) {
		values[k] = Value(trial);
		trial.RandomSwap();
	}
	for (int i = 0; i < n*n -1; i++) {
		if (values[i + 1] - values[i] > diff_max)
			diff_max = values[i + 1] - values[i];
	}

	start_temperature = (-1* diff_max)/log(0.9);

	end_temperature = 0.001;
}

double SimAnnealing::getProbability(int difference, double temperature) 
{
	return exp(-1 * difference / temperature);
}


int SimAnnealing::Algorithm(double cooling_rate, double s)
{
	Solution initial_solution(n), solution(n), solution_candidate(n);
	initial_solution.Random();
	
	Initialize();

	solution.Assign(initial_solution);
	int i = 0;
	float T = start_temperature;

	while (T > end_temperature) {
	for (int j = 0; j < s; j++) {
		solution_candidate.Assign(solution);

		solution_candidate.RandomSwap();
		
		if (Value(solution_candidate) < Value(solution)) {
			solution.Assign(solution_candidate);
		}
		else if ((rand() / (double)(RAND_MAX + 1)) < getProbability(Value(solution_candidate) - Value(solution),T)) {
			solution.Assign(solution_candidate);
		}
	}

		T = T *cooling_rate;
	}

	return Value(solution);
}


