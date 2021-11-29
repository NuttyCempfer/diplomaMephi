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
	double *matr;
	FILE *pars, *wpars;
	char * file_content,* fileIn=argv[1],* fileOut;
	char nameSect[NAMELEN], nameMatr[NAMELEN], nameSize[NAMELEN];
	struct massiveSect * MS;
    struct Matr a, b, c;
	if((pars=fopen(fileIn, "r"))==NULL)
	{
		printf("Не удалось открыть файл");
		return 1;
	}
	//if((wpars=fopen(fileOut,"w"))==NULL)
	//{
	//	printf("Не удалось открыть файл на запись \n");
	//	fclose(pars);
	//	return 1;
	//}
	MS=OpenFile(pars);
	fclose(pars);
	//printSects(MS);
	//WriteFile(wpars, MS);
	//fclose(wpars);
	while (item=getMenuItem(textmenu,N)){
		switch(item){
			case -1:
				printf("Input/output error! \n");
				break;
			case 1:
				printf("Determinant \n");
				printf("Input name sector matr1 \n");
				scanf("%s",nameSect);
				printf("Input name matrix matr1 \n");
				scanf("%s",nameMatr);
				printf("Input name size matr1 \n");
				scanf("%s",nameSize);
				i=TypeDataMatrix(nameSect,nameMatr,nameSize,MS,&a);
				printf("%d \n",i);
				printf("n=%d m=%d \n",a.N,a.M);
				PrintMatr(a);
    			printf("det= %f\n",DetMatr(a));
    			FreeMatr(a);
				break;
			case 2:
				printf("Multiply \n");
    			
				printf("Input name sector matr1 \n");
				scanf("%s",nameSect);
				printf("Input name matrix matr1 \n");
				scanf("%s",nameMatr);
				printf("Input name size matr1 \n");
				scanf("%s",nameSize);
				i=TypeDataMatrix(nameSect,nameMatr,nameSize,MS,&a);
				printf("%d \n",i);
				printf("n=%d m=%d \n",a.N,a.M);			
				PrintMatr(a);

				printf("Input name sector matr2 \n");
				scanf("%s",nameSect);
				printf("Input name matrix matr2 \n");
				scanf("%s",nameMatr);
				printf("Input name size matr2 \n");
				scanf("%s",nameSize);
				i=TypeDataMatrix(nameSect,nameMatr,nameSize,MS,&b);
				printf("%d \n",i);
				printf("n=%d m=%d \n",b.N,b.M);
				PrintMatr(b);
    			c=MultiplyMatr(a,b);
				printf("n=%d m=%d \n",c.N,c.M);


				PrintMatr(c);
    			FreeMatr(a);
    			FreeMatr(b);
    			FreeMatr(c);
				break;
			case 3:
				printf("Item3 \n");
				break;
			case 4:
				printf("Item4 \n");
				break;
			case 5:
				printf("Save progress in file \n");
				break;

		}
	}
	FreeMemory(MS);
	return 0;
}
