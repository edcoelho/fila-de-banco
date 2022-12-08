#ifndef FILA_FIFO_H
#define FILA_FIFO_H

typedef struct _fila_fifo {
    int valor;
    int chave;
    struct _fila_fifo *prox;
} Fila_FIFO;

// Inicializa a fila para qual o ponteiro "f" aponta.
void f_inicializar(Fila_FIFO **f);

// Insere o valor indexado por chave na fila para qual "f" aponta.
// Retorna 1 se inserir com sucesso e 0 se não conseguir inserir.
int f_inserir(Fila_FIFO **f, int chave, int valor);

// Retorna a chave do próximo elemento da fila para qual "f" aponta, retirando-o da fila. 
// Retorna -1 se a fila estiver vazia.
int f_obter_proxima_chave(Fila_FIFO **f);

// Retorna a chave do próximo elemento da fila para qual "f" aponta, sem retirá-lo da fila.
// Retorna -1 se a fila estiver vazia.
int f_consultar_proxima_chave(Fila_FIFO **f);

// Retorna o valor do próximo elemento da fila para qual "f" aponta, sem retirá-lo da fila.
// Retorna -1 se a fila estiver vazia.
int f_consultar_proximo_valor(Fila_FIFO **f);

// Retorna a quantidade de elementos da fila para qual "f" aponta.
int f_num_elementos (Fila_FIFO **f);

// Retorna a chave do "posicao"-ésimo elemento da fila para qual "f" aponta.
// Retorna -1 se a posição não existir.
int f_consultar_chave_por_posicao(Fila_FIFO **f, int posicao);

// Retorna o valor do "posicao"-ésimo elemento da fila para qual "f" aponta.
// Retorna -1 se a posição não existir.
int f_consultar_valor_por_posicao(Fila_FIFO **f, int posicao);

#endif