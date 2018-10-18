#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

arvore adicionar (int valor, arvore raiz, int *propagaFB) {
	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no_avl));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0;
	  * propagaFB = 1;
		return novo;
	}

	if(valor > raiz->dado) {
		raiz->dir = adicionar(valor, raiz->dir, propagaFB);
	  if(*propagaFB) {
				switch(raiz->fb) {
						case 0:
								raiz->fb = 1;
								break;
						case -1:
								raiz->fb = 0;
								propagaFB = 0;
								break;
						case 1:
								propagaFB = 0;
								return rotacionar(raiz);
				}
		}

	} else {
		raiz->esq = adicionar(valor, raiz->esq, propagaFB);
	  if(*propagaFB) {
				switch(raiz->fb) {
						case 0:
								raiz->fb = -1;
								break;
						case -1:
								propagaFB = 0;
								return rotacionar(raiz);

						case 1:
								raiz->fb = 0;
								propagaFB = 0;
								break;
				}
		}
	}
	return raiz;
}

int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

int maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->esq);
}

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

void imprimir_elemento(arvore raiz) {
	printf("%d [%d]", raiz->dado, raiz->fb);
}

arvore remover (int valor, arvore raiz) {
	if(raiz == NULL) 
		return NULL;

	if(raiz->dado == valor) {
		if(raiz->esq == NULL) {
			return raiz->dir;
		}
		if(raiz->dir == NULL) {
			return raiz->esq;
		}
		raiz->dado = maior_elemento(raiz->esq);
		raiz->esq = remover(raiz->dado, raiz->esq);
		return raiz;
	}
	if(valor > raiz->dado) {
			raiz->dir = remover(valor, raiz->dir);
	} else {
			raiz->esq = remover(valor, raiz->esq);
	}
	return raiz;

}


void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

arvore rotacionar(arvore raiz) {
	if(raiz->fb > 0) {
			switch(raiz->dir->fb)
			{
						case 1:
								return rotacao_simples_esquerda(raiz);
						case -1:
								return rotacao_dupla_esquerda(raiz);
						case 0:
								return raiz;
			}
	} else {
			switch(raiz->esq->fb) {
				case -1:
						return rotacao_simples_direita(raiz);
				case 1:
						return rotacao_dupla_direita(raiz);
				case 0:
						return raiz;
			}
	}
}






arvore rotacao_simples_direita(arvore raiz) {
	arvore p, u;
	printf("rotacao simples direita\n");

	p = raiz;
	u = raiz->esq;

	p->esq = u->dir;
	u->dir = p;

	p->fb = 0;
	u->fb = 0;



	return u;
}

arvore rotacao_simples_esquerda(arvore raiz) {
	arvore p,u;
	printf("rotacao simples esquerda\n");
	p = raiz;
	u = raiz->dir;

	p->dir = u->esq;
	u->esq = p;

	p->fb = 0;
	u->fb = 0;

	return u;
}
arvore rotacao_dupla_direita(arvore raiz) {

	arvore p,u, v;
	printf("rotacao dupla direita\n");
	p = raiz;
	u = raiz->esq;
	v = u->dir;

	u->dir = v->esq;
	v->esq = u;

	p->esq = v->dir;
	v->dir = p;

	switch(v->fb){

	case 0:
	p->fb = 0;
	u->fb = 0;
	break;
	case 1:
	v->fb = 0;
	p->fb = 0;
	u->fb = -1;
	break;
	case -1:
	p->fb = 1;
	v->fb = 0;
	u->fb = 0;

	}


	return v;
}
arvore rotacao_dupla_esquerda(arvore raiz) {
	printf("rotacao dupla esquerda\n");

	arvore v, u, p;

	p = raiz;
	u = raiz->esq;



	return raiz;
}
