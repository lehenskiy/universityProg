#include <iostream>
#include <locale.h>
#include <string.h>

using namespace std;
typedef unsigned char UC;

class BoolVector
{
	UC *bv;
	int n, m;    	//n -длина булева вектора, m - количество элементов в массиве bv
					   //связь n и m: m=n/8 если n%8=0;
					   //m=n/8+1, если n%8!=0

	int Input(const char *, int, int, int);		//формирование элемента массива bv
	void Output(int, int);                   		 //вывод элемента массива bv

public:

	// конструкторы, деструктор, перегрузка оператора присвоения
	BoolVector(int newN = 1);          			// n1 - длина булева вектора
	BoolVector(const char *s);
	BoolVector(const char *s, int n);			// strlen(s) != n
	BoolVector(const BoolVector &);
	BoolVector operator= (const BoolVector &);
	~BoolVector() { delete[]bv; }

	//ввод, вывод, вес, определение k-й компоненты
	void Scan(int);
	void Print();
	int Weight();
	UC operator[] (int);

	//сравнение
	bool operator== (BoolVector &);
	bool operator!= (BoolVector &);
	bool operator< (BoolVector &y);   	//x<y если x[i]<=y[i]
	bool operator> (BoolVector &y);		 //x>y если x[i]>=y[i]

   //побитовые операции
	BoolVector operator & (BoolVector &x);		//создается новый вектор
	BoolVector & operator &=(BoolVector &x);		//изменяется *this
	BoolVector operator |(BoolVector &x);			//создается новый вектор
	BoolVector & operator |=(BoolVector &x);		//изменяется *this
	BoolVector operator ^(BoolVector &x);			//создается новый вектор
	BoolVector & operator ^=(BoolVector &x);		//изменяется *this
	BoolVector operator ~();						//изменяется *this
	BoolVector operator <<(int);					//создается новый вектор
	BoolVector  & operator <<=(int);				//изменяется *this
	BoolVector operator >>(int);					//создается новый вектор
	BoolVector operator >>=(int);				//изменяется *this


	//Изменение одной компоненты вектора
	BoolVector SetUp1(int pos);        	//установить в 1 компоненту pos
	BoolVector SetUp0(int pos);        	//сбросить в 0 компоненту pos
	BoolVector Invert(int pos);           	//инвертировать компоненту pos

	//Изменение нескольких компонент вектора
	BoolVector SetUp1(int kol, int pos);
	//установить kol компонент начиная с позиции pos, изменяется *this
	BoolVector SetUp0(int kol, int pos);
	//сбросить  kol компонент начиная с позиции pos, изменяется *this
	BoolVector Invert(int kol, int pos);
	//инвертировать kol компонент начиная с позиции pos, изменяется *this

	friend ostream & operator<< (ostream &r, BoolVector &V);
	friend istream & operator>> (istream &r, BoolVector &V);

};

int BoolVector::Input(const char* str, int curBv, int strPos, int lenght)
{
	UC mask = 1;
	bv[curBv] = 0;
	for (int i = 0; i < lenght; i++, strPos++)
	{
		bv[curBv] <<= 1; // сдвигаем биты влево на 1 бит
		if (str[strPos] == '1') 
			bv[curBv] |= mask; // устанавливаем 1 в самый правый бит
	}
	return strPos;
}

void BoolVector::Output(int curBv, int lenght)
{
	UC mask = 1;
	mask <<= lenght - 1;
	for (int i = 0; i < lenght; i++)
	{
		if (bv[curBv] & mask) // проверка определенного бита, начиная с крайнего левого
		{
			cout << " " << '1';
		}
		else cout << " " << '0';
		mask >>= 1; // сдвиг вправо проверяемого бита
	}
}

BoolVector::BoolVector(int newN)
{
	n = newN;
	m = n / 8; 
	if(n % 8)
		m++;
	bv = new UC[m];
	for (int i = 0; i < m; i++) 
		bv[i] = 0;
}

BoolVector::BoolVector(const BoolVector& x)
{
	n = x.n;
	m = x.m;
	bv = new UC[m];
	for (int i = 0; i < m; i++)
		bv[i] = x.bv[i];
}

BoolVector::BoolVector(const char* s)
{
	n = strlen(s);
	int l = n % 8;
	m = n / 8; 
	if (l) 
		m++;
	bv = new UC[m];

	int strPos = 0, curBv = 0;
	if (l) { // если n % 8 != 0, заполняем только n % 8 бит
		strPos = Input(s, curBv, strPos, l);
		curBv++;
	}
	for (; curBv < m; curBv++) // остальные заполняем полностью
		strPos = Input(s, curBv, strPos, 8);
}

BoolVector::BoolVector(const char* s, int newN)
{
	int strLenght = strlen(s);
	n = newN;
	m = n / 8; int l = n % 8;
	if (l) 
		m++;
	bv = new UC[m];

	int curBv, strPos;
	if (strLenght >= n)
	{
		curBv = 0; strPos = strLenght - n; // откидываем первые (strlen - n) символов строки 
		if (l) {
			strPos = Input(s, curBv, strPos, l);
			curBv++;
		}
		for (; strPos < strLenght; curBv++) // остальные просто заполняем
			strPos = Input(s, curBv, strPos, 8);
	}
	else {
		int strM = strLenght / 8; int strL = strLenght % 8; strPos = 0;
		if (strL) 
			strM++;

		for (curBv = 0; curBv < m - strM; curBv++) { // первые элементы заполняем нулями
			bv[curBv] = 0;
		}
		if (strL) {
			strPos = Input(s, curBv, 0, strL);
			curBv++;
		}
		for (; strPos < strLenght; curBv++)
			strPos = Input(s, curBv, strPos, 8);
	}
}

BoolVector BoolVector::operator=(const BoolVector& x)
{
	if (this != &x)
	{
		if (m != x.m)
		{
			delete[]bv;
			m = x.m;
			bv = new UC[m];
		}
		for (int i = 0; i < m; i++)
			bv[i] = x.bv[i];
		n = x.n;
	}
	return *this;
}

BoolVector BoolVector::operator~()
{
	int i;
	for (i = 0; i < m; i++) // применям к каждому элементу отрицание
		bv[i] = ~bv[i];
	return *this;
}

void BoolVector::Scan(int newN)
{
	char* s; int newM, l;
	s = new char[newN];
	cin >> s;

	newM = newN / 8; l = newN % 8;
	if (l) 
		newM++;

	if (m != newM)
	{
		delete[]bv;
		m = newM;
		bv = new UC[m];
	}
	n = newN;
	int curBv = 0, strPos = 0;
	if (l)
	{
		strPos = Input(s, curBv, strPos, l);
		curBv++;
	}
	for (; strPos < n; curBv++)
		strPos = Input(s, curBv, strPos, 8);
}

void BoolVector::Print()
{
	int l = n % 8; int curBv = 0;
	if (l)
	{
		Output(0, l); curBv++;
	}
	for (; curBv < m; curBv++)
		Output(curBv, 8);
	cout << endl;
}

int BoolVector::Weight()
{
	int weight = 0;
	UC mask = 1;
	for (int i = 0; i < m; i++, mask = 1)
		for (mask <<= 7; mask != 0; mask >>= 1)
			if (bv[i] & mask)weight++; // сравниваем биты
	return weight;
}

UC BoolVector::operator[] (int i)
{
	int newM = i / 8, l = i % 8;
	UC mask = 1;
	mask <<= l;
	if (bv[m - newM - 1 ] & mask) 
		return '1';
	else 
		return '0';
}

bool BoolVector::operator== (BoolVector &x)
{
	if (n != x.n) 
		return false;
	for (int i = 0; i < m; i++)
		if (bv[i] != x.bv[i]) 
			return false;
	return true;
}

bool BoolVector::operator!= (BoolVector &x)
{
	if (*this == x)
		return false;
	else 
		return true;
}

bool BoolVector::operator< (BoolVector &x)
{
	if (n != x.n) 
		return false;
	for (int i = 0; i < m; i++)
		if (bv[i] >= x.bv[i]) 
			return false;
	return true;
}

bool BoolVector::operator> (BoolVector &x)
{
	if (n != x.n) 
		return false;
	for (int i = 0; i < m; i++)
		if (bv[i] <= x.bv[i]) 
			return false;
	return true;
}

BoolVector BoolVector::operator& (BoolVector &x)
{
	int newN = n, resBv = m - 1;
	if (newN > x.n) // устанавливаем m и n в сторону меньших значений других векторов
	{ 
		newN = x.n; 
		resBv = x.m - 1;
	}
	BoolVector Res(newN); // результирующий вектор
	int curBv, xBv;
	for (curBv = m - 1, xBv = x.m - 1; resBv >= 0; curBv--, xBv--, resBv--)
		Res.bv[resBv] = bv[curBv] & x.bv[xBv];
	return Res;
}

BoolVector& BoolVector::operator&= (BoolVector &x)
{
	BoolVector res;
	res = (*this & x);
	*this = res;
	return (*this);
}

BoolVector BoolVector::operator| (BoolVector& x)
{
	int newN = n, resBv = m - 1;
	if (x.n > newN)
	{
		newN = x.n;
		resBv = x.m - 1;
	}
	BoolVector res(newN);

	int curBv, xBv;
	for (curBv = m - 1, xBv = x.m - 1; ((curBv >= 0) && (xBv >= 0)); curBv--, xBv--, resBv--)
		res.bv[resBv] = bv[curBv] | x.bv[xBv];
	if (curBv >= 0)
		for (; resBv >= 0; resBv--, curBv--)
		{
			res.bv[resBv] = bv[curBv];
		}
	if (xBv >= 0)
		for (; resBv >= 0; resBv--, xBv--)
		{
			res.bv[resBv] = bv[xBv];
		}

	return res;
}

BoolVector& BoolVector::operator|= (BoolVector& x)
{
	BoolVector res;
	res = (*this | x);
	*this = res;
	return (*this);
}

BoolVector BoolVector::operator^ (BoolVector& x)
{
	int newN = n, resBv = m - 1;


	if (x.n > newN)
	{
		newN = x.n;
		resBv = x.m - 1;
	}
	BoolVector res(newN);

	int curBv, xBv;
	for (curBv = m - 1, xBv = x.m - 1; ((curBv >= 0) && (xBv >= 0)); curBv--, xBv--, resBv--)
		res.bv[resBv] = bv[curBv] ^ x.bv[xBv];
	if (curBv >= 0)
		for (; resBv >= 0; resBv--, curBv--)
		{
			res.bv[resBv] = bv[curBv];
		}
	if (xBv >= 0)
		for (; resBv >= 0; resBv--, xBv--)
		{
			res.bv[resBv] = bv[xBv];
		}

	return res;

}

BoolVector& BoolVector::operator^= (BoolVector& x)
{
	BoolVector res;
	res = (*this) ^ x;
	*this = res;
	return (*this);
}

BoolVector BoolVector::operator<< (int lenght)
{
	BoolVector res = (*this);
	if (lenght >= n) 
		for (int i = 0; i < m; i++) 
			bv[i] = 0;
	else {
		for (int i = n - 1; i >= lenght; i--) {
			if (res[i - lenght] == '1')
				res.SetUp1(i);
			else 
				res.SetUp0(i);
		}
	}
	res.SetUp0(lenght, 0);
	return res;
}

BoolVector& BoolVector::operator<<=(int lenght)
{
	BoolVector res = *this;
	res = res << lenght;
	*this = res;
	return *this;
}

BoolVector BoolVector::operator>>(int lenght)
{
	int temp = lenght;
	int i;
	for (i = 0; temp < n; i++, temp++)
	{
		if (operator[](temp) == '1')
		{
			this->SetUp1(i);
		}
		else
		{
			this->SetUp0(i);
		}
	}
	for (; i < n; i++)
	{
		this->SetUp0(i);
	}
	return *this;
}

BoolVector BoolVector::operator>>=(int lenght)
{
	BoolVector res = *this;
	res = res >> lenght;
	*this = res;
	return *this;
}

BoolVector BoolVector::SetUp1(int i)
{
	if (i < 0 || i >= n) 
		cout << "incorrect index" << endl;
	else {
		int m1 = i / 8, k = i % 8;
		UC mask = 1;  mask <<= k;
		bv[m - m1 - 1] |= mask;
	}
	return (*this);
}

BoolVector BoolVector::SetUp0(int i)
{
	if (i < 0 || i >= n) cout << "Incorrect index" << endl;
	else {
		int m1 = i / 8, k = i % 8;
		UC mask = 1;  mask <<= k;
		mask = ~(mask);
		bv[m - 1 - m1] &= mask;
	}
	return (*this);
}

BoolVector BoolVector::Invert(int i)
{
	if (i < 0 || i >= n) cout << "Incorrect index" << endl;
	else {
		int m1 = i / 8, k = i % 8;
		UC mask = 1;  mask <<= k;
		bv[m - 1 - m1] ^= mask;
	}
	return (*this);
}

BoolVector BoolVector::SetUp0(int col, int pos)
{
	for (int i = pos; (i < n) & (i < pos + col); i++) {
		SetUp0(i);
	}
	return *this;
}

BoolVector BoolVector::SetUp1(int col, int pos)
{
	for (int i = pos; (i < n) & (i < pos + col); i++) {
		SetUp1(i);
	}
	return *this;
}

BoolVector BoolVector::Invert(int col, int pos)
{
	for (int i = pos; (i < n) & (i < pos + col); i++) {
		Invert(i);
	}
	return *this;
}

istream& operator>> (istream& r, BoolVector& x)
{
	x.Scan(x.n); 
	return r;
}

ostream& operator<< (ostream& r, BoolVector& x)
{
	x.Print(); 
	return r;
}

void main()
{
	// 1)
	BoolVector B1, B2(10), B3("111011101110"), B4("111011101110", 10), B5("111011101110", 16);
	cout << "B1: " << B1 << endl;
	cout << "B2: " << B2 << endl;
	cout << "B3: " << B3 << endl;
	cout << "B4: " << B4 << endl;
	cout << "B5: " << B5 << endl;

	// 2)
	cout << "B3 weight: " << B3.Weight() << endl;
	cout << "B5 weight: " << B5.Weight() << endl;
	if (B3 == B5) {
		cout << "Vectors are equal" << endl;
	}
	else
		cout << "Vectors are not equal" << endl;

	// 3)
	BoolVector B6(B5);
	cout << "B5: " << B5 << endl;
	cout << "B6: " << B6 << endl;

	// 4)
	cout << "Enter B2(1001100111): ";
	cin >> B2;
	cout << "B2: " << B2 << endl;

	// 5)
	B1 = B2;
	cout << "B1 == B2" << B1 << endl;
	if (B1 == B2) {
		cout << "Vectors are equal" << endl;
	}
	else 
		cout << "Vectors are not equal" << endl;

	// 6)
	BoolVector V1, V2, V3;
	V1 = B1&B3, V2 = B1|B3, V3 = B1^B3;
	cout << "V1: " << V1 << endl;
	cout << "V2: " << V2 << endl;
	cout << "V3: " << V3 << endl;

	// 7)
	B1 &= B3;
	cout << "B1&=B3: " << B1 << endl;
	if (B1 == V1) {
		cout << "Vectors are equal" << endl;
	}
	else
		cout << "Vectors are not equal" << endl;

	// 8)
	B2 |= B3;
	cout << "B2|=B3: " << B2 << endl;
	if (B2 == V2) {
		cout << "Vectors are equal" << endl;
	}
	else
		cout << "Vectors are not equal" << endl;

	// 9)
	B1 = ~B1;
	cout << "B1 invert: " << B1 << endl;
	UC tmp = B1[4];
	cout << "B1[4]: " << tmp << endl;
	tmp = B1[5];
	cout << "B1[5]: " << tmp << endl;

	// 10)
	B1.SetUp1(11); 
	B1.SetUp0(7);
	B1.Invert(9);
	cout << B1 << endl;

	// 11)
	B1.SetUp1(3, 5);
	B1.Invert(3, 1);
	cout << B1 << endl;

	// 12)
	BoolVector V4 = B1 << 4;
	B1 >>= 4;
	cout << "V4: " << V4 << endl;
	cout << "B1: " << B1 << endl;
	if (V4 == B1) {
		cout << "Vectors are equal" << endl;
	}
	else
		cout << "Vectors are not equal" << endl;
}