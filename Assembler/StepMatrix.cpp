#include <iostream>
using namespace std;

int main()
{
	const int N = 3;	// кол-во строк
	const int M = 4;	// кол-во столбцов
	int arr[N][M];
	int isStep = 1;

	cout << "Enter matrix(3x4): " << endl; // записываем массив 
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> arr[i][j];

	cout << endl << "Matrix: " << endl; // выводим массив
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}
	cout << endl;

/*
0 2 3 0
0 0 -1 1
0 0 0 3 
*/

	_asm
	{
		lea	  esi, [arr]		; ESI - адрес начала строки
		mov   ecx, 0			; ECX - текущая строка
		mov   ebx, 0			; EBX - номер крайнего левого ненулевого элемента строки

		L1:						; проход по столбцам
		mov   edi, 0			; EDI - смещение столбца
		mov   eax, 0			; EAX - текущий столбец

		L2: 
		mov	  edx, [esi + edi]	; EDX - текущий элемент массива
		cmp   edx, 0
		je    L3				; Если текущий элемент равен 0, идем дальше
		cmp   eax, ebx			; Если нет - проверяем условие ступенчатой матрицы
								; (текущий крайний левый ненулевой элемент правее такового на предыдущей строке)

		jg	L4					; переходим к следующей строке
		jmp BREAK_PROG			; возвращаем false

		L3:
		add   edi, 4		; Переход к следующему столбцу(смещение на 4 байта)
		inc   eax				
		cmp   eax, M
		jne   L2				; Если EAX не равно M, то проверяем дальше
								; (если нет - идём к следующей строке)

		L4:						; проход по строкам
		mov   ebx, eax			; Записываем новый крайний левый ненулевой элемент из текущей строки
		mov   eax, M			; Загружаем в EAX количество элементов в строке
		imul  eax, 4			; Умножаем количество элементов в строке на размер элемента
		add   esi, eax			; Прибавляем к смещению полученный размер строки
		inc   ecx				; Увеличиваем на 1 счётчик строк
		cmp   ecx, N			; Сравниваем ECX с N
		jne   L1				; Если ECX не равно N, то переходим к началу цикла
		jmp   EXIT_PROG			; Если нет - выходим из программы
		
		BREAK_PROG: 
		mov isStep, 0

		EXIT_PROG:
	}

	if (isStep)
		cout << "Matrix is step";
	else cout << "Matrix is not step";

	return 0;
}