#pragma once
#include<iostream>

using namespace std;

class Node
{
	int key;
	Node* left, *right, *parent;

public:
	Node(int k = 0, Node* L = NULL, Node* R = NULL, Node* P = NULL)
	{
		key = k; left = L; right = R; parent = P;
	}
	int GetKey() { return key; }

	friend class BinTree;
};


class BinTree
{
	Node* root;

	Node* Tree(int n, Node* p); // ���������� �������� ����������������� ������ � n ���������, p - ������ ������� ������

	void Copy(Node* q, Node* p, int f);
	// ����������� ������ � ������ q, p - ����, � �������� �������������� �����
	// f=0 - ���������� ������ ����� ����� �������� ��� p;
	// f=1 - ���������� ������ ����� ������ �������� ��� p.

	int Function(Node* root, int* Array, int m, int n);

public:
	BinTree() { root = NULL; }
	BinTree(int n); 		// n - ���������� ������, ����� ��������
	BinTree(int* a, int n);	// a - ������ ������,  n - ���������� ������
							// ����������� ��������������� �-�
	BinTree(const BinTree&);
	BinTree& operator=(const BinTree&);
	~BinTree();

	void Add(int k, Node* p); 	// ���������� ���� � ������ k � ������ � ������ p
	void Del(Node* p); 		// �������� ���� p
	void DelRoot(); 			// �������� �����

	void TreeTraversalLCR(Node* p); // ����� ������ � ������ p, � ������� �� �������� ����-������-�����, ����� ��������� �� �������
	void TreeTraversalRCL(Node* p);	// ����� ������ � ������ p, � ������� �� �������� �����-������-����, ����� ��������� �� �������
	void TreeTraversalLRC(Node* p); // ����� ������ � ������ p, � ������� �� �������� ����-�����-������, ����� ��������� �� �������
	void TreeTraversalRLC(Node* p); // ����� ������ � ������ p, � ������� �� �������� �����-����-������, ����� ��������� �� �������
	void TreeTraversalCLR(Node* p); // ����� ������ � ������ p, � ������� �� �������� ������-����-�����, ����� ��������� �� �������
	void WidthTraversal(Node* p);	// ����� ������ � ������ p, � ������

	Node* FindKey(int k, Node* p);	// ����� ���� � ������ k � ������ � ������ p
	Node* FindMax(Node* p);			// ����� ���� � max ������ � ������ � ������ p
	Node* FindMin(Node* p);			// ����� ���� � min ������ � ������ � ������ p
	int FindHight(Node* p);			// ����� ������ ������ � ������ p
	int Count(Node* p);				// ���������� ���������� ����� � ������ � ������ p

	Node* GetRoot() { return root; }
	void Clear(); 					// ���������� ��� ������, ����� �����

	void PrintTree(Node* p, int k); // ����� ������ �� �������, k - ������ �� ����� ������� �������
};