// Heapsort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>

using namespace std;

void BuildMaxHeap(int mas[], int n, int i)
{
	int biggest = i;
	// Инициализируем наибольший элемент как корень
	int l = 2 * i + 1; // левый = 2*i + 1
	int r = 2 * i + 2; // правый = 2*i + 2

	// Если левый дочерний элемент больше корня
	if (l < n && mas[l] > mas[biggest])
		biggest = l;

	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (r < n && mas[r] > mas[biggest])
		biggest = r;

	// Если самый большой элемент не корень
	if (biggest != i)
	{
		swap(mas[i], mas[biggest]);

		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		BuildMaxHeap(mas, n, biggest);
	}
}

void Heapsort(int mas[], int n)
{
	// Построение кучи (снизу вверх, начинаем с последнего поддерева)
	for (int i = n / 2 - 1; i >= 0; i--)
		BuildMaxHeap(mas, n, i);

	// извлекаем элементы из кучи, начиная с самого большего,
	// пока не останется один элемент - он наименьший
	for (int i = n - 1; i > 0; i--)
	{
		// Перемещаем текущий корень в конец
		swap(mas[0], mas[i]);

		// сохраняем свойства кучи на уменьшенной куче
		BuildMaxHeap(mas, i, 0);
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

		Heapsort(mas, n);
		cout << "Sorted array: ";

		for (int i = 0; i < n; i++)
			cout << mas[i] << ' ';
		cout << endl;

		delete[] mas;

		cout << "Press 1 to restart: " << endl;
		cin >> contin;
	}
}
