#include <stdio.h>

int getMenuItem(char * textItem[], int N){
	int i,j,item;
	do{
		for(i=0; i<N; i++)
			printf("%s \n", textItem[i]);
		printf("Enter menu item from 0 to %d \n",N-1);
		j=scanf("%d",&item);
		if(j==0)
			scanf("%*[^\n]%*c");
		if(j==-1)
			return -1;
	}while(j!=1);
	return item;
}
