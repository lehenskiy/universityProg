#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
struct Trailer;

struct Lider
{
	int key;		// Номер вершины
	int count;		// Число предшественников число входящих дуг
	Lider   *nx;	// Указатель на следующий элемент в списке вершин
	Trailer *tr;	// указатель на Т список указателей на вершины к которым ведут исходящие дуги
};

struct Trailer
{
	Lider   *ld;	// указатель на вершину в списке к которой ведет
					// исходящая дуга из вершины к которой прикреплен
	Trailer *nx;	// указатель на следующий элемент
};

/*
 * AddEdge ­добавление ребра в граф
 * Входные параметры:
 * vertexes - список вершин графа
 * (vertexA,vertexB) Ребро графа определяется парой вершин
 */

void AddEdge(Lider *& vertexes, int vertexA, int vertexB) {
	Lider *ptrA = NULL, *ptrB = NULL;
	for (ptrA = vertexes; ptrA && ptrA->key != vertexA; ptrA = ptrA->nx); // перебираем вершины, пока не дойдем
	for (ptrB = vertexes; ptrB && ptrB->key != vertexB; ptrB = ptrB->nx); // до последней
	bool setEdge = true;
	
	if (ptrA && ptrB) { // если обе вершины уже были добавлены в граф
		Trailer * trTmp = ptrA->tr;
		for (Trailer * trTmp = ptrA->tr; trTmp && trTmp->ld != ptrB; trTmp = trTmp->nx); // если мы уже приходили в эту вершину
		setEdge = (bool)trTmp;  // (не) устанавливаем ребро
	}
	else {
		// vertexes Создаем вершину А добавляем в голову списка
		if (!ptrA) {
			ptrA = new Lider;
			ptrA->key = vertexA;
			ptrA->count = 0;
			ptrA->nx = NULL;
			ptrA->tr = NULL;
			ptrA->nx = vertexes;
			vertexes = ptrA;
		}
		// Создаем вершину добавляем в голову списка
		if (!ptrB) {
			ptrB = new Lider;
			ptrB->key = vertexB;
			ptrB->count = 0;
			ptrB->nx = NULL;
			ptrB->tr = NULL;
			ptrB->nx = vertexes;
			vertexes = ptrB;
		}

	}
	//     Устанавливаем ребро
	if (setEdge) {
		ptrB->count++; // увеличиваем число предшественников
		Trailer* elemTr = new Trailer;
		elemTr->ld = ptrB;
		elemTr->nx = ptrA->tr;
		ptrA->tr = elemTr; // заносим ребро в список ребер, исходящих из А
	}
}

/*
 * PrintGraph - Вывод графа
 * Входные параметры:
 * vertexes - список вершин графа
 */

void PrintGraph(Lider*vertexes) {
	if (vertexes == NULL)
		printf("Graph is Empty");
	else
		while (vertexes) { // проход по вершинам
			Trailer* trTmp = vertexes->tr;
			while (trTmp) { // проход по ребрам
				printf("(%d,%d)\n", vertexes->key, trTmp->ld->key);
				trTmp = trTmp->nx;
			}
			vertexes = vertexes->nx; // идем к следующей вершине
		}
}

/*
 * DeleteGraph - удаление графа
 * Входные параметры:
 * vertexes - список вершин графа
 */

void DeleteGraph(Lider*&vertexes) {
	while (vertexes) { // пока есть вершины
		while (vertexes->tr) { // удаляем ребра, исходящие из нее
			Trailer*tmp = vertexes->tr; // удаляем ребро
			vertexes->tr = vertexes->tr->nx; // переходим к следующему
			delete tmp;
		}
		Lider*tmp = vertexes; // удаляем вершину
		vertexes = vertexes->nx; // переходим к следующей вершине
		delete tmp;
	}

}

/*
 * ExcludeEdge - Функция удаления ребра из графа
 * Входные пареметры:
 * vertexes ­- список вершин графа
 * Ребро графа определяется парой вершин
 * Возвращаемое значение:
 * true - ребро удалено
 * false - ребро не удалено
 */

bool ExcludeEdge(Lider *& vertexes, int vertexA, int vertexB) {
	Lider *ptrA = NULL, *ptrB = NULL;
	for (ptrA = vertexes; ptrA && ptrA->key != vertexA; ptrA = ptrA->nx);
	for (ptrB = vertexes; ptrB && ptrB->key != vertexB; ptrB = ptrB->nx);
	if (ptrA && ptrA->tr && ptrB) { // существуют ли эти вершины и ребро от ptrA
		if (ptrA->tr->ld == ptrB) { // ведет ли ребро от ptrA к вершине ptrB
			Trailer * t = ptrA->tr;
			ptrA->tr = ptrA->tr->nx; // удаляем ребро
			delete t;
			ptrB->count--; // уменьшаем счетчик предшественников
		}
		else {
			Trailer * trTmp;
			for (trTmp = ptrA->tr; trTmp->nx && trTmp->nx->ld != ptrB; trTmp = trTmp->nx); // поиск вершины ptrB для ребра
			if (trTmp->nx) {
				Trailer * t = trTmp->nx;
				trTmp->nx = trTmp->nx->nx; // удаляем ребро
				delete t;
				ptrB->count--; // уменьшаем счетчик предшественников
			}
		}
		return true;
	}
	return false;
}

/*
 * Исходный граф хранится в файле graph.dat
 * списком ребер, например:
 * 1 2
 * 1 3
 * 1 5
 * 4 5
 * 2 4
 */

int main(int argc, char** argv) { // аргументы для запуска из командной строки (количество аргументов и массив аргументов)

	FILE*graphInFile = fopen("graph.dat", "r"); // чтение файла
	Lider *graph = NULL;
	int vertexA = 0, vertexB = 0;
	int k = 0;
	if (graphInFile)
	{
		while (k = fscanf(graphInFile, "%d%d", &vertexA, &vertexB) > 0) {
			printf("(%d,%d)\n", vertexA, vertexB);
			AddEdge(graph, vertexA, vertexB); // добавляем ребра в граф, если они не образуют цикл
		}

		fclose(graphInFile);
		puts("\nPrint Graph \n");
		PrintGraph(graph);
		printf("\n");
		ExcludeEdge(graph, 1, 5);
		ExcludeEdge(graph, 4, 5);
		ExcludeEdge(graph, 5, 3);
		printf("\n");
		PrintGraph(graph);
		printf("\n");
		DeleteGraph(graph);
		PrintGraph(graph);
	}
	else
		puts("File is not open");
	return 0;
}