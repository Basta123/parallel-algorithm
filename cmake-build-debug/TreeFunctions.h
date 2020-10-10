#pragma once

#include "Tree.h"

using namespace std;

/* Константы */
#define MAX_VALUE 0xFFFFFFFF        // 4 294 967 295 (максимальное значения для генерации)
#define GENERATE_COUNT 9999999   // количество генераций случайного числа
extern const char* EXTERNAL_FILE;   // внеший файл для экспорта и импорта дерева

#define SUCCESS 0
#define ERROR_CREATE_THREAD -1
#define ERROR_JOIN_THREAD   -2

struct pthreadArg {
    struct tnode *tree;
    int threadCount;
};

/* Прототипы функций */
tnode* makeRandomTree(unsigned long long &MyCountElems);
void exportTreeToFile(tnode* tree);
tnode* importTreeFromFile();
unsigned long long getCountOfFile();
unsigned long long getSumOfAllChilds(tnode* tree);
unsigned long long getSumOfAllChilds_OpenMP(tnode* tree);
void* getSumOfAllChilds_Pthread(void *args);

/* Структура бинарного дерева*/
struct tnode
{
    unsigned long long value = 0;   // числовое значение
    unsigned long long sum = 0;	// сумма значений дочерних узлов
    struct tnode *left = NULL;	// левый потомок
    struct tnode *right = NULL;	// правый потомок
};

/* Добавить узел */
tnode* addNode(unsigned long long v, tnode *tree, unsigned long long &MyCountElems);


