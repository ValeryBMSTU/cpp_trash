#include <conio.h> 
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

// �����-�� �����
void sysout(double **a, double *y, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << "*x" << j;
			if (j < n - 1)
				cout << " + ";
		}
		cout << " = " << y[i] << endl;
	}
	_getch();
	return;
}
double * gauss(double **a, double *y, int n)
{
	double *x, max;
	int k, index;
	const double eps = 0.00001;  // ��������
	x = new double[n];
	k = 0;
	while (k < n)
	{
		// ����� ������ � ������������ a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		// ������������ �����
		if (max < eps)
		{
			// ��� ��������� ������������ ���������
			cout << "������� �������� ���������� ��-�� �������� ������� ";
			cout << index << " ������� A" << endl;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		// ������������ ���������
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue; // ��� �������� ������������ ����������
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue; // ��������� �� �������� ���� �� ����
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	// �������� �����������
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}
void SLAU(int n, double** M)
{
	double **a, *y, *x;
	system("chcp 1251");
	system("cls");
	y = new double[n];
	a = new double*[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			a[i][j] = M[j][i];
			if (i == j)
				a[i][j] -= 1;
			cout << "a[" << i << "][" << j << "]= " << a[i][j] << endl;
		}
	}
	for (int i = 0; i < n; i++)
	{
		y[i] = 0;
		cout << "y[" << i << "]= " << y[i] << endl;;
	}
	cout << endl;
	sysout(a, y, n);
	x = gauss(a, y, n);
	for (int i = 0; i < n; i++)
		cout << "x[" << i << "]=" << x[i] << endl;
	cin.get(); cin.get();
	_getch();
}


// ������������� ��������� ���������, ��������� �������� � ���������� �����-������
void Install()
{
	setlocale(LC_ALL, "RUSSIAN");
	srand(time(NULL));
	cout << fixed;
	cout.precision(2);
}
// ������������ ������ ������� ������� � ����
void FileInput(double** M, int i, int j, ofstream& fout) 
{	
	//_itoa_s(M[i][j], s, 10);
	if ((M[i][j] == 0.0) || (M[i][j] == 1.0))
		fout << M[i][j] << ".0" << ' ';
	else
		fout << M[i][j] << ' ';
} 
// ������������ ������ ������� � ����
void FileInput(int X, ofstream& fout)
{
	//_itoa_s(X, s, 10);
	fout << X << endl << endl;
}
// ������ �����
double** FileRead(ifstream& fcin, int& X)
{
	fcin.open("Text.txt");

	double a;
	double** M = new double*[X];
	cout << "�������� ������� ����������� ��������:\n\n";
	fcin >> X;
	for (int i = 0; i < X; i++)
	{
		M[i] = new double[X];
		for (int j = 0; j < X; j++)
		{
			fcin >> a;
			cout << a << ' ';
			M[i][j] = a;
		}
		cout << endl;
	}
	cout << endl;
	fcin.close();

	return M;
}
// ���� ������� �������
int Size(ofstream& fout)
{	
	int X;
	cout << "������� ������ �������: ";
	cin >> X;
	FileInput(X, fout);
	return X;
}
// ����� ��������� �������
double** StdInput(int& X, ofstream& fout)
{	
	double** M = new double*[X];
	for (int i = 0; i < X; i++)
	{
		cout << endl << "������� ����� ������ �������� " << i + 1 << " ������ �������:\n" << endl;
		M[i] = new double[X];
		for (int j = 0; j < X; j++)
		{
			cin >> M[i][j];
			FileInput(M,i,j, fout);
		}
		fout << endl << endl;
	}
	system("cls");
	//cout << endl;
	return M;
}
// ����� ��������� ������������
void StdOut(int* T, int X)
{	
	for (int i = 0; i < X; i++)
	{
		cout << "P" << i + 1 << " final = " << T[i] << endl;
	}
	cout << endl;
}
// ����� ������� �� ����� �������
void Matrix(double** M, int X)
{	
	cout << "�������� �������:\n\n";
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < X; j++)
		{
			cout << M[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
// ��������� ����������� �������� � ���������� ��������
int* SimDisc(double** M, int X)
{	
	int n;
	cout << "������� ��������� �������� ��� ����������� �������: ";
	cin >> n;
	cout << endl;

	int* T = new int[X];
	for (int i = 0; i < X; i++)
	{
		T[i] = 0;
	}

	int pos = 0;
	double sum = 0.0;
	int count = 0;
	double inter = 0;
	while (count < n)
	{
		inter = rand() % 100 + 0.001;
		inter /= 100;

		//cout << "��������������� �����: " << inter << endl;
		//cout << "������� �� ��������� " << pos + 1;
		for (int j = 0; sum < inter; j++)
		{
			sum += M[pos][j];
			if (sum >= inter)
			{
				pos = j;
				T[j] += 1;
			}
		}
		sum = 0;
		//cout << " � ��������� " << pos + 1 << endl;
		count += 1;

	}
	cout << endl;
	StdOut(T, X);
	return T;

}
// ��������� ����������� �������� � ����������� ��������
int* SimCont(double** M, int X)
{
	int n = 0;
	cout << "������� ��������� �������� ��� ������������ �������: ";
	cin >> n;
	cout << endl;

	int* T = new int[X];
	for (int i = 0; i < X; i++)
	{
		T[i] = 0;
	}
	
	double** r = new double*[X];
	for (int i = 0; i < X; i++)
	{
		r[i] = new double[X];
	}

	int count = 0;
	int S = 0, s = 0;

	double min = 100;
	while (count < n)
	{
		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < X; j++)
			{
				if (M[i][j] != 0)
					r[i][j] = -(1 / (M[i][j]))*log((rand() % 100 + 0.001) / 100);
				else
					r[i][j] = 100;
				//cout << r[i][j] << endl;

			}
		}
		for (int i = 0; i < X; i++)
		{
			if (r[S][i] <= min)
			{
				min = r[S][i];
				s = i;
			}
		}
		//cout << "������� �� ��������� " << S + 1 << " � ��������� " << s + 1 << endl;
		S = s;
		T[S] += 1;
		s = 0;
		min = 100;
		count += 1;

	}
	//for (int i = 0; i < X; i++)
	//
	//	cout <<"P"<< i+1 <<" = " << T[i] << endl;
	//}
	cout << endl;
	StdOut(T, X);

	return T;

}
// ������������� ������
void Free(double** M, int X)
{	
	for (int i = 0; i < X; i++)
	{
		delete[] M[i];
	}
}
// ������������� ������
void Free(int* T, int X)
{
	delete[] T;
}

int main()
{
	Install();

	ofstream fout;
	ifstream fcin;

	int X = 0;

	double** M = FileRead(fcin, X);
	int* T = SimDisc(M, X);
	T = SimCont(M, X);

/*
	double inter = 0.0;
	inter = rand() % 100 + 0.001;
	inter /= 100;
	double* pFin = new double[X];
	for (int i = 0; i < X; i++)
	{
		pFin[i] = 0.0;
		inter = rand() % 100 + 0.001;
		inter /= 100;
		for (int j = 0; j < X; j++)
		{
			pFin[i] += inter * M[j][i];
		}
		cout << pFin[i] << endl;
	}
*/
	Free(M, X); 
	Free(T, X);

	cout << "���������� ������...";
	_getch();
	return 0;
}
