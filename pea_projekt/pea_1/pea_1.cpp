// pea_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "Matrix.h"
#include "SimAnnealing.h"
#include "TabuSearch.h"
#include "Genetic.h"
#include <iostream>
#include <conio.h>
#include <string>
using namespace std;


LARGE_INTEGER startTimer()		//funkcje potrzebne do pomiaru czasu
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}

LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}



void Menu() {
	int m;
	char sign0;
	Matrix *matrix;
	SimAnnealing *simAnnealing;
	TabuSearch *tabuSearch;
	Genetic *genetic;
	string file;

	int e;

	do {
		cout << "MENU \n[1] - Symulowane wyzarzanie.  \n[2] - Tabu Search. \n[3] - Algorytm genetyczny.";
		cin >> m;
		cout << endl;

		switch (m)
		{
		case 1:
		
			double cooling_rate;
			double s;
			cout << "Nazwa pliku: ";
			cin >> file;
			matrix = new Matrix(file);
			simAnnealing = new SimAnnealing(*matrix);
			cout << "Wprowadz wspolczynnik ochladzania: ";
			cin >> cooling_rate;
			cout << "Wprowadz liczbe iteracji s:";
			cin >> s;
			cout << "Dlugosc znalezionej sciezki: " << (*simAnnealing).Algorithm(cooling_rate, s);
			break;

		case 2:

			int neighbourhood_size, tabu_size;
			cout << "Nazwa pliku: ";
			cin >> file;
			matrix = new Matrix(file);
			tabuSearch = new TabuSearch(*matrix);
			cout << "Wprowadz rozmiar sasiedztwa: ";
			cin >> neighbourhood_size;
			cout << "Wprowadz rozmiar listy tabu:";
			cin >> tabu_size;
			cout << "Dlugosc znalezionej sciezki: " << (*tabuSearch).Algorithm(neighbourhood_size, tabu_size);
			break;

		case 3:

			double crossover_rate, mutation_rate;
			cout << "Nazwa pliku: ";
			cin >> file;
			matrix = new Matrix(file);
			genetic = new Genetic(*matrix);
			cout << "Wprowadz wspolczynnik krzyzowania: ";
			cin >> crossover_rate;
			cout << "Wprowadz wspolczynnik mutacji:";
			cin >> mutation_rate;
			cout << "Dlugosc znalezionej sciezki: " << (*genetic).Algorithm(crossover_rate, mutation_rate) << endl;
			break;
		default:
			break;

		}
		cout << endl << "Czy chcesz zakonczyc program(t/n)?"; cin >> sign0;
		cout << endl;
		} while (sign0 != 't');

	
}

void Calculate() {
	//-------------------------------------------------------------------
	//podstawowy algorytm do obliczania czasu wykonywania operacji 
	//---
	string f = "gr21.tsp";
	Matrix matrix(f);
		
	SimAnnealing p(matrix);
	TabuSearch tabu_search(matrix);
	Genetic genetic(matrix);

	double c[] = { 0.8, 0.85, 0.9, 0.95 , 0.99 };			//crossover
	double m[] = { 0.01, 0.05, 0.1 };								//mutation

	double t[10];			////zapis wyników pomiarów do tablicy w celu zautomatyzowania czêœci obliczeñ
	int result[10];

	//for (int j = 0; j < 5; j++) {
	
					
		for (int i = 0; i < 10; i++)
		{
			LARGE_INTEGER performanceCountStart, performanceCountEnd, freq;
			performanceCountStart = startTimer();					//zapamiêtujemy czas pocz¹tkowy

			result[i] = genetic.Algorithm(c[3], m[1]);
			cout << result[i] << endl;												//tutaj funkcje, których mierzymy wydajnoœæ
																				//knapsack.GreedyAlgorithm();

			performanceCountEnd = endTimer();						//zapamiêtujemy koniec czasu
			double tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart);

			QueryPerformanceFrequency(&freq);
			cout.setf(ios::fixed);
			//cout << "czestotliwosc:" << freq.QuadPart << endl;
			//cout << "tm:" << tm;
			//cout << endl << "Time:" << setprecision(8) << tm/freq.QuadPart << endl;
			t[i] = tm / freq.QuadPart;
		}




		double sum = 0;
		int sum_result = 0;
		for (int i = 0; i < 10; i++) {
			sum += t[i];
			sum_result += result[i];
		}

		cout << endl <<   " Sredni wynik: " << sum_result / 10 << endl << " Srednia ze 100 pomiarow: " << sum / 10 << endl;
	//}
	
}

int _tmain(int argc, _TCHAR* argv[])
{

	srand(time(NULL));
	
	/*string f = "gr21.tsp";
	Matrix matrix(f);
	//matrix.View();
	int neighbourhood_size = matrix.n * matrix.n;
	int tabu_size = 10;

	double cooling_rate = 0.999;
	double s = (matrix.n * matrix.n) / 4;

	double crossover_rate = 0.9;
	double mutation_rate = 0.01;


	SimAnnealing p(matrix);
	TabuSearch tabu_search(matrix);
	Genetic genetic(matrix);

	//cout << "Wyzarzanie: " << p.Algorithm(cooling_rate, s) << endl;
	//cout << "Tabu: " << tabu_search.Algorithm(neighbourhood_size, tabu_size) << endl;
	cout << "Algorytm genetyczny: " << genetic.Algorithm(crossover_rate, mutation_rate) << endl;*/

	
	
	
	//Menu();
	Calculate();
	



	system("pause");

	return 0;
}




