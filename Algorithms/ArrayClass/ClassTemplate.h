#pragma once
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

template <class T> class Array
{
public:
	T *a, n;
	Array(int m = 1);
	Array(T* b, int m);
	Array(const Array <T>& x);
	~Array();
	template <class T> friend ostream& operator << (ostream& r, Array <T>& x);
	template <class T> friend istream& operator >> (istream& r, Array <T>& x);
	T& operator[] (int i);
	Array <T>& operator= (const Array <T>& x);
	Array <T>& operator+= (T key);
	Array <T> operator+ (T key);
	Array <T>& operator+= (Array <T>);
	Array <T> operator+ (Array <T>);
	Array <T>& operator-= (T key);
	Array <T> operator- (T key);
	bool operator== (Array <T>);
	bool operator!= (Array <T>);

	Array <T>& DelPosEq(int index);
	Array <T> DelPosNew(int index);
	void Scan(int m);
	void Print();
	int FindKey(int key);
	int Max();
	int Min();
	void Sort();
	int GetN();
private:
	void Quicksort(T *arr, int l, int r);
};

template <class T> Array <T>::Array(int N)
{
	a = new T[N];
	n = N;
}

template <class T> Array <T>::Array(T* b, int m) {
	n = m;
	a = new T[n];
	for (int i = 0; i < n; i++)
		a[i] = b[i];
}

template <class T> Array <T>::Array(const Array<T>& x) {
	n = x.n;
	a = new T[n];
	for (int i = 0; i < n; i++) {
		a[i] = x.a[i];
	}
}

template <class T> Array <T>:: ~Array() {
	delete[]a;
}

template <class T> void Array <T>::Scan(int m)
{
	cout << "enter " << m << " elements: ";
	if (n != m)
	{
		delete[]a;   n = m;
		a = new T[m];
	}
	for (int i = 0; i < n; i++)
		cin >> a[i];
}


template <class T> int Array<T>::FindKey(int key) {
	for (int i = 0; i < n; i++) {
		if (a[i] == key) {
			return i;
		}
	}
	return -1;
}

template <class T> void Array<T>::Print() {
	for (int i = 0; i < n; i++) {
		cout << a[i] << ' ';
	}
	cout << endl;
}

template <class T> Array <T>& Array<T>::DelPosEq(int index)
{
	if (index >= n || index < 0)
		return *this;
	Array dump(n);
	dump = *this;
	delete[]a;
	n--;
	a = new T[n];
	for (int i = 0; i < n + 1; i++)
	{
		if (i >= index)
			a[i] = dump.a[i + 1]; // ���������� ������� � �������� ��������
		else a[i] = dump.a[i]; // ���� ��� �� ����� �� �������� key - ������ ��������
	}

	return *this;
}

template <class T> Array <T> Array <T>::DelPosNew(int index)
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
			b.a[i] = a[i + 1]; // ���������� ������� key
		else b.a[i] = a[i]; // ���� ��� �� ����� �� �������� key - ������ ��������
	}

	return b;
}

template <class T> ostream& operator<< (ostream& r, Array<T>& X) {
	for (int x = 0; x < X.n; x++)
		r << std::setw(4) << X.a[x];
	return r;
}

template <class T> ostream& operator>> (istream& r, Array<T>& X)
{
	cout << "enter the number of elements: ";
	int m;    
	cin >> m;
	if (X.n != m)
	{
		delete[]X.a;
		X.a = new T[m];  X.n = m;
	}
	cout << "enter " << m << " elements of array: ";
	for (int i = 0; i < X.n; i++) 
		r >> X[i];
	return r;
}

template <class T> int Array<T>::Max()
{
	int max = INT_MIN;
	for (int i = 0; i < n; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}

template <class T> int Array<T>::Min()
{
	int min = INT_MAX;
	for (int i = 0; i < n; i++)
		if (a[i] < min)
			min = a[i];
	return min;
}

template <class T> void Array<T>::Sort()
{
	Quicksort(a, 0, n);
}

template <class T> void Array<T>::Quicksort(T *arr, int l, int r)
{
	if (l < r)
	{
		int piv = arr[r]; // ������� �������, � ������� ����� ���������� ���������
		int i = l - 1;

		for (int j = l; j < r; j++) // ���������� �� ������� �� ����� ������� �� ������ 
									// � ��������� ��� ���������� �������� ��������
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

		Array::Quicksort(arr, l, i); // ���������� ��������� ����� ����� �������
		Array::Quicksort(arr, i + 2, r); // ������ �����
	}
}

template <class T> Array<T>& Array<T>::operator= (const Array <T>& X)
{
	if (this != &X)
	{
		delete[]a;
		n = X.n;
		a = new T[n];
		for (int i = 0; i < n; i++)
			a[i] = X.a[i];
	}
	return *this;
}

template <class T> Array <T> Array <T>::operator+ (T key)
{
	Array b(n + 1); // ������� ������ � ���-��� ��-�� ������, ��� � �������� �� 1
	for (int i = 0; i < n; i++) // �������� ��� ��-� �� �������� ������� � �����
		b.a[i] = a[i];
	b.a[n] = key; // ��������� � ����� ����������� �������

	return b;
}

template <class T> Array <T> Array <T>::operator+ (Array <T> X)
{
	Array b(n + X.n); // ������� ������ � ���-��� ��-�� ������, ��� � �������� �� ���-�� ��������� ������� �������
	int i = 0;
	for (; i < n; i++) // �������� ��� ��-� �� �������� ������� � �����
		b.a[i] = a[i];
	for (int j = 0; i < b.n; i++, j++)
		b.a[i] = X.a[j];

	return b;
}

template <class T> Array <T>& Array <T>::operator+= (T key)
{
	Array dump(n);
	dump = *this;
	delete[]a;
	n += 1;
	a = new T[n];
	for (int i = 0; i < n - 1; i++)
		a[i] = dump.a[i];
	a[n - 1] = key;

	return *this;
}

template <class T> Array <T>& Array<T> ::operator+= (Array <T> X)
{
	Array dump(n);
	dump = *this;
	delete[]a;
	n += X.n;
	a = new T[n];
	int i = 0;
	for (; i < dump.n; i++)
		a[i] = dump.a[i];
	for (int j = 0; i < n; i++, j++)
		a[i] = X.a[j];

	return *this;
}

template <class T> Array <T> Array <T>::operator- (T key)
{
	Array b(n - 1);
	int index = FindKey(key);
	for (int i = 0; i < n; i++)
	{
		if (i >= index)
			b.a[i] = a[i + 1]; // ���������� ������� key
		else b.a[i] = a[i]; // ���� ��� �� ����� �� �������� key - ������ ��������
	}

	return b;
}

template <class T> Array <T>& Array <T>:: operator-= (T key)
{
	int index = FindKey(key);
	if (index == -1)
		return *this;
	Array dump(*this);
	delete[]a;
	n -= 1;
	a = new T[n];
	for (int i = 0; i < n; i++)
	{
		if (i >= index)
			a[i] = dump.a[i + 1]; // ���������� ������� key
		else a[i] = dump.a[i]; // ���� ��� �� ����� �� �������� key - ������ ��������
	}

	return *this;
}

template <class T> T& Array<T>::operator[] (int k)
{
	try {
		if (k < 0 || k >= n) {
			throw("Incorrect index");
		}
	}
	catch (char* s) {
		cout << "Error: " << s << endl;

	}
	catch (...) {
		cout << "Error: unknown index" << endl;
	}
	return a[k];
}

template <class T> bool Array<T>::operator== (Array <T> X)
{
	if (n != X.n)
		return false;
	for (int i = 0; i < n; i++)
		if (a[i] != X.a[i])
			return false;
	return true;
}

template <class T> bool Array<T> ::operator!= (Array <T> X) {
	return !(*this == X);
}

template <class T> int Array<T>::GetN()
{
	return n;
}