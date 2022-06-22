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
	List(int n);  	    			// ������������ ������ �� n ��������� �����
	List(int *a, int n);			// ������������ ������ �� ������� n �����
	List(const List &s);			// ����������� �����������
	~List();
	List & operator= (const List &s);

	void AddAfter(int x, Node *pr); // ���������� ���� ����� ���������
	void AddToTail(int x); 			// ���������� �������� � �����
	void AddToHead(int x);     		// ���������� �������� � ������
	void AddToTail(List S);      	// ���������� ������ � �����
	void AddToHead(List S);   		// ���������� ������ � ������

	void Del(Node *p);     			// �������� �������� �� ��������� p
	void DelTail();             	// �������� �������� � ������
	void DelHead();           		// �������� �������� � ������

	Node *FindKey(int key);    		// ����� � ������ �� �����
	Node *FindPos(int pos);     	// ����� � ������ �� �������

	bool Empty();                   // �������� ������� ������
	bool NotEmpty();        	    // �������� ��������� ������
	void Clear();               	// ������� ������

	bool operator== (List S);    	// �������� ��������� �������
	bool operator!= (List S);     	// �������� ����������� �������

	Node *Max();					// ���������� max ��-�� ������
	Node *Min();                    // ���������� min ��-�� ������
	void Sort();         	    	// ���������� (������� ������ �������)

	void Scan(int n);               // ���� ������ �� n ���������
	void Print();                   // ������ ������

	friend ostream & operator<< (ostream &r, List &X);
	friend istream & operator>> (istream &r, List &X);
};