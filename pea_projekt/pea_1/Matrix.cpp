#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix()
{
}

/*Matrix::Matrix(string fileName)
{
	fstream file;
	file.open(fileName, ios::in);
	if (file.good() == true)
	{
		file >> n;					//pierwsza linia - ilosc miast

		
		M = new int *[n];

		for (int i = 0; i<n; i++)	//tworzenie x wierszy tablic o d?ugo?ci y
			M[i] = new int[n];
		
		//int ** M = new int[n][n];

		int x;
		for (int i = 0; i<n; i++)
		{
			for (int j = 0; j <= i; j++) {
				file >> x;
				M[i][j] = x;
				M[j][i] = x;
			}


		}
		file.close();
	}
	else cout << "Niepowodzenie odczytu pliku!";
}*/

Matrix::Matrix(string fileName)
{
	fstream file;
	file.open(fileName, ios::in);
	int format;
	if (file.good() == true)
	{
		char str[100];
		char * p;
		while (true) {
			file >> str;
			p = strtok(str, ": ");					//przycina do ':'

			
			if (strcmp(p, "DIMENSION") == 0) {
				file >> str;
				p = strtok(str, " :");
				n = atoi(p);
			}
			if (strcmp(p, "EDGE_WEIGHT_FORMAT") == 0) {
				file >> str;
				p = strtok(str, " :");
				if (strcmp(p, "FULL_MATRIX") == 0)
					format = 1;
				else if (strcmp(p, "LOWER_DIAG_ROW") == 0)
					format = 2;
			}
			else if (strcmp(p, "EDGE_WEIGHT_TYPE") == 0) {
				file >> str;
				p = strtok(str, " :");
				if (strcmp(p, "EUC_2D") == 0)
					format = 3;
			}
			else if (strcmp(p, "EDGE_WEIGHT_SECTION") == 0) {
				break;
			}
			else if (strcmp(p, "NODE_COORD_SECTION") == 0) {
				break;
			}
		}
		
		switch (format) {
		case 1:
			M = new int *[n];

			for (int i = 0; i < n; i++) {	//tworzenie x wierszy tablic o d?ugo?ci y
				M[i] = new int[n];
				for (int j = 0; j < n ; j++) {
					file >> M[i][j];
				}

			}
			break;
		case 2:
			M = new int *[n];
			int w;
			for (int i = 0; i < n; i++)
			{
				M[i] = new int[n];
				for (int j = 0; j <= i; j++) {
					file >> w;
					M[i][j] = w;
					M[j][i] = w;
				}
			}
			break;
		case 3:
			int nr;
			float* x = new float[n];
			float* y = new float[n];

			for (int i = 0; i < n; i++) {
				file >> nr;
				file >> x[i];
				file >> y[i];
			}
			M = new int *[n];
			float xd, yd;
			for (int i = 0; i < n; i++) {
				M[i] = new int[n];
				for (int j = 0; j < n; j++) {
					xd = x[i] - x[j];
					yd = y[i] - y[j];
					M[i][j] = int(sqrt(xd*xd + yd*yd));
				}

			
			break;
		}
		}
		file.close();

		for (int i = 0; i < n; i++)
		{
			M[i][i] = 0;
		}
	}
	else cout << "Niepowodzenie odczytu pliku!";


}




Matrix::~Matrix()
{
}

void Matrix::View()
{
	cout << setw(3) << " ";
	for (int j = 0; j<n; j++)
		cout << setw(4) << j;

	cout << endl;

	for (int i = 0; i<n; i++)
	{
		cout << endl << setw(2) << i << " ";

		for (int j = 0; j<n; j++)
			cout << setw(4) << M[i][j];
	}

	cout << endl << endl;
}