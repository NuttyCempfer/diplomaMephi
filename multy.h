#ifndef MUTLY_H
#define MULTY_H
#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Matr InsertMatr();
struct Matr MultiplyMatr(struct Matr, struct Matr);
void PrintMatr(struct Matr);
void freeMatr(struct Matr);

#endif
