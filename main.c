#include "parser.h"
#include "multy.h"
#include "determ.h"
#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainmenu.h"

int main(){
	int item;
	int i, j, m,n, k;
	double *matr;
	FILE *pars, *wpars;
	char * file_content,* fileIn,* fileOut;
	struct massiveSect * MS;
    struct Matr a, b, c;
	while (item=getMenuItem(textmenu,N)){
		switch(item){
			case -1:
				printf("Input/outpet error! \n");
				break;
			case 1:
				printf("Item1 \n");
    			a=InsertMatr(a);
   				PrintMatr(a);
    			printf("det= %f\n",DetMatr(a));
    			FreeMatr(a);
				break;
			case 2:
				printf("Item2 \n");
    			srand(time(NULL));
    			a=InsertMatr();
    			b=InsertMatr();
    			PrintMatr(a);
    			PrintMatr(b);
    			//âîçìîæíî ïîä c íàäî ïàìÿòü âûäåëèòü
    			c=MultiplyMatr(a,b);
    			PrintMatr(c);
    			freeMatr(a);
    			freeMatr(b);
    			freeMatr(c);
				break;
			case 3:
				printf("Item3 \n");
				break;
			case 4:
				printf("Item4 \n");
				break;
			case 5:
				printf("Item5 \n");
				if((pars=fopen(fileIn, "r"))==NULL)
				{
					printf("Не удалось открыть файл");
					return 1;
				}
				if((wpars=fopen(fileOut,"w"))==NULL)
				{
					printf("Не удалось открыть файл на запись \n");
					fclose(pars);
					return 1;
				}
				MS=OpenFile(pars);
				fclose(pars);
				//printSects(MS);
				WriteFile(wpars, MS);
				fclose(wpars);
				i=TypeDataMatrix("multiply","matrix2","size2",MS,&n,&m, &matr);
				printf("%d \n",i);
				printf("n=%d m=%d \n",n,m);
				for(i=0; i<n;i++){
					for(j=0; j<m; j++)
						printf("%f ",matr[i*m+j]);
					printf("\n");
				}
				free(matr);
				FreeMemory(MS);
				break;

		}
	}
	return 0;
}
