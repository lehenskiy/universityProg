#pragma once
#include <iostream>
#include <ostream>

using std::ostream;
using std::istream;

namespace ArrayClass {

	class Array
	{
		
	public:
		int *a, n;
		Array(int);
		Array(int *b, int m);		//m -����� ��-��� � ������� b

		Array(const Array &);
		Array & operator= (const Array &);
		~Array();

		void Scan(int);
		void Fill();
		void Clear();
		void Print();      			//����� ������� �� �������

		int & operator [] (int);
		int FindKey(int);  			//����� ��-�� � �������. ���������� ������ 
									//��-�� ��� -1, ���� ��-� � ������� �����������
		Array & operator+= (int);	 	//��������� ��-� � ����� ������� *this
		Array  operator+ (int el);		//������� ����� ������ b=*this+key

		Array & operator+= (Array X);	//��������� ������ X � ����� ������� *this
		Array  operator+ (Array X);		//������� ����� ������ b=*this+X

		Array & operator-= (int);		//������� ��-� �� ������� *this
		Array  operator- (int key);		//������� ����� ������ ��� ��-�� key

		Array DelPosEq(int);			//�������� ��-�� � �������� �������
								   //������� *this
		Array DelPosNew(int);			//������� ����� ������, ������ ��-�
								   //� �������� ������� ������� *this

		bool operator== (const Array &);
		bool operator!= (const Array &);

		int Max(); 					//���������� ������ max ��������
		int Min(); 					//���������� ������ min ��������
		void Sort();  				//���������� �������

		int GetN();
	private:
		void Quicksort(int *arr, int l, int r);
	};
}