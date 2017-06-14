#include "stdafx.h"
#include "Move.h"


Move::Move()
{
}

Move::Move(int city1, int city2)
{
	this->city1 = city1;
	this->city2 = city2;
}


Move::~Move()
{
}

bool Move::operator ==(const Move & move)
{
	if ( ((this->city1 == move.city1) && (this->city2 == move.city2))
		|| ((this->city2 == move.city1) && (this->city1 == move.city2)) )
		return true; 
	else
		return false;

}