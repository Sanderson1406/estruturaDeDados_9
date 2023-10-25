#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura do no

struct no {
	int numero;
	struct no *esquerda;
	struct no *direita;
	int cor; // 0 = preto, 1 = vermelho
};

//funcao que rotaciona a arvore a esquerda

struct no *rotacionarEsquerda(struct no *raiz) {
	//rotacao propriamente dita
	struct no *temp = raiz -> direita;
	raiz -> direita = temp -> esquerda;
	temp -> esquerda  = raiz;
	
	//ajuste da cor
	temp -> cor = raiz ->  cor;
	raiz -> cor = 1;
	
	//retorno
	return temp; 
}

//funcao que rotaciona a arvore a direta

struct no *rotacionarDireita(struct no *raiz) {
	//rotacao propriamente dita
	struct no *temp = raiz -> esquerda;
	raiz -> esquerda = temp -> direita;
	temp -> direita = raiz;
	
	//ajuste de cor
	temp -> cor = raiz -> cor;
	raiz -> cor = 1;
	
	return temp;
}

//funcao que sobe vermelho

void subirVermelho(struct no *raiz) {
	raiz -> cor = 1;
	raiz -> esquerda -> cor = 0;
	raiz -> direita -> cor = 0;
}

//funcao que determina a cor do no 

int vermelho(struct no *raiz) {
	int retorno = 0;
	if (raiz !=  NULL) {
		retorno = raiz -> cor;
	}
	return retorno;
}

//funcao que insere um no na arvore

struct no *inserir(struct no *raiz, int numero) {
	//inserir como arvore de busca
	if (raiz == NULL) {
		raiz = (struct no *) malloc(sizeof(struct no));
		raiz -> numero = numero;
		raiz -> esquerda = NULL;
		raiz -> direita = NULL;
		raiz -> cor = 1;
	} else {
		if (numero < raiz -> numero) {
			raiz -> esquerda = inserir(raiz -> esquerda, numero);
		} else {
			raiz -> direita = inserir(raiz -> direita, numero);
		}
	}
	
	//balanceamento da arvore
	if ((! vermelho(raiz -> esquerda)) && (vermelho(raiz -> direita))) {
		raiz = rotacionarEsquerda(raiz);
	}
	if (vermelho(raiz -> esquerda) && vermelho(raiz -> esquerda -> esquerda)) {
		raiz = rotacionarDireita(raiz);
	}
	if (vermelho(raiz -> esquerda) && vermelho(raiz -> direita)) {
		subirVermelho(raiz);
	}
	return raiz;
}

void imprimir(struct no *raiz, char *endentacao) {
	if (raiz != NULL) {
		printf("%s%d\n", endentacao, raiz -> numero);
		char *temp = (char *) malloc(1024 * sizeof(char));
		strcpy(temp, "---");
		strcat(temp, endentacao);
		imprimir(raiz -> esquerda, temp);
		imprimir(raiz -> direita, temp);
	}
}

//funcao de execucao de programa

int main() {
	struct no *raiz = NULL;
	int i = 0;
	
	for (i = 0; i < 1000; i++) {
		raiz = inserir(raiz, i);
	}
	
	imprimir(raiz, "");
}
