#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Параметр и значение
struct pair{
	char * key;
	char * value;
};
//[Секция]
struct section{
	int n;
	char * name;
	struct pair * set;
}; 
//Весь файл
struct massiveSect{
	int n;
	struct section * sects;
};
void FreeMemory (struct massiveSect *);
struct massiveSect * OpenFile(FILE *);
void printSects(struct massiveSect *); 
int WriteFile(FILE *, struct massiveSect *);
int TypeDataMatrix(char *, char *, char *, struct massiveSect *, int *, int *, double **);

#endif
