#pragma once
#include <list>
#include "Move.h"
using namespace std;

class TabuList
{
private:
	int size;
	list <Move> list;

public:

	TabuList(int size);
	~TabuList();
	void Add(Move move);
	bool Contains(Move move);
};

