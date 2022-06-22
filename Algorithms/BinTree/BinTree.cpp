#include <iostream>
#include <queue>
#include <ctime>
#include "BinTree.h"

using namespace std;



Node* BinTree::Tree(int n, Node* p)		// ���������� �������� ����������������� ������ � ������� ��������
{										//  n - ���������� ������, p - ������ ������� ������
	if (n == 0) return NULL;
	Node* q = new Node(rand() % 776);
	int nL, nR;
	nL = (n - 1) / 2; nR = n - nL -1;
	q->left = Tree(nL, q);
	q->right = Tree(nR, q);
	q->parent = p;
	return q;
}

BinTree::BinTree(int n)			// n - ���������� ������, ��� ���� ������ �� ��� ������������ ��������� �������
{
	root = Tree(n, NULL);
}

int BinTree::Function(Node* root, int* Array,int m, int n)	// ��������������� ������� ��� BinTree
{
	if (root == 0) return m;
	root->key = Array[m];
	m++;
	m = Function(root->left, Array, m, n - 1);
	m = Function(root->right, Array, m, n - 1);
	return m;
}

BinTree::BinTree(int* a, int n)		// a - ������ ������,  n - ���������� ������
{
	Function(root, a, 0, n);
}

void BinTree::Copy(Node* q, Node* p, int f)	// ������� �����������, q - ������, p - ����, � �������� �������������� �����
{											//  ��� ���� f �������� �� ��, ����� �� ���� �������� ����� ���������� ������
	if (q == NULL) return;					//	f = 0 => ����� �������
	Node* t = new Node(q->key);				//	f = 1 => ������ �������
	t->parent = p;
	if (f == 0) p->left = t;
	else p->right = t;
	Copy(q->left, t, 0);
	Copy(q->right, t, 1);
}

BinTree::BinTree(const BinTree& T)
{
	if (T.root == NULL) root = NULL;
	else 
	{
		root = new Node(T.root->key);
		Copy(T.root->left, root, 0);
		Copy(T.root->right, root, 1);
	}
}

BinTree& BinTree::operator=(const BinTree& T)
{
	if (this != &T)
	{
		Clear();
		DelRoot();
		if (T.root == NULL) root = NULL;
		else
		{
			root = new Node(T.root->key);
			Copy(T.root->left, root, 0);
			Copy(T.root->right, root, 1);
		}
	}
		return *this;
}

BinTree::~BinTree()		// ����������
{
	Clear();
	DelRoot();
}

void BinTree::Add(int k, Node* p)	// ���������� ���� � ��������� k � ������ � ������ p
{
	if (p == NULL)
		return;
	if (p->left == NULL)
	{
		Node* q = new Node(k);
		p->left = q;  q->parent = p;
		return;
	}
	if (p->right == NULL)
	{
		Node* q = new Node(k);
		p->right = q;  q->parent = p;
		return;
	}
	if (rand() % 2) Add(k, p->left);
	else Add(k, p->right);
}

void BinTree::Del(Node* p)	
{
	if (p == root) 
	{ 
		DelRoot(); 
		return; 
	}
	Node* q = p->parent; // �������� ���� p

	if ((p->left == NULL) && (p->right == NULL)) // �������� �����
	{
		if (q->left == p) q->left = NULL;
		else q->right = NULL;
		delete p;
		return;
	}
	
	if (p->left == NULL && p->right != NULL) //� p ��� ����� �����
	{
		if (q->left == p) q->left = p->right;
		else q->right = p->right;
		p->right->parent = q;
		delete p;
		return;
	}
	
	if (p->left != NULL && p->right == NULL) //� p ��� ������ �����
	{
		if (q->left == p) q->left = p->left;
		else q->right = p->left;
		p->left->parent = q;
		delete p;
		return;
	}

	//� p ���� ��� ���������
	Node* t = p;
	while (t->left != 0) 
		t = t->left;

	//�������� t �� ������
	if (t->right == NULL)
		t->parent->left = NULL;
	else 
	{
		t->parent->left = t->right;
		t->right->parent = t->parent;
	}
	
	//�������� p ����� t
	t->left = p->left;
	t->right = p->right;
	t->parent = q;

	if (q->left == p) q->left = t;
	else q->right = t;

	if (p->left != NULL)
		p->left->parent = t;

	p->right->parent = t;
	delete p;
	return;
}

void BinTree::DelRoot()	// �������� �����
{
	if ((root == NULL) || ((root->left == NULL) && (root->right == NULL)))
	{
		delete root;
		root = NULL;
		return;
	}
	if ((root->left != NULL) && (root->right == NULL))
	{
		Node* q = root;
		root = root->left;
		delete q;
		return;
	}
	if ((root->left == NULL) && (root->right != NULL))
	{
		Node* q = root;
		root = root->right;
		delete q;
		return;
	}
	if ((root->left != NULL) && (root->right != NULL))
	{
		Node* v = root;
		while (v->left != NULL)
			v = v->left;
		if (v->right == NULL)
			v->parent->left = NULL;
		else 
		{
			v->parent->left = v->right;
			v->right->parent = v->parent;
		}

		root->key = v->key;
		delete v;
		return;
	}
}

void BinTree::TreeTraversalLCR(Node* p)// ����� ������ � ������ p � ������� �� �������� ����-������-�����
{
	if (p == NULL) return;
	TreeTraversalLCR(p->left);
	cout << p->key << ' ';
	TreeTraversalLCR(p->right);
}

void BinTree::TreeTraversalRCL(Node* p)// ����� ������ � ������ p � ������� �� �������� �����-������-����
{
	if (p == NULL) return;
	TreeTraversalRCL(p->right);
	std::cout << p->key << " ";
	TreeTraversalRCL(p->left);
}

void BinTree::TreeTraversalLRC(Node* p)// ����� ������ � ������ p � ������� �� �������� ����-�����-������
{
	if (p == NULL) return;
	TreeTraversalLRC(p->left);
	TreeTraversalLRC(p->right);
	cout << p->key << ' ';
}

void BinTree::TreeTraversalRLC(Node* p)// ����� ������ � ������ p � ������� �� �������� �����-����-������
{
	if (p == NULL) return;
	TreeTraversalRLC(p->right);
	TreeTraversalRLC(p->left);
	cout << p->key << ' ';
}

void BinTree::TreeTraversalCLR(Node* p)// ����� ������ � ������ p � ������� �� �������� ������-����-�����
{
	if (p == NULL) return;
	cout << p->key << " ";
	TreeTraversalCLR(p->left);
	TreeTraversalCLR(p->right);
}

void BinTree::WidthTraversal(Node* p)// ����� ������ � ������ p � ������
{
	if (p == NULL) return;
	queue <Node*> Q;
	Q.push(p);			 // ��������� ������� � ����� queue
	while (Q.size() != 0) // ���� ������� �� �����
	{
		Node* z = Q.front(); //���������� ������ �� ������ ������� � ������
		Q.pop();			  // ������� ������� �� ������
		cout << z->key << " ";
		if (z->left) Q.push(z->left);
		if (z->right) Q.push(z->right);
	}
}

Node* BinTree::FindKey(int k, Node* p)// ����� ������� � ��������� k � ������ � ������ p
{
	if (p == NULL) return NULL;
	if (p->key == k) return p;
	Node* FindLeft = FindKey(k, p->left);
	Node* FindRight = FindKey(k, p->right);
	if (FindLeft != NULL)
		return FindLeft;
	if (FindRight != NULL)
		return FindRight;
	return NULL;
}

Node* BinTree::FindMax(Node* p)// ����� ���������� ������� � ������ � ������ p
{
	if (p == NULL) return NULL;
	if ((p->left == NULL) && (p->right == NULL)) return p;
	Node* LMax = FindMax(p->left), * RMax = FindMax(p->right), * Max = p;
	if ((LMax!=NULL) && (Max->key < LMax->key))
		Max = LMax;
	if ((RMax!=NULL)&& (Max->key < RMax->key))
		Max = RMax;
	return Max;
}

Node* BinTree::FindMin(Node* p)// ����� ���������� ������� � ������ � ������ p
{
	if (p == NULL) return NULL;
	if ((p->left == NULL) && (p->right == NULL)) return p;
	Node* LMin = FindMin(p->left), * RMin = FindMin(p->right), * Min = p;
	if (LMin!=NULL && Min->key > LMin->key)
		Min = LMin;
	if (RMin!=NULL && Min->key > RMin->key)
		Min = RMin;
	return Min;
}

int BinTree::FindHight(Node* p)// ����� ������ ������ � ������ p
{
	if (p == NULL) return 0;
	if ((p->left == NULL) && (p->right == NULL)) return 1;
	int HightL = 0, HightR = 0;
	if (p->left != NULL) HightL = FindHight(p->left);
	if (p->right != NULL) HightR = FindHight(p->right);
	int Hight;
	if (HightL > HightR)
		Hight = HightL;
	else Hight = HightR;
	return Hight + 1;
}

int BinTree::Count(Node* p)// ������� ���������� ������ � ������ � ������ p
{
	if (p == NULL) return 0;
	if ((p->left == NULL) && (p->right == NULL)) return 1;
	int CountL = 0, CountR = 0;
	if (p->left != NULL) CountL = Count(p->left);
	if (p->right != NULL) CountR = Count(p->right);
	return CountL + CountR + 1;
}

void BinTree::Clear()// �������� ������ (������ ��������)
{
	if (root == NULL) return;
	while (root->right != 0)
		Del(root->right);
	while (root->left != 0)
		Del(root->left);
}

void BinTree::PrintTree(Node* p, int k)// ����� ������ �� �������
{
	if (p == NULL) return;
	PrintTree(p->right, k + 6);
	for (int i = 0; i < k; i++) cout << ' ';
	cout << p->key << endl;
	PrintTree(p->left, k + 6);
}

int main()
{
	setlocale(LC_ALL, "RUS");
	cout << "������� ���������� ����� � ������: ";
	int amount;
	cin >> amount;
	BinTree Tree = BinTree(amount);
	
	cout << endl;
	Tree.PrintTree(Tree.GetRoot(), 7);
	
	BinTree TreeA = Tree;
	cout << "������������� ������: " << endl;
	TreeA.PrintTree(TreeA.GetRoot(), 7);
	
	BinTree TreeB;
	TreeB = Tree;
	cout << "�������������2 ������: " << endl;
	TreeB.PrintTree(TreeB.GetRoot(), 7);
	
	Node* Max = Tree.FindMax(Tree.GetRoot());
	cout << "Max �������: " << Max->GetKey() << endl;
	
	Node* Min = Tree.FindMin(Tree.GetRoot());
	cout << "Min �������: " << Min->GetKey() << endl;
	
	int n;
	cout << "������� ������� ��� ������: ";
	cin >> n;
	Node* Q = Tree.FindKey(n, Tree.GetRoot());
	if (Q == NULL)
		cout << "������� �� ������" << endl;
	else cout << "������� ������" << endl;
	
	int Hight = Tree.FindHight(Tree.GetRoot());
	cout << "������ ������: " << Hight << endl;
	
	int Uzel = Tree.Count(Tree.GetRoot());
	cout << "���-�� �����: " << Uzel << endl;
	
	cout << "���������� ��������: " << endl;
	Tree.Add(33, Tree.GetRoot());
	Tree.PrintTree(Tree.GetRoot(), 7);
	
	cout << "�������� ����: " << endl;
	Tree.Del(Tree.GetRoot());
	Tree.PrintTree(Tree.GetRoot(), 7);
	
	cout << "�������� ������:" << endl;
	Tree.Clear();
	Tree.PrintTree(Tree.GetRoot(), 7);
	
	cout << "�������� �����:" << endl;
	Tree.DelRoot();
	Tree.PrintTree(Tree.GetRoot(), 7);
}