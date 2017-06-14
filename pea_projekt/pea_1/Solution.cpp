#include "stdafx.h"
#include "Solution.h"


Solution::Solution()
{
}

Solution::Solution(int size)
{
	this -> n = size;
	path = new int[n];

	/*for (int i = 0; i < n; i++) {
		path[i] = 0;
	}*/
}


Solution::~Solution()
{
	
}

void Solution::Random()
{
	for (int i = 0; i < n; i++) {
		path[i] = i;
	}

	//srand(time(NULL));
	random_shuffle(&path[0], &path[n]);

}

void Solution::Swap(int i, int j)
{
	int buff = path[i];
	path[i] = path[j];
	path[j] = buff;
}

void Solution::RandomSwap()
{
	int i, j;
	do {
		i = rand() % n;
		j = rand() % n;
	} while (i == j);

	//Move move(path[i],path[j]);
	Swap(i, j);

	//return move;
}

bool Solution::Contains(int element)
{
	for (int i = 0; i < n; i++) {
		if (this->path[i] == element)
			return true;
	}

	return false;
}

void Solution::View()
{
	for (int i = 0; i < n; i++) {
		cout << path[i] << " ";
	}
	cout << endl;
}

void Solution::Assign(Solution s)
{
	for (int i = 0; i < n; i++) {
		this->path[i] = s.path[i];
	}
}

bool Solution::operator==(const Solution & s)
{
	for (int i = 0; i<n; i++)
	{
		if (this->path[i] != s.path[i])
		{
			return(false);
		}
	}
	return(true);
}
