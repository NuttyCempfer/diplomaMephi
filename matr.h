#ifndef MATR_H
#define MATR_H

struct Matr{
    int N;
    int M;
    double * A;
};

struct Matr InsertMatr();
void FreeMatr(struct Matr a);
void PrintMatr(struct Matr a);
#endif
