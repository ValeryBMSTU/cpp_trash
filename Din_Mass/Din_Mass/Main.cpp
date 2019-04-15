#include <iostream>
#include <conio.h>

using namespace std;


void Write(double** M, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> M[i][j];
		}
	}
}
void Read(double** M, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << M[i][j] << ' ';
		}
		cout << endl;
	}
}

int main()
{
	int n;
	cin >> n;
	double** M = new double*[n];
	for (int i = 0; i < n; i++)
	{
		M[i] = new double[n];
	}
	Write(M, n);
	Read(M, n);

	for (int i = 0; i < n; i++)
	{
		delete[] M[i];
	}
	delete[] M;
	_getch();
	return 0;
}