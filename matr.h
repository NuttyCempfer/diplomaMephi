#include <stdio.h>
#ifndef MATR_H
#define MATR_H

struct Matr{
    int N;
    int M;
    double * A;
};

struct Matr InsertMatr();
void FreeMatr(struct Matr);
void PrintMatr(struct Matr);
void FileOutput(struct Matr, FILE *);
#endif
