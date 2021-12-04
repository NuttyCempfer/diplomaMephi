#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void FreeMatr(struct Matr a){
    free(a.A);
}

void PrintMatr(struct Matr a){
    int i,j;
    if(a.N==0 || a.M==0){
        printf("Matrix is empty! \n");
        return;
    }
	printf("n=%d m=%d \n",a.N,a.M);			
    for(i=0;i<a.N;i++){
        for(j=0;j<a.M;j++)
            printf("%f ",a.A[i*a.M+j]);
        printf("\n");
    }
    printf("\n");
}

void FileOutput(struct Matr a, FILE * f){
    int i,j;
    if(a.N==0 || a.M==0){
        fprintf(f,"Matrix is empty! \n");
        return;
    }
	fprintf(f,"\nn=%d m=%d \n",a.N,a.M);			
    for(i=0;i<a.N;i++){
        for(j=0;j<a.M;j++)
            fprintf(f,"%f ",a.A[i*a.M+j]);
        fprintf(f,"\n");
    }
}
