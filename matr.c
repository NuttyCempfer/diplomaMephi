#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*struct Matr InsertMatr(){
    struct Matr a;
    int i,j,x,y;
    printf("Insert number of line\n");
    scanf("%d",&x);
    printf("Insert number of column\n");
    scanf("%d",&y);
    a.N=x;
    a.M=y;
    a.A=malloc(x*sizeof(double **));
    if(a.A==NULL){
        a.N=0;
        a.M=0;
        a.A=NULL;
        return a;
    }
    for(i=0;i<x;i++){
        a.A[i]=malloc(y*sizeof(double));
        if(a.A[i]==NULL){
            a.N=i;
            FreeMatr(a);
            a.N=0;
            a.M=0;
            a.A=NULL;
            return a;
        }
    }
    for(i=0;i<x;i++){
        for(j=0;j<y;j++)
            a.A[i][j]=rand()%1000/100.;
    }
    return a;
};*/

void FreeMatr(struct Matr a){
    free(a.A);
}

void PrintMatr(struct Matr a){
    int i,j;
    if(a.N==0 || a.M==0){
        printf("Matrix is empty! \n");
        return;
    }
    for(i=0;i<a.N;i++){
        for(j=0;j<a.M;j++)
            printf("%f ",a.A[i*a.M+j]);
        printf("\n");
    }
    printf("\n");
}
