#include <iostream>
#include <time.h>
#include "External_chains.h"
#include "Internal_chains.h"

using namespace std;

int main()
{
	// Внешние цепочки
	/*
	srand(time(0));
	int n = 15;
	int *a = new int[n], h;

	// Создаем массив случайных чисел
	for (int i = 0; i < n; i++) {
		a[i] = rand() % 264;
		cout << a[i] << " ";
	}

	cout << endl << endl;

	// Cоздаем хеш-таблицу
	List* H = new List[7];
	for (int i = 0; i < n; i++)
	{
		h = a[i] % 7;
		H[h].AddToTail(a[i]);
	}

	for (int j = 0; j < 7; j++)
	{
		H[j].PrintList();
	}

	cout << endl << endl;

	int x, y;
	cout << "Enter x and y: ";
	cin >> x >> y;

	cout << endl << endl;

	if (H[x % 7].FindKey(x) != 0)H[x % 7].Del(H[x % 7].FindKey(x));
	for (int j = 0; j < 7; j++)
	{
		H[j].PrintList();
	}

	cout << endl << endl;

	if (H[y % 7].FindKey(y) == 0)H[y % 7].AddToTail(y);
	for (int j = 0; j < 7; j++)
	{
		H[j].PrintList();
	}
	*/
	// Внутренние цепочки
	//*
	srand(time(0));
	int n = 15;
	int *a = new int[n], h;

	// Создаем массив случайных чисел
	for (int i = 0; i < n; i++) {
		a[i] = rand() % 100;
		cout << a[i] << " ";
	}

	for (int i = 0; i < 4; i++)cout << endl;

	Hash table(a, n, 7);

	table.Print();

	for (int i = 0; i < 4; i++)cout << endl;

	int x, y;
	cout << "Enter x and y: ";
	cin >> x >> y;
	if (table.Find(x) != 0)table.Del(x);
	cout << "Delete element " << x << " : " << endl;
	table.Print();

	cout << endl;
	cout << endl;
	cout << endl;
	for (int i = 0; i < 4; i++)cout << endl;

	if (table.Find(y) == 0)table.Add(y);
	cout << "Add element " << y << " : " << endl;

	table.Print();
	//*/
}