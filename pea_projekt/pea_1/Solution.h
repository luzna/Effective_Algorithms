#pragma once

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include <algorithm>
using namespace std;
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Move.h"

class Solution
{
public:

	int n;
	int *path;  //rozwi?zanie

	Solution();
	Solution(int size);
	~Solution();
	void Random();
	void Swap(int i, int j);
	void RandomSwap();
	bool Contains(int element);
	void View();
	void Assign(Solution s);
	bool operator==(const Solution & s);
};

