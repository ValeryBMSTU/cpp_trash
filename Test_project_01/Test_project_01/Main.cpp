#include <conio.h> 
#include <iostream>
#include "stdio.h"


#define F(v, i) (v |= (1 & lt; &lt; i))
//using std::cout;
using namespace std;
//Некий текст
int main()
{
	setlocale(LC_ALL, "RUSSIAN");

	unsigned short n = 16 >> 2;
	int x = 0;
	x = ((1 << 3) | (3 << 1)) & (7 ^ 3);

	cout << x;
	_getch();
	return 0;
}