#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Programa para representar o jogo "Adivinhe o número de estou pensando.
A estratura de dados para usada para gerenciar os valores foi uma  arvore Avl.*/

/*Caroline da Silva Morais Alves*/

/*-----------Cabeçalho-------------------*/

typedef struct tipoNo *ponteiro;
void inicializa(ponteiro *raiz);
void insere(ponteiro *p, int x);
void imprimePreOrdem(ponteiro p, int raiz);
int altura (ponteiro praiz);
int fBalanceamento (ponteiro raiz);
void RSE(ponteiro *raiz);
void RSD(ponteiro *raiz);
int BalancearEsq (ponteiro *raiz);
int BalancearDir (ponteiro *raiz);
int Balanceamento(ponteiro *raiz);
void inserirIntervalo (ponteiro *arvore);
void inserirAleatorio (ponteiro *arvore);
void limpabuffer(void);
void jogo(ponteiro p);

/*------------Estrutura da árvore--------------*/

typedef struct tipoNo{
    int chave, altura;
    ponteiro esq, dir;
}tipoNo;


void inicializa(ponteiro *arvore){
    *arvore = NULL;
  }

void insere(ponteiro *p, int x){

        if(*p == NULL){
            *p = (ponteiro)malloc(sizeof(tipoNo));
            (*p)->chave = x;
            (*p)->esq = NULL;
            (*p)->dir = NULL;
        }

        else if (x < (*p)->chave){
            insere(&(*p)->esq, x);
        }
        else if (x > (*p)->chave){
            insere(&(*p)->dir, x);
        }

    Balanceamento(p);
return;
}

void imprimePreOrdem(ponteiro p, int raiz){
    if(p!=NULL){
        if (p->chave == raiz)
            printf("%d",raiz);
        else
            printf("-%d",p->chave);
        imprimePreOrdem(p->esq, raiz);
        imprimePreOrdem(p->dir, raiz);}
return;
}

int altura (ponteiro raiz) {
    int aEsq = 0, aDir = 0;

    if (raiz == NULL)
        return 0;
    aEsq = altura(raiz->esq);
    aDir = altura(raiz->dir);

    if(aEsq > aDir)
        return aEsq +1;
    else
       return aDir +1;
}

int fBalanceamento (ponteiro raiz){

    if (raiz == NULL)
        return 0;
    return altura(raiz->esq) - altura(raiz->dir);
}

/*-----Funções para balanceamento-------*/

void RSE(ponteiro *raiz){
    ponteiro pAux;

    pAux = (*raiz)->dir;
    (*raiz)->dir = pAux->esq;
    pAux->esq = (*raiz);
    (*raiz) = pAux;
return;
}

void RSD(ponteiro *raiz){
    ponteiro pAux;

    pAux = (*raiz)->esq;
    (*raiz)->esq = pAux->dir;
    pAux->dir = (*raiz);
    (*raiz) = pAux;
return;
}

int BalancearEsq (ponteiro *raiz) {
	int fbe = fBalanceamento ((*raiz)->esq);

	if (fbe > 0){
        RSD(raiz);
        return 1;
	}
    else if (fbe < 0){
        RSE ((&(*raiz)->esq));
        RSD(&(*raiz));
        return 1;
    }
    return 0;
}

int BalancearDir (ponteiro *raiz) {
	int fbd = fBalanceamento ((*raiz)->dir);

	if ( fbd < 0 ){
        RSE(raiz);
        return 1;
	}
    else if (fbd > 0){
        RSD(&((*raiz)->dir));
        RSE (&(*raiz));
        return 1;
    }
    return 0;
}

int Balanceamento(ponteiro *raiz) {
    int fb = fBalanceamento(*raiz);

    if ( fb > 1)
        return BalancearEsq(raiz);
    else if (fb < -1 )
        return BalancearDir(raiz);
    else
        return 0;
}


/*----------Funções auxiliares---------*/

void inserirIntervalo (ponteiro *arvore){
    int n1, n2, i;

    scanf("%d %d", &n1, &n2);

        for (i = n1; i <= n2; i++){
            insere(arvore, i);
        }
return;
}

void inserirAleatorio (ponteiro *arvore) {
    int n,i,quantidade;
    scanf("%d", &quantidade);

        for (i=1; i<=quantidade; i++){
            scanf("%d,", &n);
            insere(arvore, n);
        }
limpabuffer();//limpa buffer caso o usuário entre com mais numeros que n
return;
}

void limpabuffer(void)//função para limpar o buffer
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void jogo(ponteiro p){
    char c;
    int cont = 1;
    while (p!=NULL){
        printf("%d?\n", p->chave);
        setbuf(stdin, NULL);
        c = getchar();
        getchar();
            if (c == '<'){
                cont++;
                p = p->dir;}
            else if (c == '>'){
                cont++;
                p = p->esq;}
            else if (c =='='){
                printf("Numero palpites: %d\n", cont);
                return;}
    }
return;
}

int main()
{
    ponteiro arvore;
    char op;

    scanf("%c",&op);
    switch(op){
        case 'i':
            inicializa(&arvore);
            inserirIntervalo(&arvore);
            jogo(arvore);
            printf("Arvore: ");imprimePreOrdem(arvore, arvore->chave);
            printf("\n");
            break;
        case 'c':
            inicializa(&arvore);
            inserirAleatorio(&arvore);
            jogo(arvore);
            printf("Arvore: ");imprimePreOrdem(arvore, arvore->chave);
            printf("\n");
            break;

        }
return 0;
}
