#include "External_chains.h"

using namespace std;

List::List(int a[], int n)
{

	head = new Node(a[0], 0);
	Node* current = head;
	for (int i = 1; i < n; i++)
	{
		Node* t = new Node(a[i], 0);
		current->next = t;
		current = current->next;
	}

}

List::List(int n)
{
	srand(time(0));
	int numb = rand() % 100;
	head = new Node(numb, 0);
	Node* current = head;
	for (int i = 1; i < n; i++)
	{
		numb = rand() % 100;
		Node* t = new Node(numb, 0);
		current->next = t;
		current = current->next;
	}
}

List::~List()
{
	Clear();
}

List::List(const List&T)
{
	Node* current = T.head->next;
	head = new Node(T.head->key, 0);
	Node* cur2 = head;
	while (current->next)
	{
		cur2->next = new Node(current->key, 0);
		cur2 = cur2->next;
		current = current->next;
	}
}

List& List::operator=(const List& T)
{
	Node* current = T.head->next;
	head = new Node(T.head->key, 0);
	Node* cur2 = head;
	while (current->next)
	{
		cur2->next = new Node(current->key, 0);
		cur2 = cur2->next;
		current = current->next;
	}
	return *this;
}

void List::AddToHead(int k)
{
	if (head == 0)
	{
		head->key = k;
		return;
	}
	Node* temp = new Node(k, head);
	head = temp;
}

void List::AddToTail(int k)
{
	if (head == 0)
	{
		head = new Node(k, 0);
		return;
	}
	Node* temp = head;
	while (temp->next)temp = temp->next;
	temp->next = new Node(k, 0);
}

void List::AddAfter(int k, Node* pr)
{
	Node* temp = head;
	while (temp != pr)temp = temp->next;
	Node* nod = new Node(k, temp->next);
	temp->next = nod;
}

void List::Del(Node* p)
{
	if (p == 0)
		return;
	Node* temp = head;
	if (temp == 0)
		return;
	if (p == temp) {
		head = head->next;
		delete temp;
		return;
	}
	while (temp && temp->next != p) temp = temp->next;
	if (temp == 0)
		return;
	if (temp->next == p)
	{
		Node* temp2 = temp->next;
		temp->next = temp2->next;
		delete temp2;
	}

}

void List::DelHead()
{
	if (head == 0)
		return;
	Node* temp = head;
	head = head->next;
	delete temp;
}

void List::DelTail()
{
	if (head == 0)return;
	Node* temp = head;
	Node* temp_prev = 0;

	while (temp->next) {
		temp_prev = temp;
		temp = temp->next;
	}
	if (temp_prev) 
		temp_prev->next = 0;
	delete temp;
}

void List::DelAfter(Node* pr)
{
	if (head == 0)return;
	Node* temp = head;
	while (temp != pr) 
		temp = temp->next;
	if (!temp->next)
		return;
	Node* temp2 = temp->next;
	temp->next = temp2->next;
	delete temp2;
}

Node* List::FindKey(int k)
{
	if (head == 0)return 0;
	Node* ans = 0;
	Node* temp = head;
	while (temp && temp->key != k)
		temp = temp->next;
	return temp;
}

Node* List::Findpos(int pos)
{
	if (head == 0)return 0;
	Node* temp = head;
	for (; pos > 1 && temp->next; pos--)
		temp = temp->next;
	if (temp->next)
		return temp;
	return 0;
}

bool List::Empty()
{
	return head;
}

void List::Clear()
{
	if (head == 0)return;
	while (head != 0)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}

}

void List::PrintList()
{
	if (head == 0)return;
	cout << head->key;
	Node* temp = head->next;
	while (temp != 0)
	{
		cout << " <-- " << temp->key;
		temp = temp->next;
	}
	cout << endl << endl;

}