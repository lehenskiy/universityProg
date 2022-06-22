// Quicksort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>

using namespace std;

int partition(int* mas, int l, int r)
{
	int pivot = mas[l];
	int i = l - 1, j = r + 1;

	while (true) {
		// ищем элемент, больший чем опорный, с левой границы
		do {
			i++;
		} while (mas[i] < pivot);

		// ищем элемент, меньший чем опорный, с правой границы
		do {
			j--;
		} while (mas[j] > pivot);

		// границы сдвинулись друг к другу
		if (i >= j)
			return j;

		int dump = mas[i]; // обмен элементов
		mas[i] = mas[j];
		mas[j] = dump;
	}
}

void Quicksort(int arr[], int low, int high)
{
	if (low < high) {
		
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		Quicksort(arr, low, pi);
		Quicksort(arr, pi + 1, high);
	}
}

int main()
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

		Quicksort(mas, 0, n - 1);
		cout << "Sorted array: ";

		for (int i = 0; i < n; i++)
			cout << mas[i] << ' ';
		cout << endl;

		delete[] mas;

		cout << "Press 1 to restart: " << endl;
		cin >> contin;
	}
}
