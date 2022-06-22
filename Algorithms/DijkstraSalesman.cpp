// DijkstraSalesman.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>

using namespace std;

int minCostPointer(int n, int *m, int firstCity)
{
	// не переходим в первый город, если даже путь в него минимален.
	int min = 100;
	int pointer;
	for (int i = 0; i < n; i++)
	{
		if (m[i] != 0 && m[i] < min && i != firstCity)
		{
			min = m[i];
			pointer = i;
		}
	}
	return pointer;
}

void deleteFromArray(int n, int **&m, int col, int row)
{
	for (int i = 0; i < n; i++)
	{
		m[col][i] = 100;
		m[i][row] = 100;
	}
}

void printArray(int n, int **m)
{
	ios init(NULL);

	for (int cols = 0; cols < n; cols++)
	{
		cout << "  " << setfill('-') << setw(5 * n + 1) << "-" << endl;

		cout.copyfmt(init);
		cout << cols + 1 << " ";
		for (int rows = 0; rows < n; rows++)
		{
			if (m[cols][rows] == 100)
				cout << "| " << setw(2) << "-- ";
			else cout << "| " << setw(2) << m[cols][rows] << " ";
		}
		cout << "|" << endl;
	}
	cout << "  " << setfill('-') << setw(5 * n + 1) << "-" << endl;
	cout.copyfmt(init);
}

int main()
{
	setlocale(LC_ALL, "Russian"); // русский язык

	int n, k, i, j;
	cout << "Введите количество городов." << std::endl;
	cin >> n;

	int *p = new int[n]; // создание массива городов
	int *pmin = new int[n];

	ios init(NULL);

	int **m = new int*[n]; // создание матрицы стоимостей

	cout << "     ";

	for (int cols = 0; cols < n; cols++)
		cout << cols + 1 << "    ";

	cout << endl;

	srand(static_cast<unsigned int>(time(0))); // - случайные числа вместо псевдослучайных

	for (int rows = 0; rows < n; rows++)
	{
		cout << "  " << setfill('-') << setw(5 * n + 1) << "-" << endl;
		m[rows] = new int[n];

		cout.copyfmt(init);
		cout << rows + 1 << " ";
		for (int cols = 0; cols < n; cols++)
		{
			if (rows == cols)
				m[rows][cols] = 0;
			else
				m[rows][cols] = rand() % 99 + 1; // генерация стоимостей в интервале [1, 99]
			cout << "| " << setw(2) << m[rows][cols] << " ";
		}
		cout << "|" << endl;
	}
	cout << "  " << setfill('-') << setw(5 * n + 1) << "-" << endl;
	cout.copyfmt(init);

	cout << "Введите начальный город." << endl;
	cin >> k;

	int *way = new int [n]; // создание матрицы путей

	k--; // разница в нумерациях (пользователь вводит с 1, мы - с 0)
	int cost = 0;

	for (int i = 0; i < n - 1; i++) // пока не останется только вернуться в первый город
	{
		way[i] = k; // записываем текущий город
		k = minCostPointer(n, m[k], way[0]); // получаем следующий город, притом это не может быть первый город
		cout << "Выбираем в качестве следующего города №" << k + 1 << ", стоимость - " << m[way[i]][k] << endl;
		cost += m[way[i]][k];
		deleteFromArray(n, m, way[i], k); // удаляем из матрицы строки и столбцы
		printArray(n, m); // отрисовка массива
	}
	
	way[n-1] = k; // - последний город для посещения

	cout << "Последний путь из города " << way[n - 1] + 1 << " в город " << way[0] + 1 << ", стоимостью " << m[way[n - 1]][way[0]] << endl;

	cout << "Итоговый путь: ";

	way[n] = way[0]; // возвращаемся в точку старта
	cost += m[way[n - 1]][way[0]];

	for (int i = 1; i <= n; i++)
	{
		cout << way[i - 1] + 1 << "->" << way[i] + 1 << ", ";
	}
	cout << "стоимостью - " << cost << endl;
}