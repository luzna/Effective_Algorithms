#pragma once
class Move
{
public:
	int city1;
	int city2;

	Move();
	Move(int city1, int city2);
	~Move();

	bool operator==(const Move & m);

};

