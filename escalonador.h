#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "fila_fifo.h"
#include "logtree.h"

typedef struct _escalonador {
    Fila_FIFO *filas[5];
    int disciplinas_fila[5];
    int fila_atual;
    int cont_atendimento;

    int delta_t;
    int timers_caixas[10];
    int quant_caixas;
    int relogio;

    Log *registrador;
} Escalonador;

// Inicializa o escalonador: Inicializa as 5 filas, define os “caixas” timers dos caixas, define o tempo "delta_t" para cada operação e define as disciplinas de atendimento de "n_1" a "n_5".
void e_inicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5);

// Insere na fila “classe” o cliente de número “num_conta”, que pretende realizar “qtde_operacoes” operações bancárias.
int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes);

// Retorna o número da conta do próximo cliente a ser atendido de acordo com a Disciplina de Atendimento, retirando-o da sua respectiva fila.
// Retorna -1 caso não tenha nenhum cliente em todas as filas.
int e_obter_prox_num_conta(Escalonador *e);

// Retorna o número da conta do próximo cliente a ser atendido de acordo com a Disciplina de Atendimento, sem retirá-lo da sua respectiva fila.
// Retorna -1 caso não tenha nenhum cliente em todas as filas.
int e_consultar_prox_num_conta (Escalonador *e);

// Retorna a quantidade de operações bancárias que o próximo cliente das filas pretende realizar com o caixa, sem retirá-lo da sua respectiva fila.
// Retorna -1 caso não tenha nenhum cliente em todas as filas.
int e_consultar_prox_qtde_oper(Escalonador *e);

// Retorna a próxima fila que será atendida de acordo com a Disciplina de Atendimento.
// Retorna -1 caso não tenha nenhum cliente em todas as filas.
int e_consultar_prox_fila(Escalonador *e);

// Retorna a quantidade total de clientes esperando atendimento em todas as filas.
int e_consultar_qtde_clientes(Escalonador *e);

// Retorna o tempo necessário para que o próximo cliente a ser atendido realize todas as operações financeiras que deseja, sem retirá-lo da sua respectiva fila.
// Retorna -1 caso não tenha nenhum cliente em todas as filas.
int e_consultar_tempo_prox_cliente(Escalonador *e);

// Realiza a configuração de inicialização do escalonador através da leitura do arquivo de configuração de nome “nome_arq_conf”.
// Retorna 1 em caso de sucesso e 0 caso contrário.
int e_conf_por_arquivo(Escalonador *e, char *nome_arq_conf);

// Executa a simulação do atendimento, lendo o arquivo de configuração de nome “nome_arq_in” e escrevendo o resultado do processamento para o arquivo de nome “nome_arq_out”.
void e_rodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out);

#endif