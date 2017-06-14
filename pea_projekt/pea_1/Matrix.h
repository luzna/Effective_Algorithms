#pragma once

#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

class Matrix
{
public:

	int n;		//liczba miast
	int **M;		//macierz koszt�w

	Matrix();
	Matrix(string fileName); //wczytywanie pliku do M
	
	

	~Matrix();
	void View();
};

