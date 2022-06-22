#include <iostream>

using namespace std;

#define n 5	// строки
unsigned int a[n] = {
	0b10011,
	0b01011,
	0b10101,
	0b01011,
	0b10011
};

int main()
{
	
	cout << "Matrix:" << endl;
	for (int i = 0; i < n; i++) {
		for (unsigned j = unsigned(1) << (n - 1); j != 0; j >>= 1) {
			cout << ((a[i] & j) ? '1' : '0') << "	";
		}
		cout << endl;
	}

	//ввод k1
	cout << endl << "k1: ";
	unsigned inp = -1;
	while (inp >= n)
		cin >> inp;

	//веса столбцов
	unsigned char vesa[n] = { 0 };
	//временная переменная
	unsigned t = 0;
	//индекс столбца с минимальным весом
	uint8_t max_index = 0;
	_asm {
												; считаем веса всех столбцов
												; маска текущего столбца = 1 << (n - 1)
		mov esi, 1
		shl esi, n
		shr esi, 1
												
		mov t, 0							; храним счетчик прохода по столбцам в t

											; начинаем цикл горизонтального прохода
		mov ecx, n
	l1:
		push ecx					; толкаем счетчик внешнего на стек
		mov ecx, n					; начинаем цикл прохода снизу вверх
	l2:								; собираем смещение в edx
									; = (ecx - 1) * 4 (размер int)
		mov edx, ecx
		dec edx
		imul edx, 4
		mov ebx, a[edx]				; если а[текущая строка]
		and ebx, esi				; &маска столбца
		cmp ebx, 0
		je skip
		lea edx, [vesa]				; тогда вес текущего столбца++
		add edx, t
		inc[edx]
	skip:
		dec ecx						; следующая строка выше
		cmp ecx, 0					; если счетчик = 0
		jne l2						; то цикла по строкам сверху вниз
		pop ecx						; возвращаем счетчик прохода по столбцам
		shr esi, 1					; маска по стобцам >>= 1, т.е.следующий столбец
		inc t						; x - позиция++
		dec ecx
		cmp ecx, 0
		jne l1

									; веса столбцов посчитаны
									; находим индекс столбца с максимальным весом max_index
		mov ebx, 0
		mov bl, 0					; max = 0
		mov ecx, n					; начинаем цикл прохода по vesa[i]
	l3:
		lea edx, [vesa]				
		add edx, ecx                
		dec edx                         
		mov al, [edx]				; al = *edx
		cmp al, bl					; если vesa[ecx - 1] > max
		jb lessequals
		mov bl, al					; то max = w[ecx - 1]
		mov max_index, cl			;  max_index = ecx(текущий счетчик)
		dec max_index
		lessequals:
		dec ecx
		cmp ecx, 0
		jne l3

									; переставляем столбцы k1 и max_index
									; делаем маски для их столбцов
									; маска максимального столбца - eax,
									; маска столбца k1 - ebx
		mov eax, 1
		rol eax, n					; << (n
		ror eax, 1					; -1 - max_index)
		mov cl, max_index
		max_indexloop:				; делаем смещение вправо max_index раз
		ror eax, 1
		dec ecx;
		cmp ecx, 0;
		jne max_indexloop;

		mov ebx, 1					; ebx = 1
		rol ebx, n
		ror ebx, 1
		mov ecx, inp
	
	kloop: 
		ror ebx, 1
		dec ecx
		cmp ecx, 0
		jne kloop
									; маски построены
									; проходим по строкам
		mov ecx, n
	l4:
									; esi переводится в 1 если он 0 и наоборот если он 1
									; если результат текущего AND - а единица
									; это значит что при одиинаковых значениях
									; в столбцах k1 и max_index esi будет 0
									; и ничего менять не нужно
		mov esi, 0;
		mov edx, a[ecx * 4 - 4];
		and edx, eax				; если a[ecx - 1] & маска макс столбца
		cmp edx, 0					; больше ноля
		jbe firstiszero
		xor esi, 1					; то esi ^= 1
	firstiszero:
		mov edx, a[ecx * 4 - 4]
		and edx, ebx				; если a[ecx - 1] & маска столбца k1
		cmp edx, 0					; больше ноля
		jbe secondiszero
		xor esi, 1					; то esi ^= 1
	
	secondiszero:
		cmp esi, 1					; если esi = 1
		jne esizero
									; то значения не совпадают, поэтому
		mov edx, a[ecx * 4 - 4]
		xor edx, eax				; a[ecx - 1] ^= маска макс столбца
		mov a[ecx * 4 - 4], edx
		mov edx, a[ecx * 4 - 4]
		xor edx, ebx				; a[ecx - 1] ^= маска столбца k1
		mov a[ecx * 4 - 4], edx
	
	esizero:
		dec ecx
		cmp ecx, 0
		jne l4
	}

	cout << "max: " << (unsigned)max_index << endl;

	//измененный массив
	cout << "Changed matrix:" << endl;
	for (int i = 0; i < n; i++) {
		for (unsigned j = unsigned(1) << (n - 1); j != 0; j >>= 1) {
			cout << ((a[i] & j) ? '1' : '0') << "	";
		}
		cout << endl;
	}
}