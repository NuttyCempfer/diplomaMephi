#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

void FreeMemory (struct massiveSect * MS){
	int i,j;
	if(MS==NULL)
		return;
	for(i=0; i<MS->n; i++){
		for(j=0; j<MS->sects[i].n; j++){
			free(MS->sects[i].set[j].key);
			free(MS->sects[i].set[j].value);
		}	
		free(MS->sects[i].set);
	}
	free(MS->sects);
}


void printSects(struct massiveSect * MS){
	int i,j;
	if(MS==NULL)
		return;
	for(i=0; i<MS->n; i++){
		printf("Секция: %s \n",MS->sects[i].name);
		for(j=0; j<MS->sects[i].n; j++){
			printf("Ключ: %s \n",MS->sects[i].set[j].key);
			printf("Значение: %s \n",MS->sects[i].set[j].value);
		}	
	}
} 

// [] - сектор 
// ; - комментарий
// param= - параметр
// =23, [2,3,4,5,6,7], asdfe - значение
struct massiveSect * OpenFile(FILE * pars){
	struct massiveSect * MS=NULL;
	struct section * cursect=NULL, * tmp;
	struct pair * tmp_k;
	char * p, c, * q;
	char * k, * v;
	int l, i;
	/*fscanf ("%*[]s" что-то писать для выявления ключа и т.д.)*/	
	for(;;){
		c='\0';
		if((l=fscanf(pars," ;%c",&c)) == 0){//проверка на комментарий
			if(fscanf(pars,"%m[^\n]",&p)!=0){ //проверка на всю строку и выделение памяти под p
				if(sscanf(p," [%m[^]]%c",&q,&c)==2 && c==']'){
					//printf("Секция: %s\n",q);
					if(MS!=NULL){
						for(i=0; i<MS->n && strcasecmp(q, MS->sects[i].name); i++);
						if(i==MS->n){
							tmp=realloc(MS->sects, ++MS->n*sizeof(struct section));
							if(tmp==NULL){
								printf("Ошибка выделения памяти! \n");
								free(q);
								FreeMemory(MS);
								return NULL;
							}
							MS->sects=tmp;
							cursect=&MS->sects[MS->n-1];
							MS->sects[MS->n-1].n=0;
							MS->sects[MS->n-1].name=q;
							MS->sects[MS->n-1].set=NULL;
						}
						else{
							printf("Дублирование секции! \n");
							//cursect=&MS->sects[i];
							FreeMemory(MS);
							free(q);
							return NULL;
						}
					}
					else{
						MS=malloc(sizeof(struct massiveSect));
						if(MS==NULL){
							printf("Ошибка выделения памяти! \n");
							free(q);
							return NULL;
						}
						MS->n=1;
						MS->sects=malloc(sizeof(struct section));
						if(MS->sects==NULL){
							printf("Ошибка выделения памяти! \n");
							free(q);
							FreeMemory(MS);
							return NULL;
						}
						cursect=&MS->sects[0];
						MS->sects[0].n=0;
						MS->sects[0].name=q;
						MS->sects[0].set=NULL;
					}
				}
				else{
					if(sscanf(p," %m[^=]%c",&q,&c)==2 && c=='='){
						sscanf(q,"%m[^ ]",&k);
						free(q);
						//printf("Ключ: %s\n",k);
						sscanf(p," %*[^=]= %m[^\n]",&q);
						sscanf(q,"%m[^ ]",&v);
						free(q);
						//printf("Значение: %s\n",v);
						if(MS==NULL){
							printf("Ключ вне секции! \n");
							free(k);
							free(v);
							return NULL;
						}
						for(i=0; i<cursect->n && strcmp(k,cursect->set[i].key); i++);
						if(i!=cursect->n){
							printf("Дублирование ключа! \n");
							free(k);
							free(v);
							FreeMemory(MS);
							return NULL;
						}
						tmp_k=realloc(cursect->set, ++cursect->n*sizeof(struct pair));
						if(tmp_k==NULL){
							printf("Ошибка выделения памяти! \n");
							free(k);
							free(v);
							FreeMemory(MS);
							return NULL;
						}
						cursect->set=tmp_k;
						cursect->set[cursect->n-1].key=k;
						cursect->set[cursect->n-1].value=v;						
					}
					else{
						printf("Синтаксическая ошибка! \n");
						FreeMemory(MS);
					}
				}
				free(p);
			}
			fscanf(pars,"%*c");//Отсекаем перевод строки
		}
		else if(c!='\n'){
			fscanf(pars, "%*[^\n]");
			fscanf(pars,"%*c");
		}
		if(l==EOF)
			break;
	}
	//FreeMemory(MS);
	return MS;
}

int WriteFile(FILE * wpars, struct massiveSect * MS){
	int i,j;
	if(MS==NULL)
		return 1;
	for(i=0; i<MS->n; i++){
		fprintf(wpars,"[%s] \n",MS->sects[i].name);
		for(j=0; j<MS->sects[i].n; j++){
			fprintf(wpars,"%s=%s \n",MS->sects[i].set[j].key,MS->sects[i].set[j].value);
		}	
	}
	return 0;
}


int TypeDataMatrix(char *nameSect, char *nameMatr, char *nameSize,
					struct massiveSect * S, int *pn, int *pm, double ** pa){
	int nsect, nmatr, nsize,l;
	char *p, *q;
	double *tmp, k;
	for(nsect=0; nsect<S->n && strcmp(S->sects[nsect].name,nameSect); nsect++);
	if(nsect==S->n)
		return 1;
	for(nmatr=0; nmatr<S->sects[nsect].n && strcmp(S->sects[nsect].set[nmatr].key, nameMatr ); nmatr++);
	if(nmatr==S->sects[nsect].n)
		return 2;
	for(nsize=0; nsize<S->sects[nsect].n && strcmp(S->sects[nsect].set[nsize].key, nameSize ); nsize++);
	if(nsize==S->sects[nsect].n)
		return 3;
	if(sscanf(S->sects[nsect].set[nsize].value,"%d",pm)!=1)
		return 6;
	if(S->sects[nsect].set[nmatr].value[0]!='(')
		return 6;
	if((p=strchr(S->sects[nsect].set[nmatr].value,')'))==NULL)
		return 6;
	if(strlen(p)!= 1)
		return 6;
	*pa=NULL;
	l=0;
	p=S->sects[nsect].set[nmatr].value;
	while(*p!=')'){
		k=strtod(p+1,&q);
		l++;
		if(p+1==q || *q!=',' && *q!=')'){
			free(*pa);
			return 6;
		}
		p=q;
		if((tmp=realloc(*pa,sizeof(double)*l))==NULL){
			free(*pa);
			return 6;
		}
		*pa=tmp;
		tmp[l-1]=k;
	}
	if(l%*pm!=0){
		free(*pa);
		return 4;
	}
	*pn=l/(*pm);
	

	/*
	 Распарсить размер матрицы.
	 Распарсить саму матрицу.
	 
	 */
	return 0;
}
/*
 Коды ошибок:
 0-succ
 1-Не найдена секция
 2-Не найдена матрица
 3-Не найден размер
 4-Не соответствие размера и матрицы
 5-Ошибка выделения памяти
 6-Синтаксическая ошибка
 7-
 8-
 9-
 
Что нужно программно избегать/исправить:
	1) Повторение секции (решение: объединить в одну)
	2) Повторение ключей внутри этой секции (решение: брать более актуальный ключ)
 	3) Игнор пробелов в ключах и их занчениях (чисто синтаксический вид)
	4) Массивы, матрицы (решение:если матрица, то писать хотя бы одну размерность.
									Если чисто массив, то просто строка)
	5) Научится вытаскивать значения в нужный нам тип данных 
		(число это число, массив - массив, матрица - матрица и т.д.)
*/
/*
[qwe]
t=7
e=5
u=7
 q = 7
var=(1,2,3,4,5,6)
mas=(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16)
rasm=4

[qas]
d=7
q=7
*/

