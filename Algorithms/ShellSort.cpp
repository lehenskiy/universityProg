#include <iostream>
#include <math.h>
#include <ctime>

using namespace std;

void Shell(int* mas, int n) {
	int l, s, dump;
	int m = n / 2;
	int *step = new int[m];
	step[m - 1] = 0;
	step[0] = 1;
	int i = 0;
	for (; 3 * step[i] < n; i++) 
	{ // Рассчитываем шаги по Седжвику
		i++;
		if (i % 2 == 0) 
			step[i] = 9 * pow(2, i) - 9 * pow(2, i / 2) + 1; // четный порядок
		else step[i] = 8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1; // нечетный
	}
	i--;
	for (; i >= 0; i--) // итерации для сортировки с шагами
	{
		s = step[i]; // текущий шаг
		for (int o = 0; o < s; o++)  // сортировка с шагом
		{
			for (int j = o + s; j < n; j = j + s) // сортировка группы
			{
				dump = mas[j];
				for (l = j - s; l >= 0 && mas[l] > dump; l = l - s) // перемещение элемента на свое место в группе
					mas[l + s] = mas[l];
				mas[l + s] = dump;
			}
		}
	}
}

void main()
{
	int n;
	char contin = '1';
	while (contin == '1')
	{
		cout << "Enter n: ";
		cin >> n;
		int* mas = new int[n];
		
		cout << "Array: ";
		
		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0; i < n; i++) // заполнение массива
			mas[i] = rand() % 99 + 1;

		for (int i = 0; i < n; i++)
			cout << mas[i] << ' ';
		cout << endl;

		Shell(mas, n);
		cout << "Sorted array: ";
		
		for (int i = 0; i < n; i++)
			cout << mas[i] << ' ';
		cout << endl;

		delete[] mas;

		cout << "Press 1 to restart: " << endl;
		cin >> contin;
	}
}
