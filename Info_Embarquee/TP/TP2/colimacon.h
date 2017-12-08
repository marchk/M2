#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void fillR(int** tab, int cols, int* i,  int* j, int* val, int max);

void fillD(int** tab, int rows, int* i,  int* j, int* val, int max);

void fillL(int** tab, int cols, int* i,  int* j, int* val, int max);

void fillU(int** tab, int rows, int* i,  int* j, int* val, int max);

void affiche(int** tab, int rows, int cols);

void colimacon(int **tab, int rows, int cols);
