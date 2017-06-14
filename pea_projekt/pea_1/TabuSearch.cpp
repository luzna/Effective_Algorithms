#include "stdafx.h"
#include "TabuSearch.h"


TabuSearch::TabuSearch()
{

}

TabuSearch::TabuSearch(Matrix m)
{
	cities = m;
	this->n = cities.n;
}

TabuSearch::~TabuSearch()
{}

int TabuSearch::Value(Solution s)
{
	int sum = 0;
	for (int i = 0; i < n - 1; i++) {
		sum += cities.M[s.path[i]][s.path[i + 1]];
	}
	sum += cities.M[s.path[0]][s.path[n - 1]];

	if (sum == 0) {
		return INT_MAX;
	}
	
	return sum;
}

int TabuSearch::Algorithm(int neighbourhood_size, int tabu_size)
{
	int no_change_count = 0;
	Solution solution(n), best_solution(n);
	solution.Random();
	best_solution.Assign(solution);
	Move move, best_move;
	TabuList tabu_list(tabu_size);

	for (int i = 0; i < NUM_INTERATIONS; i++) {
		Solution neighbour(n), best_neighbour(n);
		
		for (int j = 0; j < neighbourhood_size; j++){ 
			neighbour.Assign(solution);
			//move = neighbour.RandomSwap();
			if (!tabu_list.Contains(move) && Value(neighbour) < Value(best_neighbour)) {
				best_neighbour.Assign(neighbour);
				best_move = move;
			}
		}
		if (Value(best_neighbour) < Value(best_solution)) {
			best_solution.Assign(best_neighbour);
			no_change_count = 0;
		}
		else if (Value(best_neighbour) == Value(best_solution)) {
			no_change_count++;
		}

		//DYWERSYFIKACJA
		if (no_change_count == 2*n && DIVERSIFY == 1) {
			Solution n_best_solution(n);
			for (int i = 0; i < 10; i++) {
				solution.Random();
				if (Value(n_best_solution) < Value(solution)) {
					n_best_solution.Assign(solution);
				}
			}
			solution.Assign(n_best_solution);
			no_change_count = 0;
		}

		solution.Assign(best_neighbour);
		tabu_list.Add(best_move);
	}
	
	return Value(best_solution);
}
