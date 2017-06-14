#pragma once
#include "Matrix.h"
#include "Solution.h"
#include "Move.h"
#include <list>
#include <vector>
using namespace std;

#define POPULATION_SIZE 200
#define UNCHANGED_GENERATIONS_LIMIT 100

class Genetic
{
public:
	Matrix cities;
	int genes_amount;

	Solution** population;
	Solution** next_population;
	Solution *best_chromosome;
	double crossover_rate, mutation_rate;


	Genetic();

	Genetic(Matrix m);
	~Genetic();
	void randomPopulation();
	void nextPopulation();
	bool hasDuplicate(Solution chromosome, int population_count);

	double pathLength(Solution s);
	void copyToNextPopulation(Solution s, int index);
	Solution rouletteSelection(double *fitness);
	//Solution* oxCrossover(Solution parent_a, Solution parent_b);
	vector<Solution> oxCrossover(Solution parent_a, Solution parent_b);

	void Mutate(Solution * const chromosone);

	

	double randomInclusive(double max);

	double randomExclusive(double max);

	double evaluateFitness(Solution s);

	double getBestFitness();

	int Algorithm(double crossover_rate, double mutation_rate);
};

