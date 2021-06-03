#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Matr{
    int N;
    int M;
    double ** A;
};

struct Matr InsertMatr();
double DetMatr(struct Matr);
int PermutationMatr(int [], int);
void FreeMatr(struct Matr);
void PrintMatr(struct Matr);

int main(){
    struct Matr a;
    a=InsertMatr(a);
    PrintMatr(a);
    printf("det= %f\n",DetMatr(a));
    FreeMatr(a);
    return 0;
}

struct Matr InsertMatr(){
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
};

void FreeMatr(struct Matr a){
    int i;
    for(i=0;i<a.N;i++)
        free(a.A[i]);
    free(a.A);
}

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

void PrintMatr(struct Matr a){
    int i,j;
    if(a.N==0 || a.M==0){
        printf("Matrix is empty! \n");
        return;
    }
    for(i=0;i<a.N;i++){
        for(j=0;j<a.M;j++)
            printf("%f ",a.A[i][j]);
        printf("\n");
    }
    printf("\n");
}
