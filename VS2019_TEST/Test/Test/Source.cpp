// Реализовать очередь с динамическим зацикленным буфером
// Формат ввода
// В первой строке количество команд n.n ≤ 1000000.

// Каждая команда задаётся как 2 целых числа : a b.

// a = 2 - pop front
// a = 3 - push back

// Если дана команда pop front, то число b - ожидаемое значение.Если команда pop front вызвана для пустой структуры данных, то ожидается “ - 1”.

// Формат вывода
// Требуется напечатать YES - если все ожидаемые значения совпали.Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include "stdlib.h"
#include <iostream>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#define SIZE 4 // Стартовый размер зацикленного буфера

using namespace std;

class Loop_buf {
public:
	Loop_buf() : size(SIZE), top(0), bot(0), info_flag(true) {
		mass = new int[size];
	}
	// Выбор команды
	bool command_switch(const int a, const int b) {
		if (a == 2) {
			return this->pop(b);
		}
		else if (a == 3) {
			return this->push(b);
		}
		else {
			return false;
		}
	}
	~Loop_buf() {
		delete[] mass;
	}
private:
	bool resize() {
		int* p = new int[size * 2];
		if (p == NULL) {
			return false;
		}
		for (int i = 0; bot != top; i++) {
			*(p + i) = mass[bot];
			bot = (bot + 1) % size;
		}
		bot = 0;
		top = size - 1;
		delete[] this->mass;
		mass = p;
		size *= 2;
		return true;
	}
	bool push(const int b) {
		if (bot == (top + 1) % size) {
			info_flag = resize();
		}
		if (info_flag) {
			mass[top] = b;
			top = (top + 1) % size;
			return true;
		}
		else {
			return false;
		}
	}
	bool pop(const int b) {
		if (top != bot) {
			if (b == mass[bot]) {
				bot = (bot + 1) % size;
				return true;
			}
			else {
				bot = (bot + 1) % size;
				return false;
			}
		}
		else if (b == -1) { // По условию ожидается, что для пустого буфера b = -1
			return true;
		}
		else {
			return false;
		}
	}

	int* mass;
	int size;
	int top;
	int bot;
	bool info_flag;
};

int main() {
	Loop_buf* Queue = new Loop_buf();
	bool info_flag = true;
	int n = 0;

	cin >> n; // Ввод количества команд

	for (int i = 0, command = 0, data = 0; i < n; i++) {
		cin >> command;
		cin >> data;
		if (!Queue->command_switch(command, data)) {
			info_flag = false; // Установка флага в случае хотя бы одного несовпадения
		}
	}

	if (info_flag) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}

	//delete Queue;

	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}