#include "multyMpi.h"
#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Matr MultiplyMatr(struct Matr a, struct Matr b){
    int i,j,k;
    struct Matr c;
    c.N=a.N;
    c.M=b.M;
    if(a.N!=b.M){
        c.N=0;
        c.M=0;
        c.A=NULL;
        return c;
    }
    c.A=malloc(a.N*sizeof(double *));
    if(c.A==NULL){
        c.N=0;
        c.M=0;
        c.A=NULL;
        return c;
    }

    for(i=0;i<a.N;i++){
        c.A[i]=malloc(b.M*sizeof(double));
        if(c.A[i]==NULL){
            c.N=i;
            FreeMatr(a);
            c.N=0;
            c.M=0;
            c.A=NULL;
            return c;
        }
    }
    for(i=0;i<c.N; i++){
        for(j=0; j<c.M; j++){
            c.A[i][j]=0;
            for(k=0; k<c.N; k++)
                c.A[i][j]+=a.A[i][k]*b.A[k][j];
        }
    }
    return c;
}

