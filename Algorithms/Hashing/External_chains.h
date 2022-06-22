#pragma once
#include <iostream>
#include <time.h>

using namespace std;

class Node
{
	int key;
	Node *next;
public:
	Node(int k = -1, Node *N = NULL)
	{
		key = k; next = N;
	}
	friend class List;
};

class List
{
	Node *head;
public:
	List() { head = NULL; }
	List(int a[], int n); 		 	//создание списка из массива
						   //эл-ты добавл€ютс€ в хвост
	List(int n);  		//создание списка случайных эл-тов, 
				   //эл-ты добавл€ютс€ в хвост
	~List();
	List(const List&);
	List & operator= (const List &);

	void AddToHead(int k);
	void AddToTail(int k);
	void AddAfter(int k, Node *pr);

	void Del(Node* p);
	void DelHead();
	void DelTail();
	void DelAfter(Node *pr);

	Node *FindKey(int k);
	//возвращает адрес предка узла с ключом key
	//если key нет -- возвращает NULL
	//head возвращаетс€ в двух случа€х!!
	Node *Findpos(int pos);
	//возвращает адрес предка
	//или NULL, если в списке <pos эл-тов
	bool Empty();
	void Clear();
	void PrintList();
};
