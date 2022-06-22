#include "C:\Users\Alexey\source\repos\ArrayClass\ArrayClass\ArrayClass.h";
#include <ctime>
#include<iomanip>
#include <string.h>

using std::cout;
using std::cin;
using std::setw;
using std::endl;

using namespace ArrayClass;

Array::Array(int N = 1) // Создание массива, по умолчанию размер = 1
{
	a = new int[N];
	n = N;
}

Array::Array(int *b, int m)		//m -число эл-тов в массиве b
{
	a = new int[m];
	for (int i = 0; i < m; i++)
		a[i] = b[i];
	n = m;
}

Array::Array(const Array &X) // копия
{
	n = X.n;
	a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = X.a[i];
}

void Array::Scan(int m)			//ввод массива из m эл-тов с клавиатуры
{
	cout << "enter " << m << " elements: ";
	if (n != m)
	{
		delete[]a;   n = m;
		a = new int[m];
	}
	for (int i = 0; i < n; i++)
		cin >> a[i];
}


void Array::Fill()
{
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 99 + 1;
	}
}

void Array::Clear()
{
	delete[] a;
	n = 1;
	a = new int[1];
}

Array & Array::operator= (const Array &X)
{
	if (this != &X)
	{
		delete[]a;
		n = X.n;
		a = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = X.a[i];
	}
	return *this;
}

Array::~Array() // деструктор - высвобождаем память
{
	delete[]a;
}


void Array::Print()
{
		for (int i = 0; i < n; i++) {
			cout << a[i] << ' ';
		}
		cout << "\n";
}

int & Array::operator [] (int k)	//считывание i-го эл-та массива a
{
	try {
		if (k < 0)
			throw 0;
		if (k >= n)
			throw "incorrect index";
		return a[k];
	}
	catch (int m)
	{
		cout << "index <0";
		return a[m];
	}
	catch (char *s)
	{
		cout << s;
		return a[n - 1];
	}
	catch (...)
	{
		cout << "incorrect index";
		return a[0];
	}
}

int Array::FindKey(int el)
{
	for (int i = 0; i < n; i++)
		if (a[i] == el)
			return i;
	return -1;
}

Array Array::operator+ (int el) // создаем новый массив b=*this+key - не посмотрел, в файле уже реализовано
{
	Array b(n + 1); // создаем массив с кол-вом эл-ов больше, чем у текущего на 1
	for (int i = 0; i < n; i++) // копируем все эл-ы из текущего массива в новый
		b.a[i] = a[i];
	b.a[n] = el; // добавляем в конец необходимый элемент

	return b;
}

Array & Array::operator+= (int el) // добавляем эл-т в конец массива *this - реализовано в файле
{
	Array dump(n);
	dump = *this;
	delete[]a;
	n += 1;
	a = new int[n];
	for (int i = 0; i < n - 1; i++)
		a[i] = dump.a[i];
	a[n - 1] = el;

	return *this;
}

Array  Array::operator+(Array X) // создаем новый массив b=*this+X - реализовано в файле
{
	Array b(n + X.n); // создаем массив с кол-вом эл-ов больше, чем у текущего на кол-во элементов второго массива
	int i = 0;
	for (; i < n; i++) // копируем все эл-ы из текущего массива в новый
		b.a[i] = a[i];
	for (int j = 0; i < b.n; i++, j++)
		b.a[i] = X.a[j];

	return b;
}

Array & Array::operator+= (Array X) // добавляем массив X в конец массива *this
{
	Array dump(n);
	dump = *this;
	delete[]a;
	n += X.n;
	a = new int[n];
	int i = 0;
	for (; i < dump.n; i++)
		a[i] = dump.a[i];
	for (int j = 0; i < n; i++, j++)
		a[i] = X.a[j];

	return *this;
}

Array  Array::operator- (int key)		//создаем новый массив без эл-та key
{
	Array b(n - 1);
	int index = FindKey(key);
	for (int i = 0; i < n; i++)
	{
		if (i >= index)
			b.a[i] = a[i + 1]; // пропускаем элемент key
		else b.a[i] = a[i]; // пока еще не дошли до элемента key - просто копируем
	}

	return b;
}

Array & Array::operator-= (int key)		// удаляем эл-т из массива *this
{
	int index = FindKey(key);
	if (index == -1)
		return *this;
	Array dump(*this);
	delete[]a;
	n -= 1;
	a = new int[n];
	for (int i = 0; i < n; i++)
	{
		if (i >= index)
			a[i] = dump.a[i + 1]; // пропускаем элемент key
		else a[i] = dump.a[i]; // пока еще не дошли до элемента key - просто копируем
	}

	return *this;
}

Array Array::DelPosEq(int index)			//удаление эл-та с заданной позиции
							   //массива *this
{
	if (index >= n || index < 0)
		return *this;
	Array dump(n);
	dump = *this;
	delete[]a;
	n -= 1;
	a = new int[n];
	for (int i = 0; i < n + 1; i++)
	{
		if (i >= index)
			a[i] = dump.a[i + 1]; // пропускаем элемент с заданным индексом
		else a[i] = dump.a[i]; // пока еще не дошли до элемента key - просто копируем
	}

	return *this;
}

Array Array::DelPosNew(int index)			//создаем новый массив, удалив эл-т
							   //с заданной позиции массива *this
{
	if (index >= n || index < 0)
	{
		Array b(*this);
		return b;
	}
	Array b(n - 1);
	for (int i = 0; i < n; i++)
	{
		if (i >= index)
			b.a[i] = a[i + 1]; // пропускаем элемент key
		else b.a[i] = a[i]; // пока еще не дошли до элемента key - просто копируем
	}

	return b;
}

bool Array::operator== (const Array &X)
{
	if (n != X.n)
		return false;
	for (int i = 0; i < n; i++)
		if (a[i] != X.a[i])
			return false;
	return true;
}

bool Array::operator!= (const Array &X)
{
	return !(*this == X);
}

int Array::Max()
{
	int max = INT_MIN;
	for (int i = 0; i < n; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}

int Array::Min()
{
	int min = INT_MAX;
	for (int i = 0; i < n; i++)
		if (a[i] < min)
			min = a[i];
	return min;
}

ostream & operator<< (ostream &r, Array &X)
{
	for (int x = 0; x < X.n; x++)
		r << setw(4) << X.a[x];
	return r;
}

istream & operator>> (istream &r, Array &X)
{
	cout << "enter the number of elements: ";
	int m;    cin >> m;
	if (X.n != m)
	{
		delete[]X.a;
		X.a = new int[m];  X.n = m;
	}
	cout << "enter " << m << " elements of array: ";
	for (int i = 0; i < X.n; i++) r >> X[i];
	return r;
}

int Array::GetN()
{
	return n;
}

void Array::Sort()
{
	Quicksort(a, 0, n - 1);
}

void Array::Quicksort(int *arr, int l, int r)
{
	if (l < r)
	{
		int piv = arr[r]; // опорный элемент, с которым будем сравнивать остальные
		int i = l - 1;

		for (int j = l; j < r; j++) // проходимся по массиву от левой границы до правой 
									// и сортируем для выбранного опорного элемента
		{
			if (arr[j] < piv)
			{
				i++;
				int t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
		int t = arr[i + 1];
		arr[i + 1] = arr[r];
		arr[r] = t;

		Array::Quicksort(arr, l, i); // рекурсивно сортируем левую часть массива
		Array::Quicksort(arr, i + 2, r); // правую часть
	}
}

