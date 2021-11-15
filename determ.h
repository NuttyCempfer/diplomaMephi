#ifndef DETERM_H
#define DETERM_H
#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Matr InsertMatr();
double DetMatr(struct Matr);
int PermutationMatr(int [], int);
void FreeMatr(struct Matr);
void PrintMatr(struct Matr);

#endif
