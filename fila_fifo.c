#include <stdlib.h>
#include "fila_fifo.h"

void f_inicializar(Fila_FIFO **f) {
    *f = NULL;
}

int f_inserir(Fila_FIFO **f, int chave, int valor) {
    int chave_repetida = 0;
    Fila_FIFO *novo_elemento, *inicio_fila;

    inicio_fila = *f;

    novo_elemento = (Fila_FIFO *) malloc(sizeof(Fila_FIFO));
    if (novo_elemento == NULL)
        return 0;

    novo_elemento->chave = chave;
    novo_elemento->valor = valor;
    novo_elemento->prox = NULL;

    while (*f != NULL && (*f)->prox != NULL) {
        if ((*f)->chave == chave)
            chave_repetida = 1;

        *f = (*f)->prox;
    }

    if ((*f)->chave == chave)
        chave_repetida = 1;

    if (chave_repetida) {
        *f = inicio_fila;
        return 0;
    }

    if (*f == NULL) {
        *f = novo_elemento;
    } else {
        (*f)->prox = novo_elemento;
        *f = inicio_fila;
    }

    return 1;
}

int f_obter_proxima_chave(Fila_FIFO **f) {
    int chave;
    Fila_FIFO *proximo;

    if (*f == NULL)
        return -1;

    proximo = *f;
    chave = proximo->chave;
    
    *f = (*f)->prox;
    free(proximo);
    proximo = NULL;

    return chave;
}

int f_consultar_proxima_chave(Fila_FIFO **f) {
    if (*f != NULL)
        return (*f)->chave;
    else
        return -1;
}

int f_consultar_proximo_valor(Fila_FIFO **f) {
    if (*f != NULL)
        return (*f)->valor;
    else
        return -1;
}

int f_num_elementos(Fila_FIFO **f) {
    int i;
    Fila_FIFO *inicio_fila;
    inicio_fila = *f;

    i = 0;
    while(*f != NULL){
        *f = (*f)->prox;
        i++;
    }

    *f = inicio_fila;
    return i;
}

int f_consultar_chave_por_posicao(Fila_FIFO **f, int posicao) {
    int i, chave;
    Fila_FIFO *inicio_fila;

    inicio_fila = *f;

    i = 1;
    while (i < posicao && (*f)->prox != NULL) {
        *f = (*f)->prox;
        i++;
    }

    if (i == posicao)
        chave = (*f)->chave;
    else
        chave = -1;

    *f = inicio_fila;
    return chave;
}

int f_consultar_valor_por_posicao(Fila_FIFO **f, int posicao) {
    int i, valor;
    Fila_FIFO *inicio_fila;

    inicio_fila = *f;

    i = 1;
    while (i < posicao && (*f)->prox != NULL) {
        *f = (*f)->prox;
        i++;
    }

    if (i == posicao)
        valor = (*f)->valor;
    else
        valor = -1;

    *f = inicio_fila;
    return valor;
}