#pragma once
#include <iostream>

using namespace std;

class List;

class Node
{
	int key;
	Node *prev, *next;

public:
	Node(int k = 0, Node *pr = 0, Node *nxt = 0)
	{ key = k; prev = pr; next = nxt; }

	int& Key() { return key; }
	Node*& Prev() { return prev; }
	Node*& Next() { return next; }
	friend class List;
};

class List
{
	Node *head, *tail;

public:

	List();
	List(int n);  	    			// Формирование списка из n случайных чисел
	List(int *a, int n);			// Формирование списка из массива n чисел
	List(const List &s);			// Конструктор копирования
	~List();
	List & operator= (const List &s);

	void AddAfter(int x, Node *pr); // Добавление узла после заданного
	void AddToTail(int x); 			// Добавление элемента в хвост
	void AddToHead(int x);     		// Добавление элемента в голову
	void AddToTail(List S);      	// Добавление списка в хвост
	void AddToHead(List S);   		// Добавление списка в голову

	void Del(Node *p);     			// Удаление элемента по указателю p
	void DelTail();             	// Удаление элемента с хвоста
	void DelHead();           		// Удаление элемента с головы

	Node *FindKey(int key);    		// Поиск в списке по ключу
	Node *FindPos(int pos);     	// Поиск в списке по позиции

	bool Empty();                   // Проверка пустоты списка
	bool NotEmpty();        	    // Проверка непустоты списка
	void Clear();               	// Очистка списка

	bool operator== (List S);    	// Проверка равенства списков
	bool operator!= (List S);     	// Проверка неравенства списков

	Node *Max();					// Нахождение max эл-та списка
	Node *Min();                    // Нахождение min эл-та списка
	void Sort();         	    	// Сортировка (методом прямой вставки)

	void Scan(int n);               // Ввод списка из n элементов
	void Print();                   // Печать списка

	friend ostream & operator<< (ostream &r, List &X);
	friend istream & operator>> (istream &r, List &X);
};