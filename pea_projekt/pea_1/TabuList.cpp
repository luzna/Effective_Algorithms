#include "stdafx.h"
#include "TabuList.h"


TabuList::TabuList(int size)
{
	this->size = size;
}

TabuList::~TabuList()
{
}

void TabuList::Add(Move move)
{
	this->list.push_back(move);

	if (list.size() > size)
		list.pop_front();

}

bool TabuList::Contains(Move move)
{
	for (std::list<Move>::iterator it = list.begin(); it != list.end(); ++it)
		if( *it == move )
			return true;
		
	return false;
}
