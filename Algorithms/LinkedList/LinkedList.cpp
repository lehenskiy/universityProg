#include "Header.h"
#include <ctime>

List::List() 
{
	head = new Node; // фиктивная голова
	tail = new Node(0, head, 0); // фиктивный хвост
	head->next = tail;
}

List::List(int m)
{
	srand(time(0));
	head = new Node;
	tail = new Node(0, head, 0);
	head->next = tail;
	for (int i = 0; i < m; i++)
	{
		int x = rand() % 1000 + 1;
		AddToTail(x);
	}
}

List::List(int* a, int n)
{
	head = new Node;
	tail = new Node(0, head, 0);
	head->next = tail;

	for (int i = 0; i < n; i++)
		AddToTail(a[i]);
}

List::List(const List& x)
{
	head = new Node;
	tail = new Node(0, head, 0);
	head->next = tail;

	Node* s = x.head->next;
	while (s != x.tail)
	{
		AddToTail(s->key);
		s = s->next;
	}
}

List::~List()
{
	Clear(); 
	delete head; 
	delete tail;
}


List& List::operator= (const List& x)
{
	if (this != &x)
	{
		Clear();
		Node* s = x.head->next;
		while (s != x.tail)
		{
			AddToTail(s->key);
			s = s->next;
		}
	}
	return *this;
}

bool List::operator==(List x) {
	Node* q1 = this->head->next, *q2 = x.head->next;
	if (q1 == this->tail && q2 == x.tail) 
		return true;

	while (q1 != this->tail && q2 != x.tail) { // итеративно проверяем равенство элементов
		if (q1->key != q2->key) 
			return false;
		q1 = q1->next;
		q2 = q2->next;
	}
	if (q1 == this->tail && q2 == x.tail) // дошли до конца и все эл-ты равны
		return true;
	return false; // один список длиннее другого
}

bool List::operator!=(List x) {
	return !(*this == x);
}

void List::AddAfter(int k, Node* pr)
{
	Node* q = new Node(k, pr, pr->next); // инициализируем новый элемент 
	pr->next = q;
	q->next->prev = q;
}

void List::AddToTail(int x)
{
	AddAfter(x, tail->prev);
}

void List::AddToHead(int x)
{
	AddAfter(x, head);
}

void List::AddToHead(List x) {
	Node* q = x.tail->prev; // идем с конца, так как таким образом 
							// список в обратном порядке получается
	while (q != x.head)
	{
		AddToHead(q->key);
		q = q->prev;
	}
}

void List::AddToTail(List x) {
	Node* q = x.head->next;
	while (q != x.tail)
	{
		AddToTail(q->key);
		q = q->next;
	}
}

void List::Del(Node* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
}

void List::DelTail()
{
	Del(tail->prev);
}

void List::DelHead()
{
	Del(head->next);
}

Node* List::FindKey(int x)
{
	Node* q = this->head->next;
	while (q != this->tail) { // просто линейный поиск
		if (q->key == x)
			return q;
		q = q->next;
	}
	// в идеале выкинуть исключение, но можно и так
	return NULL;
}

Node *List::FindPos(int pos)
{
	Node *q = this->head->next;
	int i = 0;
	while (q != this->tail && i < pos)
	{
		i++; 
		q = q->next;
	}
	if (i == pos && q != this->tail)
		return q;
	return NULL;
}

bool List::Empty()
{
	return (this->head->next == this->tail);
}

bool List::NotEmpty()
{
	return !(Empty());
}

Node* List::Max() 
{
	Node *M = NULL;
	Node *q = head->next;
	if (q == tail) {
		cout << "List is empty" << endl;
		return M;
	}
	M = q; q = q->next;
	while (q != tail) {
		if (q->key > M->key) {
			M = q;
		}
		q = q->next;
	}
	return M;
}

Node* List::Min() {
	Node *M = 0;
	Node *q = head->next;
	if (q == tail) {
		cout << "The list is empty" << endl;
		return M;
	}
	M = q; q = q->next;
	while (q != tail) {
		if (q->key < M->key)
			M = q;
		q = q->next;
	}
	return M;
}

void List::Clear()
{
	while (NotEmpty()) 
		DelHead();
}

void List::Sort()
{

	for (Node* i = head->next->next; i != tail; )
	{
		Node* j = i->prev; // сортировка вставками
		for (; j != head && j->key > i->key; j = j->prev);
		if (j != head) 
			AddAfter(i->key, j);
		else 
			AddToHead(i->key);
		i = i->next;
		Del(i->prev);
	}
}

void List::Print()
{
	Node* p = head->next;
	while (p != tail)
	{
		cout << p->key << ' ';
		p = p->next;
	}
	cout << endl;
}

void List::Scan(int n)
{
	Clear();
	int i, x;
	cout << "Enter elements: ";
	for (i = 0; i < n; i++)
	{
		cin >> x;
		AddToTail(x);
	}
}

ostream& operator<< (ostream &r, List &x)
{
	x.Print(); 
	return r;
}

istream& operator>> (istream &r, List &x) {
	int n; 
	cout << "Enter the number of elements: ";
	cin >> n;
	x.Scan(n);
	return r;
}

int main()
{
	// 1)
	List s1;
	s1.AddToHead(1);
	s1.AddToTail(10);
	cout << "s1: ";
	s1.Print();

	// 2)
	List s2(6);
	cout << "s2: " << s2;
	Node *max, *min;
	min = s2.Min();
	max = s2.Max();
	cout << "Min: " << min->Key() << endl;
	cout << "Max: " << max->Key() << endl;
	s2.Sort();
	cout << "Sorted s2: " << s2;

	// 3)
	Node* found = s2.FindPos(2);
	if (found != NULL)
	{
		cout << "Second element: " << found->Key() << endl;
		s2.Del(found);
		cout << "s2 without the second element: " << s2;
	}
	else
		cout << "There is no such position" << endl;

	// 4)
	found = s2.FindPos(6);
	if(found != NULL)
		cout << "Sixth element:" << found->Key() << endl;
	else
		cout << "There is no such position" << endl;
	s2.DelTail();
	cout << "s2 without tail: " << s2;

	// 5)
	List s3;
	s3 = s1;
	if (s1 == s3)
		cout << "s1 == s3";
	else
		cout << "s1 != s3";
	cout << endl;
	found = s3.FindKey(15);
	if (found != NULL)
		cout << found->Key() << endl;
	else
		cout << "There is no such element" << endl;

	// 6)
	s3.DelHead();
	found = s3.FindKey(10);
	if(found != NULL)
		s3.Del(found);
	cout << "s3: " << s3;
	if (s3.Empty())
		cout << "s3 is empty";
	else
		cout << "s3 is not empty";
	cout << endl;

	// 7)
	int mas[6];
	srand(time(0));
	for (int i = 0; i < 6; i++)
	{
		mas[i] = rand() % 20;
	}
	List s4(mas, 6);
	cout << "s4: " << s4;
	found = s4.FindKey(25);
	if (found != NULL)
		cout << found->Key() << endl;
	else
		cout << "There is no such element" << endl;
	found = s4.FindPos(3);
	s4.AddAfter(25, found);
	cout << "s4: " << s4;

	// 8)
	List s5(s2);
	cout << "s5: " << s5;
	found = s5.FindKey(4);
	if (found != NULL)
	{
		found = s5.FindKey(4);
		s5.Del(found);
		cout << "Key 4 deleted";
	}
	else
	{
		s5.AddToTail(4);
		cout << "Key 4 added";
	}
		
	cout << endl << s5;

	// 9)
	cout << "Enter s5: (11 12 13 14)" << endl;
	cin >> s5;
	if (s4 == s5)
		cout << "s4 == s5";
	else
		cout << "s4 != s5";
	cout << endl;

	// 10)
	s5.AddToTail(s4);
	s5.AddToHead(s1);
	cout << "s5: " << s5;
}