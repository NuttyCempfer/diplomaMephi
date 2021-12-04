#include "parser.h"
#include "multy.h"
#include "determ.h"
#include "matr.h"
#include "mainmenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAMELEN 100

int main(int argc, char * argv[]){
	int item;
	int i, j, m,n, k;
	double *matr, det;
	FILE *pars, *wpars;
	char * file_content,* fileIn,* fileOut;
	char nameSect[NAMELEN], nameMatr[NAMELEN], nameSize[NAMELEN];
	struct massiveSect * MS;
    struct Matr a, b, c;
	if(argc==1 || argc>3){
		printf("Программа требует параметров \n");
		printf("Первый параметр - имя конфигурационного файла \n");
		printf("Второй параметр - имя файла вывода \n");
		printf("В случае отсутствия второго параметра - производится вывод на экран \n");
		return 1;
	}
	fileIn=argv[1];
	if(argc==3)
		fileOut=argv[2];
	else
		fileOut=NULL;
	if((pars=fopen(fileIn, "r"))==NULL)
	{
		printf("Не удалось открыть файл");
		return 1;
	}
	if(fileOut)
		if((wpars=fopen(fileOut,"w"))==NULL)
		{
			printf("Не удалось открыть файл на запись \n");
			fclose(pars);
			return 1;
		}
	MS=OpenFile(pars);
	fclose(pars);
	//printSects(MS);
	//WriteFile(wpars, MS);
	while (item=getMenuItem(textmenu,N)){
		switch(item){
			case -1:
				printf("Input/output error! \n");
				break;
			case 1:
				if(i=TypeDataMatrix("determinant","matrix","size",MS,&a)){
					printf("Error %d \n",i);
					break;
				}
				det=DetMatr(a);
				if(fileOut){
					fprintf(wpars,"\nИсходная матрица \n");
					FileOutput(a,wpars);
					fprintf(wpars,"\nDet=%f\n",det);
				}
				else{
					printf("Исходная матрица \n");
					PrintMatr(a);
    				printf("det= %f\n",DetMatr(a));
				}
    			FreeMatr(a);
				break;
			case 2:
				if(i=TypeDataMatrix("multiply","matrix1","size1",MS,&a)){
					printf("Error %d \n",i);
					break;
				}
				if(fileOut){
					fprintf(wpars,"\nИсходная матрица 1\n");
					FileOutput(a,wpars);
				}
				else{
					printf("Исходная матрица 1\n");
					PrintMatr(a);
				}
				if(i=TypeDataMatrix("multiply","matrix2","size2",MS,&b)){
					printf("Error %d \n",i);
					break;
				}
				if(fileOut){
					fprintf(wpars,"\nИсходная матрица 2\n");
					FileOutput(b,wpars);
				}
				else{
					printf("Исходная матрица 2\n");
					PrintMatr(b);
				}
				c=MultiplyMatr(a,b);
				if(fileOut){
					fprintf(wpars,"\nПроизведение матриц \n");
					FileOutput(c,wpars);
				}
				else{
					printf("Произведение матриц \n");
					PrintMatr(c);
				}
				FreeMatr(a);
    			FreeMatr(b);
    			FreeMatr(c);
				break;
			case 3:
				printf("Multiply MPI \n");
				break;
			case 4:
				printf("Determinant MPI \n");
				break;
		}
	}
	if(fileOut)
		fclose(wpars);
	FreeMemory(MS);
	return 0;
}
