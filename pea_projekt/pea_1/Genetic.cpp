#include "stdafx.h"
#include "Genetic.h"


Genetic::Genetic()
{
}


Genetic::Genetic(Matrix m)
{
	cities = m;
	this->genes_amount = m.n;

	population = new Solution*[POPULATION_SIZE];
	next_population = new Solution*[POPULATION_SIZE];
	this->best_chromosome = new Solution(genes_amount);
	randomPopulation();
}

Genetic::~Genetic()
{
}

void Genetic::randomPopulation()
{
	Solution *chromosome;
		
	for (int i = 0; i < POPULATION_SIZE; i++) {

		chromosome = new Solution(genes_amount);
		(*chromosome).Random();
		
		population[i] = new Solution(genes_amount);
		//next_population[i] = new Solution(genes_amount);
		(*population[i]).Assign(*chromosome);
		(*chromosome).~Solution();
	}
}

void Genetic::nextPopulation()
{
	double fitness[POPULATION_SIZE];

	for (int i = 0; i < POPULATION_SIZE; i++) {
		fitness[i] = evaluateFitness(*population[i]);
	}

	//--------------------------------------------
	// elitism - find and copy over the two best chromosones to the new population
	//-----------------------------------------------
	int first_elite_index, second_elite_index;
	first_elite_index = max_element(fitness, fitness + POPULATION_SIZE) - fitness;
	(*best_chromosome).Assign(*(population[first_elite_index]));

	double best_fitness = 0;
	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (i != first_elite_index && fitness[i] > best_fitness) {
			best_fitness = fitness[i];
			second_elite_index = i;
		}
	}
	
	this->next_population = new Solution*[POPULATION_SIZE];
	for (int i = 0; i < POPULATION_SIZE; i++) {
		next_population[i] = new Solution(genes_amount);
	}

	int offspring_amount = 0;
	(*next_population[offspring_amount]).Assign(*population[first_elite_index]);
	offspring_amount++;
	(*next_population[offspring_amount]).Assign(*population[second_elite_index]);
	offspring_amount++;

	while (true) {
		Solution parent_a(genes_amount), parent_b(genes_amount);
		parent_a.Assign(rouletteSelection(fitness));
		parent_b.Assign(rouletteSelection(fitness));
		
		while (parent_b == parent_a) {
			parent_b.Assign(rouletteSelection(fitness));
		}
		

		vector <Solution> offsprings(2);
		offsprings = oxCrossover(parent_a, parent_b);
		
		double random = randomInclusive(1);
		if (random <= mutation_rate)
		{
			(offsprings[0]).RandomSwap();
			(offsprings[1]).RandomSwap();
		}
			


		/* Add to new population if an equal chromosone doesn't exist already */
		
		//if (!hasDuplicate((offsprings[0]), offspring_amount))
		//{
			(*next_population[offspring_amount]).Assign((offsprings[0]));
			//copyToNewPopulation(offsprings[0], offspringCount);
			offspring_amount++;
		//}
		/* check if the new population is filled */
		if (offspring_amount == POPULATION_SIZE)
		{
			break;
		}
		if (!hasDuplicate((offsprings[1]), offspring_amount))
		{
			(*next_population[offspring_amount]).Assign((offsprings[1]));
			//copyToNewPopulation(offsprings[1], offspring_amount);
			offspring_amount++;
		}
		if (offspring_amount == POPULATION_SIZE)
		{
			break;
		}
		
	}

	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		(*population[i]).Assign(*next_population[i]);
	}
}

bool Genetic::hasDuplicate(Solution chromosome, int population_count)
{
	/* Iterate through each chromosone in newPopulation and compare them gene by gene */
	for (int i = 0; i < population_count; i++)
	{
		int genes_compared = 0;
		for (int gene = 0; gene < genes_amount; gene++)
		{
			if (chromosome.path[gene] != (*next_population[i]).path[gene])
			{
				/* These chromosones are not equal! */
				break;
			}
			genes_compared++;
		}

		if (genes_compared == genes_amount)
		{
			return true;
		}
	}

	return false;
}


double Genetic::pathLength(Solution s)
{
	int sum = 0;
	for (int i = 0; i < genes_amount - 1; i++) {
		sum += cities.M[s.path[i]][s.path[i + 1]];
	}
	sum += cities.M[s.path[0]][s.path[genes_amount - 1]];

	if (sum == 0) {
		return INT_MAX;
	}

	return sum;
}

void Genetic::copyToNextPopulation(Solution s, int index)
{
	(*next_population[index]).Assign(s);
}

Solution Genetic::rouletteSelection(double * fitness)
{
	double sum = 0;
	for (int i = 0; i < POPULATION_SIZE; i++) {
		sum += fitness[i];
	}

	//srand(time(NULL));
	double random = ((double)rand() * sum) / (double)RAND_MAX;
	sum = 0;
	for (int i = 0; i < POPULATION_SIZE; i++) {
		sum += fitness[i];
		if (sum >= random) {
			return (*population[i]);
		}
	}
	return (NULL);
}

vector<Solution> Genetic::oxCrossover(Solution parent_a, Solution parent_b)
{
	//Solution *offsprings[2];
	//offsprings[0] = new Solution(genes_amount);
	//offsprings[1] = new Solution(genes_amount);

	vector <Solution> offsprings;
	Solution offspring_a(genes_amount);
	Solution offspring_b (genes_amount);
	offsprings.push_back(offspring_a);
	offsprings.push_back(offspring_b);



	//srand(time(NULL));
	double random = ((double)rand() * 1) / (double)RAND_MAX;
	if (random > crossover_rate) {
		memcpy(offsprings[0].path, parent_a.path, sizeof(int) * genes_amount);
		memcpy(offsprings[1].path, parent_b.path, sizeof(int) * genes_amount);
		return offsprings;
	}

	int cut_index_1 = (int)randomInclusive(genes_amount);
	int cut_index_2 = (int)randomInclusive(genes_amount);
	while (cut_index_2 == cut_index_1) {
		cut_index_2 = (int)randomInclusive(genes_amount);
	}
	unsigned int cut_start, cut_end;
	if (cut_index_1 < cut_index_2) {
		cut_start = cut_index_1;
		cut_end = cut_index_2;
	}
	else {
		cut_start = cut_index_2;
		cut_end = cut_index_1;
	}


	for (int i = cut_start; i < cut_end; i++) {
		offsprings[0].path[i] = parent_b.path[i];
		offsprings[1].path[i] = parent_a.path[i];
	}

	int fill_index1 = cut_end;
	int fill_index2 = cut_end;
	int i = cut_end;
	while (fill_index1 != cut_start || fill_index2 != cut_start) {
		fill_index1 = fill_index1 % genes_amount;
		fill_index2 = fill_index2 % genes_amount;
		i = i % genes_amount;
		if (!(offsprings[0]).Contains(parent_a.path[i]) && fill_index1 != cut_start) {
			(offsprings[0]).path[fill_index1] = parent_a.path[i];
			fill_index1++;
		}
		if (!(offsprings[1]).Contains(parent_b.path[i]) && fill_index2 != cut_start) {
			(offsprings[1]).path[fill_index2] = parent_b.path[i];
			fill_index2++;
		}
		i++;
	}
	
	return offsprings;
}

void Genetic::Mutate(Solution *chromosone)
{
	/* 0.0 <= random <= 1 */
	{
		double random = randomInclusive(1);
		/* Nope, didn't happen */
		if (random > mutation_rate)
		{
			return;
		}
	}

	Solution tmp;
	int random1 = (int)randomExclusive(genes_amount);
	int random2 = (int)randomExclusive(genes_amount);
	while (random1 == random2)
	{
		random2 = (int)randomExclusive(genes_amount);
	}

	tmp.Assign(chromosone[random1]);
	chromosone[random1].Assign(chromosone[random2]);
	chromosone[random2].Assign(tmp);

}


double Genetic::randomInclusive(double max)
{
	//srand(time(NULL));
	/* Generate random number r, 0.0 <= r <= max */
	//return ((double)rand() / (double)RAND_MAX * max);
	return ((double)rand() * max) / (double)RAND_MAX;
}

double Genetic::randomExclusive(double max)
{
	//srand(time(NULL));
	/* Generate random number r, 0.0 <= r < max */
	//return ((double)rand() / ((double)RAND_MAX + 1) * max);
	return ((double)rand() * max) / ((double)RAND_MAX + 1);
}

double Genetic::evaluateFitness(Solution s)
{
	return 1 / pathLength(s);
}

double Genetic::getBestFitness()
{
	return evaluateFitness(*best_chromosome);
}

int Genetic::Algorithm(double crossover_rate, double mutation_rate)
{
	this->crossover_rate = crossover_rate;
	this->mutation_rate = mutation_rate;

	int no_change_count = 0;
	double best_fitness = -1;
	double new_fitness;

	while (no_change_count < UNCHANGED_GENERATIONS_LIMIT) {

		nextPopulation();
		new_fitness = getBestFitness();

		if (new_fitness > best_fitness) {

			best_fitness = new_fitness;
			no_change_count = 0;
		}
		else
			no_change_count++;
	}

	return pathLength(*best_chromosome);
}
