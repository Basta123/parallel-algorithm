#pragma once


using namespace std;


extern const char* EXTERNAL_FILE;   // внеший файл для экспорта и импорта дерева


struct pthreadArg {
    struct tnode *tree;
    int threadCount;

};

/* Прототипы функций */
tnode* makeRandomTree(unsigned long long &MyCountElems);


unsigned long long getSumOfAllChilds(tnode* tree);
unsigned long long getSumOfAllChilds_OpenMP(tnode* tree, int num_thrds);




/* Структура бинарного дерева*/
struct tnode
{
    unsigned long long value = 0;   // числовое значение
    unsigned long long sum = 0;	// сумма значений дочерних узлов
    struct tnode *left = NULL;	// левый потомок
    struct tnode *right =NULL;	// правый потомок
};

/* Добавить узел */
tnode* addNode(unsigned long long v, tnode *tree, unsigned long long &MyCountElems);