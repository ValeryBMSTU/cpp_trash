#include "stdlib.h"
#include <iostream>

using namespace std;

struct time_x{
	int x0;
	int x1;
};

int main() {
	int n = 0;
	cin >> n;
	time_x* mass = new time_x[n];
	for (int i = 0; i < n; i++) {
		cin >> mass[i].x0;
		cin >> mass[i].x1;
	}


	return 0;
}