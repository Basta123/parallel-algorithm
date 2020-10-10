#include <stdio.h>
#include <ctime>
#include <fstream>
#include <omp.h>
#include <math.h>
#include "TreeFunctions.h"

using namespace std;

unsigned long long MyCountElems = 0;

double startTime, endTime;    // временные засечки


int num_thrds;


void defaultSum(tnode * tree){

    startTime = omp_get_wtime();
    unsigned long long sum = getSumOfAllChilds(tree);
    endTime = omp_get_wtime();

    printf("[Default] Time: %lf\n", endTime - startTime);
    printf("[Default] Sum: %llu\n", sum);
}



void openMpSum(tnode * tree, int num_thrds){
    // tnode* tree = importTreeFromFile();



    printf("Mycount of elements: %llu\n", MyCountElems);

    omp_set_nested(1);
    omp_set_max_active_levels(10);

    startTime = omp_get_wtime();
    unsigned long long sum = getSumOfAllChilds_OpenMP(tree, num_thrds);

    endTime = omp_get_wtime();

    printf("[OpenMP] Time: %lf\n", endTime - startTime);
    printf("[OpenMP] Sum: %llu\n", sum);
}

int main(){

    tnode* tree = makeRandomTree(MyCountElems);

    defaultSum(tree);

    num_thrds = 4;
    openMpSum(tree, num_thrds);


    return 0;
}

