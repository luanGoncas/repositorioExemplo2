#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int valor;
	char cor;
	struct No *esquerda;
	struct No *direita;
	struct No *pai;
	struct No *tio;
}TNoRB;

typedef struct{
	TNoRB *raiz;
}TArvoreRB;

void inserirNo(TNoRB *n, TNoRB *raiz){
	TNoRB *nAux;
	if(raiz == NULL){
		raiz->cor = 'B';
		raiz->valor = n->valor;
		raiz->esquerda = n->esquerda;
		raiz->direita = n->direita;
		raiz->pai = n->pai;
		raiz->tio = n->tio;
		raiz = n;
	}else{
		nAux = raiz;
		while(n != NULL){
			if(nAux->valor < n->valor){
				inserirNo(n->esquerda, nAux);
				n->pai = nAux;
				n->cor = 'R';
			}else{
				if(nAux->valor > n->valor || nAux->valor == n->valor){
					inserirNo(n->direita, nAux);
					n->pai = nAux;
					n->cor = 'R';
				}
			}
		}
	}
}

void rotate_ll(TNoRB *n){
	TNoRB *nAux = n;
	if(n->cor == 'R' && n->direita->cor == 'R'){
		nAux = n->pai;
		n->esquerda = n;
		n->tio = n->direita;
		n = nAux;
		n->cor = 'B';
	}
}

void rotate_rr(TNoRB *n){
	TNoRB *nAux = n;
	if(n->cor == 'R' && n->esquerda->cor == 'R'){
		nAux = n->pai;
		n = n->pai;
		n->direita = n;
		n->tio = n->esquerda;
		n = nAux;
		n->cor = 'B';
	}
}

void rotate_lr(TNoRB *n){
	if(n->cor == 'R' && n->pai->cor == 'R' && n->direita->cor == 'R'){
		rotate_ll(n);
		rotate_rr(n->pai);
	}
}

void rotate_rl(TNoRB *n){
	if(n->cor == 'R' && n->pai->cor == 'R' && n->esquerda->cor == 'R'){
		rotate_rr(n);
		rotate_ll(n->pai);
	}
}

void fixUp(TNoRB *raiz){
	TNoRB *nAux = raiz;
	while(nAux != NULL){
		if(nAux->cor == 'B'){
			nAux = nAux->esquerda;
			if(nAux->cor == 'R' && nAux->tio->cor == 'R'){
				if(nAux->pai->cor == 'R'){
					rotate_lr(nAux);
				}else{
					rotate_ll(nAux);
				}
				nAux = nAux->esquerda;
			}
			if(nAux->cor == 'R' && nAux->tio->cor == 'R'){
				if(nAux->pai->cor == 'R'){
					rotate_rl(nAux);
				}else{
					rotate_rr(nAux);
				}
				nAux = nAux->direita;
			}
		}else{
			nAux->cor = 'B';
			fixUp(raiz);
		}
	}
}

void removerNo(TNoRB *raiz, int valor){
	TNoRB *nAux = raiz;
	while(nAux != NULL){
		if(nAux->valor < valor){
			nAux = nAux->esquerda;
		}
		if(nAux->valor > valor){
			nAux = nAux->direita;
		}
		if(nAux->valor == valor){
			nAux->pai = nAux;
			nAux->pai->esquerda = nAux->esquerda;
			nAux->pai->direita = nAux->direita;
			nAux->pai->tio = nAux->tio;
			nAux = NULL;
		}
	}
}

void percorrerInOrdem(TNoRB *n){
	if(n != NULL){
		percorrerInOrdem(n->esquerda);
		printf("Valor: %d\n Cor: %d\n", n->valor, n->cor);
		percorrerInOrdem(n->direita);
	}
}

int main(){
	FILE *arquivo;
	TArvoreRB *arvore;
	TNoRB entrada[8];
	int i = 0;

	arquivo = fopen("entrada.txt", "rt");
	while(fgets(entrada[i], 8, arquivo) != NULL){
		inserirNo(TNoRB entrada[i], arvore->raiz);
		i++;
	}

	fixUp(arvore->raiz);

	percorrerInOrdem(arvore->raiz);

	return 0;
}