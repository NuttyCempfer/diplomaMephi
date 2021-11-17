#include "determMpi.h"
#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PermutationMatr(int a[], int N){
    int i,j,l,s;
    for(j=-1,i=0; i<N-1; i++)
        if(a[i]<a[i+1])
            j=i;
        if(j==-1)
            return 0;
    for(i=j+1; i<N; i++)
        if(a[i]>a[j])
            l=i;
    s=a[j];
    a[j]=a[l];
    a[l]=s;
    for(i=j+1; i<j+1+(N-j-1)/2; i++){
        s=a[i];
        a[i]=a[N-i+j];
        a[N-i+j]=s;
    }
    return ((N-j-1)/2)%2==0?-1:1;
}

double DetMatr(struct Matr a){
    int i,j,neg=1;
    double det,sum=0;
    int b[a.N];
    for(i=0; i<a.N; i++)
        b[i]=i+1;
    while(neg!=0){
        for(det=1, j=0; j<a.N; j++)
            det*=a.A[j][b[j]-1];
        det*=neg;
        neg*=PermutationMatr(b,a.N);
        sum+=det;
    }
    return sum;
}

