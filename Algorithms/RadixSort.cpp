#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<locale.h>
#include<ctime>

using namespace std;

void printArray(int* a, int n);
int max_rank(int* a, int n);
void bit_sort(int* a, int l, int r, int k);

int main()
{
	int n;
	cout << "Enter array size: ";
	cin >> n;
	int* mas = new int[n];
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < n; i++) {
		mas[i] = rand() % 1000;
	}

	cout << "Current array: " << endl;
	printArray(mas, n);

	int k = max_rank(mas, n);
	bit_sort(mas, 0, n - 1, k);

	cout << "Sorted array: " << endl;
	printArray(mas, n);

	delete[] mas;
}

void printArray(int* a, int n)
{
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int max_rank(int* a, int n) // вычислить максимальный разряд
{
	int max = 0;
	for (int i = 0; i < n; i++) { // находим максимальное число массива
		if (a[i] > max) {
			max = a[i];
		}
	}
	int mask = 1;
	mask <<= 31; // идем с максимального бита(31, так как INT_MAX = 2^31)
	int k = 0;
	while (mask)
	{
		if ((mask & max) != 0) {
			return (31 - k);
		}
		mask = mask >> 1;
		k++;
	}
	return 0;
}

void bit_sort(int* a, int l, int r, int curRank)
{
	if ((l >= r) || (curRank < 0)) return;
	else
	{
		int i = l;
		int j = r;
		int mask = 1;
		mask <<= curRank;
		while (i < j) // устойчивая сортировка по текущему биту
		{
			while ((i < j) && ((a[i] & mask) == 0)) // ищем элемент массива, больший текущей маски
				i++;
			while ((i < j) && ((a[j] & mask) != 0)) // ищем элемент массива, меньший текущей маски
				j--;
			if (i < j)
				swap(a[i], a[j]); // меняем элементы местами 
		}
		if ((a[r] & mask) == 0) // сдвиг j
			j++;
		if (l < j)
			bit_sort(a, l, j - 1, curRank - 1); // сортируем левую часть по меньшему биту
		if (i < r)
			bit_sort(a, i, r, curRank - 1); // сортируем правую часть по меньшему биту
	}
}