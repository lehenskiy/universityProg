#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

class Usel
{
	int key, next;
public:
	Usel(int k = -1, int N = -1)
	{
		key = k; next = N;
	}
	void PrintUsel();
	friend class Hash;
};

class Hash
{
	int dim;  		//размер хеш-таблицы
	int p;			//хеш-функция: h=x%p
	Usel *TAB;

public:
	Hash();
	Hash(int a[], int n, int P); 	//n--размер массива a
								   //p=P
	~Hash();
	Hash(const Hash &);
	Hash & operator= (const Hash &);
	void Add(int k);	//добавление эл-та в хеш-таблицу
	Usel* Find(int k);
	void Del(int k);	//k -- ключ
	void Print();
};
