#ifndef MAINMENU_H
#define MAINMENU_H
#include <stdio.h>
#include <string.h>

char * textmenu[]={
	"0 - Exit",
	"1 - Determinant", 
	"2 - Multiply",
	"3 - Determinant MPI",
	"4 - Multiply MPI",
	"5 - Save progress (?)"
};

int N=sizeof(textmenu)/sizeof(textmenu[0]);

int getMenuItem(char * [], int);

#endif
