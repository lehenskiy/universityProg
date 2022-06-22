#include "Internal_chains.h"

using namespace std;

Hash::Hash()
{
	dim = 2; p = 2; TAB = new Usel[dim];
}

Hash::Hash(int a[], int n, int P)
{
	dim = n + 5; p = P;
	TAB = new Usel[dim];
	for (int i = 0; i < n; i++)
		Add(a[i]);
}

Hash::~Hash()
{
	delete[] TAB;
}

Hash::Hash(const Hash& T)
{
	dim = T.dim;
	p = T.p;
	TAB = new Usel[dim];
	for (int i = 0; i < dim; i++)
	{
		TAB[i].key = T.TAB[i].key;
		TAB[i].next = T.TAB[i].next;
	}
}

Hash& Hash::operator=(const Hash& T)
{
	dim = T.dim;
	p = T.p;
	delete[] TAB;
	TAB = new Usel[dim];
	for (int i = 0; i < dim; i++)
	{
		TAB[i].key = T.TAB[i].key;
		TAB[i].next = T.TAB[i].next;
	}
	return *this;
}

void Hash::Add(int k)
{
	int h = k % p;
	if (TAB[h].key == -1) TAB[h].key = k;
	else
	{
		int j;
		for (j = dim - 1; j >= 0; j--)
			if (TAB[j].key == -1)
			{
				TAB[j].key = k; break;
			}
		int t = h;
		while (TAB[t].next != -1) t = TAB[t].next;
		TAB[t].next = j;
	}
}

Usel* Hash::Find(int k)
{
	int h = k % p;
	while (TAB[h].next != -1 && TAB[h].key != k)h = TAB[h].next;
	if (TAB[h].key == k)return (TAB + h);
	return 0;

}

void Hash::Del(int k)
{
	Usel* temp = this->Find(k);
	if (temp == 0)
		return;
	if (temp->next != -1) {
		int nxt = temp->next;
		temp->key = TAB[temp->next].key;
		temp->next = TAB[temp->next].next;
		TAB[nxt].key = -1;
		TAB[nxt].next = -1;
	}
	else
	{
		temp->key = -1;
		temp->next = -1;
	}
	return;
}

void Hash::Print()
{
	cout << setw(4);
	for (int i = 0; i < dim; i++) cout << i << setw(4);
	cout << endl;
	for (int i = 0; i < dim; i++) cout << TAB[i].key << setw(4);
	cout << endl;
	for (int i = 0; i < dim; i++) cout << TAB[i].next << setw(4);
	cout << endl;


}

void Usel::PrintUsel()
{
	if (this == 0)return;
	cout << this->key;
	return;
}