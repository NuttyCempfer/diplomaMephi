#ifndef MAINMENU_H
#define MAINMENU_H
#include <stdio.h>
#include <string.h>

char * textmenu[]={
	"0 - Exit",
	"1 - Item1",
	"2 - Item2",
	"3 - Item3",
	"4 - Item4",
	"5 - Item5"
};

int N=sizeof(textmenu)/sizeof(textmenu[0]);

int getMenuItem(char * [], int);

#endif
