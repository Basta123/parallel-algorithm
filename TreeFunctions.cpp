#include <ctime>
#include <fstream>
#include <omp.h>
#include "TreeFunctions.h"





tnode* makeRandomTree(unsigned long long &MyCountElems) {

    tnode* tree = new tnode;
    tree->value = 4294967295/2;

    srand(unsigned(time(NULL)));
    for (int i = 0; i < 10000000; i++) {
        unsigned long long random = rand();
        addNode(random, tree, MyCountElems);
    }

    printf("[+] Random tree generated\n");
    return tree;
}


/* Добавить узел */
tnode* addNode(unsigned long long v, tnode *tree, unsigned long long &MyCountElems)
{
    // Если дерева нет, то формируем корень
    if (tree == NULL)
    {
        tree = new tnode;		// память под узел
        tree->value = v;		// значение
        tree->sum = 0;			// сумма дочерних
        tree->left = NULL;		// ветви инициализируем пустотой
        tree->right = NULL;
        MyCountElems++;

    }
    else if (v < tree->value)	// условие добавление левого потомка
        tree->left = addNode(v, tree->left, MyCountElems);
    else if(v > tree->value)
        tree->right = addNode(v, tree->right,MyCountElems);
    return(tree);
}



unsigned long long getSumOfAllChilds(tnode* tree) {

    if (tree != NULL){
        unsigned long long leftSum = 0;
        unsigned long long rightSum = 0;

        if (tree->left != NULL) {
            tree->left->sum = getSumOfAllChilds(tree->left);
            leftSum = tree->left->sum + tree->left->value;
        }

        if (tree->right != NULL)
        {
            tree->right->sum = getSumOfAllChilds(tree->right);
            rightSum = tree->right->sum + tree->right->value;
        }

        return leftSum + rightSum;
    }
    return 0;
}

unsigned long long getSumOfAllChilds_OpenMP(tnode* tree, int num_thrds) {
    if (tree != NULL) {
        unsigned long long leftSum = 0;
        unsigned long long rightSum = 0;

        int activelevel = omp_get_active_level();
     //   printf("activeLevel : %i\n", activelevel);

        int maxlevel = omp_get_max_active_levels();
       // printf("MaxLevel : %i\n", maxlevel);

        if (omp_get_active_level() >= omp_get_max_active_levels())
            return getSumOfAllChilds(tree);

#pragma omp parallel default(none), shared(tree, leftSum, rightSum, num_thrds), num_threads(num_thrds)
        {
#pragma omp sections
            {
#pragma omp section
                {
                    // сумма вершин для левого поддерева
                    if (tree->left != NULL){
                        tree->left->sum = getSumOfAllChilds_OpenMP(tree->left, num_thrds);
                        leftSum = tree->left->sum + tree->left->value;

                    }
                }

#pragma omp section
                {
                    // сумма вершин для правого поддерева
                    if (tree->right != NULL){
                        tree->right->sum = getSumOfAllChilds_OpenMP(tree->right, num_thrds);
                        rightSum = tree->right->sum + tree->right->value;
                    }
                }
            }
        }

        return leftSum + rightSum;
    }

    return 0;
}




