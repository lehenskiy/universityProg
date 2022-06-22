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
	List(int a[], int n); 		 	//�������� ������ �� �������
						   //��-�� ����������� � �����
	List(int n);  		//�������� ������ ��������� ��-���, 
				   //��-�� ����������� � �����
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
	//���������� ����� ������ ���� � ������ key
	//���� key ��� -- ���������� NULL
	//head ������������ � ���� �������!!
	Node *Findpos(int pos);
	//���������� ����� ������
	//��� NULL, ���� � ������ <pos ��-���
	bool Empty();
	void Clear();
	void PrintList();
};
