#include<stdio.h>
#include<stdlib.h>
#include "Arvore.h"

void criarArvore(No **pRaiz){
   *pRaiz=1;
   //*pRaiz ->esq;
   printf("Arvore criada\n");
}
void insercao(No **pRaiz, int raiz, int numero){
	if (*pRaiz==NULL){
	*pRaiz=(No *)malloc(sizeof (No));
	(*pRaiz)->esq=NULL;
	(*pRaiz)->dir=NULL;
	(*pRaiz)->raiz=numero;
	printf("Raiz = %d.\n", numero);
	}else {
		if (numero<((*pRaiz)->raiz)){
			insercao(&(*pRaiz)->esq, numero);
		}else{
			insercao(&(*pRaiz)->dir, numero);
		}
	}
     printf("Arvore criada\n");
}
int main(){

No minha_estrutura;
criarArvore(&minha_estrutura);
insercao(&minha_estrutura, 5, 3);

}
