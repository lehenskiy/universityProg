#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <iostream>
using namespace std;
struct Trailer;

struct Lider
{
	int key, count;
	Lider *next;
	Trailer *tr;
	Lider();
	void ReduceCount();
	void IncreaseCount();
	void AddTrailer(Lider *p);
	void DelTrailer(Lider * p);
};

struct Trailer
{
	Lider *ptr;
	Trailer *next;
	Trailer() { ptr = NULL; next = NULL; }
};

struct Graph
{
	Lider *head;
	Graph() { head = new Lider; }
	~Graph() { Clear(); delete head; }
	Lider *FindKey(int k);
	void AddToHead(int k);
	void Del(Lider *p);
	void Clear();
	int FormGraph();
	void SortGraph(Graph&);
	bool Empty();
	Lider *FindCount(int k);
	void Exclude(Lider *p);
	void AddToTail(Lider *p);
};

Lider::Lider()
{
	key = count = 0;
	next = NULL;
	tr = NULL;
}

void Lider::ReduceCount()
{
	Trailer *t;
	t = tr;
	while (t != NULL)
	{
		t->ptr->count--;
		t = t->next;
	}
}

void Lider::IncreaseCount()
{
	Trailer *t;
	t = tr;
	while (t != NULL)
	{
		t->ptr->count++;
		t = t->next;
	}
}

void Lider::AddTrailer(Lider * p)
{
	Trailer *t;
	t = new Trailer;
	t->ptr = p;
	t->next = tr;
	tr = t;
}

void Lider::DelTrailer(Lider * p)
{
	Trailer*s, *t = p->tr;
	while (t != NULL)
	{
		s = t;
		p->tr = t->next;
		t = t->next;
		delete s;
	}
}

Lider * Graph::FindKey(int k)
{
	Lider* q = head;
	if (!Empty())
	{
		for (q = q->next; (q->next != NULL) && (q->key != k); q = q->next);
		if (q->key != k)
			return NULL;
		return q;
	}
	return NULL;
}

void Graph::AddToHead(int k)
{
	Lider*p;
	p = new Lider;
	p->key = k;
	p->next = head->next;
	head->next = p;
}

void Graph::Del(Lider * p)
{
	if (p->tr != NULL)
		p->DelTrailer(p);
	Lider *q = head;
	while (q->next != p)
		q = q->next;
	q->next = p->next;
	delete p;
}

void Graph::Clear()
{
	while (!Empty())
		Del(head->next);
}

int Graph::FormGraph()
{
	int n = 0, x, y;
	Lider *px, *py;
	cout << "Enter x, y: ";
	cin >> x >> y;
	while (x, y)
	{
		if (FindKey(x) == NULL)
		{
			AddToHead(x);
			px = head->next;
			n++;
		}
		else 
			px = FindKey(x);
		if (FindKey(y) == NULL)
		{
			AddToHead(y);
			py = head->next;
			n++;
		}
		else 
			py = FindKey(y);
		py->count++;
		px->AddTrailer(py);
		cout << "Enter x, y: ";
		cin >> x >> y;
	}
	return n;
}

void Graph::SortGraph(Graph & NewLD)
{
	Lider *p;
	while (!Empty())
	{
		p = FindCount(0);
		Exclude(p);
		NewLD.AddToTail(p);
		p->ReduceCount();
	}
	p = NewLD.head->next;
	while (p != NULL)
	{
		p->IncreaseCount();
		p = p->next;
	}
}

bool Graph::Empty()
{
	return (head->next == NULL);
}

Lider * Graph::FindCount(int k)
{
	Lider*p = head->next;
	if (!Empty())
	{
		for (; p != NULL && p->count != k; p = p->next);
		if (p->count == k)
			return p;
	}
	return NULL;
}

void Graph::Exclude(Lider * p)
{
	Lider *q = head;
	while (q->next != p)
		q = q->next;
	q->next = p->next;
}

void Graph::AddToTail(Lider * p)
{
	Lider* q = head;
	for (; q->next != NULL; q = q->next);
	q->next = p;
	p->next = NULL;
}

void main()
{
	char restart = 'y';
	while(restart == 'y')
	{	
		int n, *res;
		Graph LD, NewLD;
		n = LD.FormGraph();
		LD.SortGraph(NewLD);
		res = new int[n];
		Lider* p = NewLD.head->next;
		for (int i = 0; p != NULL; p = p->next, i++)
			res[i] = p->key;
		cout << "Result: ";
		for (int i = 0; i < n; i++)
			cout << res[i] << ' ';
		cout << endl << "Enter y to restart: " << endl;
		delete[]res;
		cin >> restart;
	}
}

/* 1st example:
1 4  
1 6
2 1
2 3
2 7
3 4
5 3
6 5 
7 8
8 5
9 4
9 5
9 6
0 0
y
1 2
1 5
1 7
2 6
3 9
4 2
4 8
5 3
7 4
8 3
8 6
9 6
8 9
0 0
n
*/