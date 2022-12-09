#ifndef LOGTREE_H
#define LOGTREE_H

typedef struct _log {
    int conta;
    int classe;
    int timer;
    int caixa;
    struct _log *esq;
    struct _log *dir;
} Log;

// Inicializa o registrador para qual o "l" aponta.
void log_inicializar(Log **l);

// Faz um registro em "l" guardando o tempo de atendimento "timer", o número da conta atendida "conta", a classe de número "classe" e o caixa de número "caixa".
void log_registrar(Log **l, int conta, int classe, int timer, int caixa);

// Retorna o tempo médio de espera, em minutos, para a classe de número "classe".
float log_media_por_classe(Log **l, int classe);

// Retorna a soma dos tempos de espera de todas as contas da classe "classe".
int log_obter_soma_por_classe(Log **l, int classe);

// Retorna a quantidade de clientes atendidos cujas contas são da classe de número "classe".
int log_obter_contagem_por_classe(Log **l, int classe);

#endif