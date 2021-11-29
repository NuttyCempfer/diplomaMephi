#include "multy.h"
#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Matr MultiplyMatr(struct Matr a, struct Matr b){
    int i,j,k;
    struct Matr c;
    c.N=a.N;
    c.M=b.M;
    if(a.M!=b.N){
        c.N=0;
        c.M=0;
        c.A=NULL;
        return c;
    }
    c.A=malloc(c.N*c.M*sizeof(double));
    if(c.A==NULL){
        c.N=0;
        c.M=0;
        c.A=NULL;
        return c;
    }

    for(i=0;i<c.N; i++){
        for(j=0; j<c.M; j++){
            c.A[i*c.M+j]=0;
            for(k=0; k<a.M; k++){
                c.A[i*c.M+j]+=a.A[i*a.M+k]*b.A[k*b.M+j];
			}
        }
    }
    return c;
}

