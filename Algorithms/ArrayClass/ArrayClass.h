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
		Array(int *b, int m);		//m -число эл-тов в массиве b

		Array(const Array &);
		Array & operator= (const Array &);
		~Array();

		void Scan(int);
		void Fill();
		void Clear();
		void Print();      			//вывод массива на консоль

		int & operator [] (int);
		int FindKey(int);  			//поиск эл-та в массиве. Возвращает индекс 
									//эл-та или -1, если эл-т в массиве отсутствует
		Array & operator+= (int);	 	//добавляет эл-т в конец массива *this
		Array  operator+ (int el);		//создаем новый массив b=*this+key

		Array & operator+= (Array X);	//добавляет массив X в конец массива *this
		Array  operator+ (Array X);		//создаем новый массив b=*this+X

		Array & operator-= (int);		//удаляем эл-т из массива *this
		Array  operator- (int key);		//создаем новый массив без эл-та key

		Array DelPosEq(int);			//удаление эл-та с заданной позиции
								   //массива *this
		Array DelPosNew(int);			//создаем новый массив, удалив эл-т
								   //с заданной позиции массива *this

		bool operator== (const Array &);
		bool operator!= (const Array &);

		int Max(); 					//возвращает индекс max элемента
		int Min(); 					//возвращает индекс min элемента
		void Sort();  				//сортировка массива

		int GetN();
	private:
		void Quicksort(int *arr, int l, int r);
	};
}