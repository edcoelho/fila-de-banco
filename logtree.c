#include <stdlib.h>
#include "logtree.h"

void log_inicializar(Log **l) {
    *l = NULL;
}

void log_registrar(Log **l, int conta, int classe, int timer, int caixa, int qtde_opers) {
    Log *raiz, *pai, *novo_elemento;

    raiz = *l;
    pai = NULL;
    novo_elemento = (Log *) malloc(sizeof(Log));
    novo_elemento->conta = conta;
    novo_elemento->classe = classe;
    novo_elemento->timer = timer;
    novo_elemento->caixa = caixa;
    novo_elemento->qtde_opers = qtde_opers;
    novo_elemento->esq = NULL;
    novo_elemento->dir = NULL;

    while (*l != NULL) {
        pai = *l;
        if (conta < (*l)->conta)
            *l = (*l)->esq;
        else
            *l = (*l)->dir;
    }

    if (pai == NULL)
        *l = novo_elemento;
    else if (conta < pai->conta)
        pai->esq = novo_elemento;
    else
        pai->dir = novo_elemento;

    if (raiz != NULL)
        *l = raiz;
}

float log_media_por_classe(Log **l, int classe) {
    return (float) log_obter_soma_por_classe(l, classe) / log_obter_contagem_por_classe(l, classe);
}

int log_obter_soma_por_classe(Log **l, int classe) {
    if (*l == NULL)
        return 0;
    else if ((*l)->classe == classe)
        return (*l)->timer + log_obter_soma_por_classe(&(*l)->esq, classe) + log_obter_soma_por_classe(&(*l)->dir, classe);
    else
        return log_obter_soma_por_classe(&(*l)->esq, classe) + log_obter_soma_por_classe(&(*l)->dir, classe);
}

int log_obter_soma_operacoes_por_classe(Log **l, int classe) {
    if (*l == NULL)
        return 0;
    else if ((*l)->classe == classe)
        return (*l)->qtde_opers + log_obter_soma_operacoes_por_classe(&(*l)->esq, classe) + log_obter_soma_operacoes_por_classe(&(*l)->dir, classe);
    else
        return log_obter_soma_operacoes_por_classe(&(*l)->esq, classe) + log_obter_soma_operacoes_por_classe(&(*l)->dir, classe);
}

int log_obter_contagem_por_classe(Log **l, int classe) {
    if (*l == NULL)
        return 0;
    else if ((*l)->classe == classe)
        return 1 + log_obter_contagem_por_classe(&(*l)->esq, classe) + log_obter_contagem_por_classe(&(*l)->dir, classe);
    else
        return log_obter_contagem_por_classe(&(*l)->esq, classe) + log_obter_contagem_por_classe(&(*l)->dir, classe);
}