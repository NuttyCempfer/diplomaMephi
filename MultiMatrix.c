#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Matr{
    int N;
    int M;
    double ** A;
};

struct Matr InsertMatr();
struct Matr MultiplyMatr(struct Matr, struct Matr);
void PrintMatr(struct Matr);
void freeMatr(struct Matr);

int main(){
    struct Matr a, b, c;
    int i,j,k;
    srand(time(NULL));
    a=InsertMatr();
    b=InsertMatr();
    PrintMatr(a);
    PrintMatr(b);
    //возможно под c надо память выделить
    c=MultiplyMatr(a,b);
    PrintMatr(c);
    freeMatr(a);
    freeMatr(b);
    freeMatr(c);
    return 0;
}

struct Matr InsertMatr(){
    int i,j,x,y;
    struct Matr a;
    printf("Input number of line\n");
    scanf("%d",&x);
    printf("Input number of column\n");
    scanf("%d",&y);
    a.N=x;
    a.M=y;
    a.A=malloc(x*sizeof(double *));
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
            freeMatr(a);
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
}

void freeMatr(struct Matr a){
    int i;
    for(i=0; i<a.N; i++)
        free(a.A[i]);
    free(a.A);
}

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
            freeMatr(a);
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

void PrintMatr(struct Matr a){
    int i, j;
    if(a.N==0 || a.M==0){
        printf("Matrix is empty\n");
        return;
    }
    for(i=0; i<a.N;i++){
        for(j=0; j<a.M;j++)
            printf("%f ",a.A[i][j]);
        printf("\n");
    }
    printf("\n");
}
